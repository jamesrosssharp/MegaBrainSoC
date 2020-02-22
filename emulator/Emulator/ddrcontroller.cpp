#include "ddrcontroller.h"

DDRController::DDRController()
{
    m_memory.resize(16*1024*1024 / 4); // DDR is 16MB
}

uint32_t DDRController::readMem(uint32_t address)
{
    return m_memory.at((address >> 2) & 0x3fffff);
}

uint32_t DDRController::writeMem(uint32_t address, uint32_t value)
{
    m_memory[address >> 2] = value;
    return 1;
}
