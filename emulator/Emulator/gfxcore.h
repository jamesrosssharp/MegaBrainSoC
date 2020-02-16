#ifndef GFXCORE_H
#define GFXCORE_H

#include "peripheral.h"

#include "igfxdevicedelegate.h"


class GFXCore   : public Peripheral, public IGfxDeviceDelegate
{
public:
    GFXCore();
    ~GFXCore();

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

    virtual void* getImageData();

    uint8_t* m_gfxmem;
};

#endif // GFXCORE_H
