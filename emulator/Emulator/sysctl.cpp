#include "sysctl.h"

#include "cortexm0cpu.h"
#include "nvic.h"

constexpr uint32_t kVTOR_REG_ADDRESS = 0x08;

SysCtl::SysCtl(CortexM0CPU* cpu)    :
    m_cpu(cpu)
{
    m_vtor = 0x0; // Vectors based at 0x0
}

uint32_t SysCtl::readMem(uint32_t address)
{

    if ((address & ~3UL) == kVTOR_REG_ADDRESS) // VTOR
    {
        return m_vtor;
    }
    return 0x0;
}

uint32_t SysCtl::writeMem(uint32_t address, uint32_t value)
{

    if ((address & ~3UL) == kVTOR_REG_ADDRESS) // VTOR
    {
        m_vtor = value;
    }
    return 0x0;
}
