#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include <cstdint>

// Base class for all bus peripherals

class Peripheral
{
public:
    virtual ~Peripheral();

    virtual uint32_t readMem(uint32_t address) = 0;
    virtual uint32_t writeMem(uint32_t address, uint32_t value) = 0;

};


#endif // PERIPHERAL_H
