#ifndef SPICONTROLLER_H
#define SPICONTROLLER_H

#include <thread>
#include <mutex>
#include <condition_variable>

#include "peripheral.h"
#include "spidevice.h"
#include "nvic.h"

class SystemBus;

class SPIController : public Peripheral
{
public:
    SPIController(SPIDevice* device, NVIC* nvic, uint32_t irq);
    ~SPIController();

    void registerSystemBus(SystemBus* systembus);

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

private:
    void threadFunc();

private:
    SPIDevice* m_device;
    NVIC* m_nvic;

    uint32_t m_irq;

    std::mutex m_mutex;
    std::condition_variable m_cond;

    volatile bool m_threadExit;

    uint32_t m_controlReg;
    uint32_t m_dmaSourceAddrReg;
    uint32_t m_dmaSinkAddrReg;

    SystemBus* m_bus;

    std::thread m_thread;
};

#endif // SPICONTROLLER_H
