#ifndef GFXCORE_H
#define GFXCORE_H

#include "peripheral.h"

#include "igfxdevicedelegate.h"

#include <thread>
#include <mutex>
#include <condition_variable>

class SystemBus;
class NVIC;

class GFXCore   : public Peripheral, public IGfxDeviceDelegate
{
public:
    GFXCore(NVIC* nvic);
    ~GFXCore();

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

    virtual void* getImageData();

    void registerSystemBus(SystemBus* bus);

private:

    void* backBufferPtr();
    void blitterThreadFunc();
    void dmaThreadFunc();

private:

    SystemBus* m_sysbus;
    NVIC* m_nvic;

    uint8_t* m_gfxmem;

    volatile bool m_threadExit;



    uint32_t m_bltControlReg;

    uint32_t m_bltSrcWH;
    uint32_t m_bltScrRS;
    uint32_t m_bltDestXY;
    uint32_t m_bltSrcAddr;
    uint32_t m_bltSrcXY;
    uint32_t m_bltFillCol;
    uint32_t m_bltDepth;

    uint32_t m_fbcon;

    uint32_t m_dmacon;
    uint32_t m_dmasrc;
    uint32_t m_dmadest;

    uint32_t m_palette[256];

    std::mutex m_bltMutex;
    std::condition_variable m_bltCond;

    std::thread m_bltThread;

    std::mutex m_dmaMutex;
    std::condition_variable m_dmaCond;

    std::thread m_dmaThread;

};

#endif // GFXCORE_H
