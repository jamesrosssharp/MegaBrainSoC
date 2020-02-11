#include "spicontroller.h"

/*
 *  Registers
 *
 *  0x0:  Control reg
 *
 *      Bit 16: 1 = go (cleared by hardware)
 *      Bits 0-15: transfer size in bytes
 *
 *  0x4:  DMA source address reg (must be dword aligned)
 *  0x8:  DMA sink address reg (must be dword aligned)
 *
 *
 *
 */

#define GO_FLAG (1UL<<16)

#include "systembus.h"
#include "nvic.h"

SPIController::SPIController(SPIDevice* device, NVIC* nvic, uint32_t irq) :
    m_device(device),
    m_nvic(nvic),
    m_irq(irq),
    m_thread([] (SPIController* spi) { spi->threadFunc(); }, this)
{

}

void SPIController::registerSystemBus(SystemBus* systembus)
{
    m_bus = systembus;
}


SPIController::~SPIController()
{
    m_threadExit = true;
    m_cond.notify_all();
    m_thread.join();
}

uint32_t SPIController::readMem(uint32_t address)
{

    switch (address)
    {
        case 0:
            return m_controlReg;
        case 4:
            return m_dmaSourceAddrReg;
        case 8:
            return m_dmaSinkAddrReg;
    }

    return 0;
}

uint32_t SPIController::writeMem(uint32_t address, uint32_t value)
{
    switch (address)
    {
        case 0:
            m_controlReg = value;

            if (m_controlReg & GO_FLAG)
            {
                m_cond.notify_all();
            }
            break;
        case 4:
            m_dmaSourceAddrReg = value;
            break;
        case 8:
            m_dmaSinkAddrReg = value;
            break;
    }

    return 0;
}

void SPIController::threadFunc()
{

    while (! m_threadExit)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock);

        if (m_controlReg & GO_FLAG)
        {
            if (!m_bus)
                continue;

            m_controlReg &= ~GO_FLAG;

            uint16_t bytes = m_controlReg & 0xffff;

            // Perform DMA transcation. SPI bus freq is 32MHz, therefore 4Mbytes / second (or sleep 1 microsecond
            // every four bytes bytes)

            uint32_t sourceAddr = m_dmaSourceAddrReg & ~3UL;
            uint32_t sinkAddr   = m_dmaSinkAddrReg & ~3UL;

            m_device->assertChipSelect(true);

            while (bytes)
            {
                uint32_t dword = m_bus->readMem(sourceAddr);

                uint32_t outword = 0;

                for (int i = 0; i < 4; i++)
                {
                    if (!bytes)
                        break;

                    outword >>= 8;

                    uint8_t byte = dword & 0xff;
                    uint8_t outByte = 0;
                    m_device->transceive(byte, &outByte);

                    outword |= (static_cast<uint32_t>(outByte) << 24);
                    dword >>= 8;

                    bytes--;

                }

                m_bus->writeMem(sinkAddr, outword);

                sourceAddr += 4;
                sinkAddr += 4;

                // Sleep to throttle transfer to bus speed
                struct timespec tm1, tm2;

                tm1.tv_sec = 0 ; //1

               // tm1.tv_sec = 1;
                tm1.tv_nsec = 31;
                nanosleep(&tm1, &tm2);
            }

            m_device->assertChipSelect(false);

            m_nvic->assertIRQ(m_irq, true);

        }
    }
}
