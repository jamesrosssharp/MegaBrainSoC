#ifndef ROM_H
#define ROM_H

#include <vector>

#include "peripheral.h"

class ROM : public Peripheral
{
public:
    ROM();

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

private:

    std::vector<uint32_t> m_memory;

};

#endif // ROM_H
