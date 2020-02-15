#ifndef GFXCORE_H
#define GFXCORE_H

#include "peripheral.h"


class GFXCore   : public Peripheral
{
public:
    GFXCore();

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

};

#endif // GFXCORE_H
