#include "systembus.h"

#include "rom.h"
#include "cortexm0cpu.h"
#include "ddrcontroller.h"
#include "uart.h"
#include "sram.h"

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

constexpr uint32_t kSRAMStart   = 0x00001000;
constexpr uint32_t kSRAMEnd     = 0x00001fff;
constexpr uint32_t kSRAMMask    = 0xfffff000;
constexpr uint32_t kSRAMMaskVal = 0x00001000;

constexpr uint32_t kUARTStart   = 0x10000000;
constexpr uint32_t kUARTEnd     = 0x100000ff;
constexpr uint32_t kUARTMask    = 0xffffff00;
constexpr uint32_t kUARTMaskVal = 0x10000000;

constexpr uint32_t kDDRStart   = 0x20000000;
constexpr uint32_t kDDREnd     = 0x20ffffff;
constexpr uint32_t kDDRMask    = 0xff000000;
constexpr uint32_t kDDRMaskVal = 0x20000000;


SystemBus::SystemBus(CortexM0CPU* cpu, ROM* rom, DDRController* ddr, UART* uart, SRAM* sram)    :
    m_cpu(cpu),
    m_rom(rom),
    m_ddr(ddr)
{
    m_addresses.emplace_back(kROMStart,  kROMEnd,  kROMMask,  kROMMaskVal,  rom);
    m_addresses.emplace_back(kSRAMStart,  kSRAMEnd,  kSRAMMask,  kSRAMMaskVal,  sram);
    m_addresses.emplace_back(kUARTStart, kUARTEnd, kUARTMask, kUARTMaskVal, uart);
    m_addresses.emplace_back(kDDRStart,  kDDREnd,  kDDRMask,  kDDRMaskVal,  ddr);
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

    // Which peripheral is being read from?

    int p = findPeripheral(addr);

    if (p >= 0)
    {
        PeriphWrapper& pw = m_addresses.at(static_cast<std::size_t>(p));
        return pw.m_periph->readMem(addr - pw.m_addrMin);
    }
    else {
        // Exception?
        return 0;
    }
}

void SystemBus::writeMem(uint32_t addr, uint32_t value)
{

    // Which peripheral is being read from?

    int p = findPeripheral(addr);

    if (p >= 0)
    {
        PeriphWrapper& pw = m_addresses.at(static_cast<std::size_t>(p));
        pw.m_periph->writeMem(addr - pw.m_addrMin, value);
    }
    else {
        // Exception?
    }
}

