
#include <fstream>
#include <stdexcept>

#include "rom.h"

ROM::ROM()
{

    // Load our ROM contents

    m_memory.resize(1024); // ROM is 1k words (4kB)

    std::ifstream from;

    from.open("../../code/SimpleROM/main.bin", std::ios::binary);

    if (!from.is_open())
    {
        throw std::runtime_error("Cannot open ROM!");
    }

    uint32_t i = 0;
    while (! from.eof())
    {
        uint8_t bytes[4];
        from.read(reinterpret_cast<char*>(bytes), 4);
        m_memory[i++] = static_cast<uint32_t>(bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24));
    }

}

uint32_t ROM::readMem(uint32_t address)
{
    return m_memory.at((address >> 2) & 0x3ff);
}

uint32_t ROM::writeMem(uint32_t address, uint32_t value)
{
    // NOP - it's a ROM!
    (void) address;
    (void) value;
    return 0;
}
