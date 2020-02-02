#ifndef SYSTEMBUS_H
#define SYSTEMBUS_H

#include <cstdint>
#include <vector>

#include "peripheral.h"

class CortexM0CPU;
class ROM;
class DDRController;
class UART;
class SRAM;

class SystemBus
{
public:
    SystemBus(CortexM0CPU* cpu, ROM* rom, DDRController* ddr, UART* uart, SRAM* sram);

    uint32_t readMem(uint32_t addr);
    void     writeMem(uint32_t addr, uint32_t value);

private:

    class PeriphWrapper
    {
    public:
        PeriphWrapper(uint32_t addrMin, uint32_t addrMax, uint32_t addrMask, uint32_t addrMaskValue, Peripheral* periph) :
            m_addrMin(addrMin),
            m_addrMax(addrMax),
            m_addrMask(addrMask),
            m_addrMaskValue(addrMaskValue),
            m_periph(periph) {}

        uint32_t m_addrMin;
        uint32_t m_addrMax;
        uint32_t m_addrMask;
        uint32_t m_addrMaskValue;
        Peripheral* m_periph;
    };

    int findPeripheral(uint32_t addr); // returns index of periph wrapper, -1 if not found

private:


    CortexM0CPU* m_cpu;
    ROM* m_rom;
    DDRController* m_ddr;

    std::vector<PeriphWrapper> m_addresses;

};

#endif // SYSTEMBUS_H
