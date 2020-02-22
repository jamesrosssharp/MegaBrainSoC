#ifndef GFXCORE_H
#define GFXCORE_H

#include "peripheral.h"

#include "igfxdevicedelegate.h"

#include <thread>
#include <mutex>
#include <condition_variable>

class GFXCore   : public Peripheral, public IGfxDeviceDelegate
{
public:
    GFXCore();
    ~GFXCore();

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

    virtual void* getImageData();

private:

    void* backBufferPtr();
    void blitterThreadFunc();

private:


    uint8_t* m_gfxmem;

    volatile bool m_threadExit;

    std::mutex m_bltMutex;
    std::condition_variable m_bltCond;

    std::thread m_bltThread;

    uint32_t m_bltControlReg;

    uint32_t m_bltSrcWH;
    uint32_t m_bltScrRS;
    uint32_t m_bltDestXY;
    uint32_t m_bltSrcAddr;
    uint32_t m_bltSrcXY;
    uint32_t m_bltFillCol;
    uint32_t m_bltDepth;

    uint32_t m_fbcon;

    uint32_t m_palette[256];
};

#endif // GFXCORE_H
