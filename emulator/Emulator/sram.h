#ifndef SRAM_H
#define SRAM_H

#include <vector>

#include "peripheral.h"

class SRAM : public Peripheral
{
public:
    SRAM();

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

private:

    std::vector<uint32_t> m_memory;

};

#endif // SRAM_H
