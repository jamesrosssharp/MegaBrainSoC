#include "sram.h"

SRAM::SRAM()
{

    m_memory.resize(1024); // 1k words = 4kB

}

uint32_t SRAM::readMem(uint32_t address)
{
    return m_memory.at((address >> 2) & 0x3ff);
}

uint32_t SRAM::writeMem(uint32_t address, uint32_t value)
{
    m_memory[address >> 2] = value;
    return 1;
}
