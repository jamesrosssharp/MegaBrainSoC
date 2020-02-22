#include "systembus.h"

#include "rom.h"
#include "cortexm0cpu.h"
#include "ddrcontroller.h"
#include "uart.h"
#include "sram.h"
#include "spicontroller.h"
#include "sysctl.h"
#include "nvic.h"
#include "gfxcore.h"

#include <mutex>

/*
 *  NOTES:
 *
 *  - system bus is always 32 bits wide, and cannot handle unaligned accesses
 *  - to perform unaliagned accesses, the whole 32 bit word must be queried and
 *    the relevant word or byte extracted.
 *
 * MEMORY MAP
 *
 * - 0x00000000 - 0x00001000 (4kB)  ROM
 *
 */

constexpr uint32_t kROMStart   = 0x00000000;
constexpr uint32_t kROMEnd     = 0x00000fff;
constexpr uint32_t kROMMask    = 0xfffff000;
constexpr uint32_t kROMMaskVal = 0x00000000;

constexpr uint32_t kDDRStart   = 0x20000000;
constexpr uint32_t kDDREnd     = 0x20ffffff;
constexpr uint32_t kDDRMask    = 0xff000000;
constexpr uint32_t kDDRMaskVal = 0x20000000;

constexpr uint32_t kSCBStart    = 0xE000ED00;
constexpr uint32_t kSCBEnd      = 0xE000ED8F;
constexpr uint32_t kSCBMask     = 0xffffff00;
constexpr uint32_t kSCBMaskVal  = 0xE000ED00;

constexpr uint32_t kNVICStart    = 0xE000E100;
constexpr uint32_t kNVICEnd      = 0xE000ECFF;
constexpr uint32_t kNVICMask     = 0xfffff000;
constexpr uint32_t kNVICMaskVal  = 0xE000E000;

constexpr uint32_t kSRAMStart   = 0x00001000;
constexpr uint32_t kSRAMEnd     = 0x00001fff;
constexpr uint32_t kSRAMMask    = 0xfffff000;
constexpr uint32_t kSRAMMaskVal = 0x00001000;

constexpr uint32_t kUARTStart   = 0x10000000;
constexpr uint32_t kUARTEnd     = 0x100000ff;
constexpr uint32_t kUARTMask    = 0xffffff00;
constexpr uint32_t kUARTMaskVal = 0x10000000;

constexpr uint32_t kSPI0Start   = 0x10000100;
constexpr uint32_t kSPI0End     = 0x100001ff;
constexpr uint32_t kSPI0Mask    = 0xffffff00;
constexpr uint32_t kSPI0MaskVal = 0x10000100;

constexpr uint32_t kGFXStart   = 0x10010000;
constexpr uint32_t kGFXEnd     = 0x1001ffff;
constexpr uint32_t kGFXMask    = 0xffff0000;
constexpr uint32_t kGFXMaskVal = 0x10010000;



SystemBus::SystemBus(CortexM0CPU* cpu, ROM* rom, DDRController* ddr, UART* uart, SRAM* sram,
                     SPIController* spi0, SysCtl* sysctl, NVIC* nvic, GFXCore* gfx)    :
    m_cpu(cpu),
    m_rom(rom),
    m_ddr(ddr)
{
    m_addresses.emplace_back(kROMStart,  kROMEnd,  kROMMask,  kROMMaskVal,  rom);
    m_addresses.emplace_back(kDDRStart,  kDDREnd,  kDDRMask,  kDDRMaskVal,  ddr);
    m_addresses.emplace_back(kSCBStart,  kSCBEnd,  kSCBMask,  kSCBMaskVal,  sysctl);
    m_addresses.emplace_back(kNVICStart,  kNVICEnd,  kNVICMask,  kNVICMaskVal,  nvic);
    m_addresses.emplace_back(kSRAMStart,  kSRAMEnd,  kSRAMMask,  kSRAMMaskVal,  sram);
    m_addresses.emplace_back(kUARTStart, kUARTEnd, kUARTMask, kUARTMaskVal, uart);
    m_addresses.emplace_back(kSPI0Start, kSPI0End, kSPI0Mask, kSPI0MaskVal, spi0);
    m_addresses.emplace_back(kGFXStart, kGFXEnd, kGFXMask,    kGFXMaskVal, gfx);
}

int SystemBus::findPeripheral(uint32_t addr)
{
    int i = 0;
    for (auto p : m_addresses) // Linear search -- ok for small N
    {
        if ((addr & p.m_addrMask) == p.m_addrMaskValue)
            return i;
        i ++;
    }
    return -1;
}

uint32_t SystemBus::readMem(uint32_t addr)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    // Which peripheral is being read from?

    int p = findPeripheral(addr);

    if (p >= 0)
    {
        PeriphWrapper& pw = m_addresses.at(static_cast<std::size_t>(p));

        if (addr < pw.m_addrMin) return 0;

        return pw.m_periph->readMem(addr - pw.m_addrMin);
    }
    else {
        // Exception?
        return 0;
    }
}

void SystemBus::writeMem(uint32_t addr, uint32_t value)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    // Which peripheral is being read from?

    int p = findPeripheral(addr);

    if (p >= 0)
    {
        PeriphWrapper& pw = m_addresses.at(static_cast<std::size_t>(p));

        if (addr < pw.m_addrMin) return; // This handles screwy peripherals like the NVIC

        pw.m_periph->writeMem(addr - pw.m_addrMin, value);
    }
    else {
        // Exception?
    }
}

