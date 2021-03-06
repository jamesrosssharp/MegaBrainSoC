#include "gfxcore.h"

#include <stdlib.h>
#include <string.h>

#include "blitter.h"
#include "systembus.h"
#include "nvic.h"

#include "interrupts.h"

/*
 *  GFX Core consists of:
 *
 *  Framebuffer is always 32 bit, 640 * 360 (Which will be tripled in hardware to 1920*1080)
 *  Only the lower 24 bits of each sample are used.
 *
 *  Depth buffer high bit stores active framebuffer, so depth buffer doesn't have to be cleared each frame.
 *
 *  Memory:
 *
 *      0x00000000 - 0x002fffff - FB0
 *      0x00300000 - 0x005fffff - FB1
 *      0x00600000 - 0x008fffff - depth buffer
 *      0x00900000 - 0x00ffffff - user space
 *
 *  FBCON -
 *      Reg 0x00    control reg
 *              bit 0:  0 = backbuffer is FB0, frontbuffer is FB1
 *                      1 = backbuffer is FB1, frontbuffer is FB0
 *
 *  DMA Controller -
 *      Reg 0x10    Control Reg
 *              Bits 0-15: dma xfer size (in 32 bit words)
 *              Bit 16: "GO" (cleared by hardware)
 *
 *
 *      Reg 0x14    DMA Source (main mem)
 *      Reg 0x18    DMA Dest (gfx mem)
 *
 *  Blitter controller -
 *
 *      (Allows blits from user mem or backbuffer to backbuffer)
 *      Reg 0x20    Control reg
 *                  Bit 0: 1 = start (cleared by hardware)
 *                  Bit 1: blit depth
 *                          0 = indexed
 *                          1 = 32 bpp
 *                  Bit 2: src
 *                          0 = usr gfx mem
 *                          1 = back buffer
 *                  Bits 3 - 5: blit func
 *                          000b = copy
 *                          001b = block fill
 *                          others = reserved
 *
 *      Reg 0x24    Source w, h
 *      Reg 0x28    Source row stride
 *      Reg 0x2c    Dest x,y - on current back buffer
 *      Reg 0x30    Source base addr
 *      Reg 0x34    Source x,y - on current back buffer (if applicable)
 *      Reg 0x38    Fill color
 *      Reg 0x3c    Blit depth value
 *
 *  Sprite channel 0 - 31 : (0x40 - 0x23f)
 *
 *      TODO
 *
 *  Palette:        0x300 - 0x6ff
 *      Lowest 24 bits is used for 8-bit indexed operations
 *
 */

// TODO Hardware reg description + include generation

#define FBSIZE 0x00300000
#define USR_MEM_START 0x00900000
#define GFX_MEM_SIZE     16*1024*1024

#define GFXREG_FBCON    0x00

#define GFXREG_DMACON   0X10
#define GFXREG_DMASRC   0X14
#define GFXREG_DMADEST  0X18

#define GFXREG_BLTCON         0x20
#define GFXREG_BLTSRCWH       0x24
#define GFXREG_BLTSRCRS       0x28
#define GFXREG_BLTDESTXY      0x2c
#define GFXREG_BLTSRCADDR     0x30
#define GFXREG_BLTSRCXY       0x34
#define GFXREG_BLTFILLCOL     0x38
#define GFXREG_BLTDEPTH       0x3c

#define GFXREG_BLTCON_GOFLAG    0x01UL
#define GFXREG_BLTCON_BLTDEPTH  0x02UL
#define GFXREG_BLTCON_BLTSRC    0x04UL

#define GFXREG_BLTCON_BLTFUNC_MASK    0x038UL
#define GFXREG_BLTCON_BLTFUNC_SHIFT   3
#define GFXREG_BLTCON_BLTFUNC_COPY 0
#define GFXREG_BLTCON_BLTFUNC_FILL 1

#define GFXREG_DMACON_GOFLAG 0x010000UL
#define GFXREG_DMACON_SIZE_MASK 0xffffUL
#define GFXREG_DMACON_SIZE_SHIFT 0



GFXCore::GFXCore(NVIC* nvic)  :
    m_nvic(nvic),
    m_threadExit(false),
    m_bltThread([] (GFXCore* gfx) { gfx->blitterThreadFunc(); }, this),
    m_dmaThread([] (GFXCore* gfx) { gfx->dmaThreadFunc();}, this)
{
    m_gfxmem = new uint8_t[GFX_MEM_SIZE];
    memset(m_gfxmem, 0x30, GFX_MEM_SIZE);

    m_fbcon = 0;
    m_bltControlReg = 0;
}

void GFXCore::registerSystemBus(SystemBus *bus)
{
    m_sysbus = bus;
}

GFXCore::~GFXCore()
{
    m_threadExit = true;
    m_bltCond.notify_all();
    m_dmaCond.notify_all();
    m_bltThread.join();
    m_dmaThread.join();
    delete [] m_gfxmem;
}

void* GFXCore::getImageData()
{
    return m_gfxmem;
}

uint32_t GFXCore::readMem(uint32_t address)
{
    switch (address)
    {
        case GFXREG_FBCON:

            break;
        case GFXREG_DMACON:
            return m_dmacon;
        case GFXREG_DMASRC:
            return m_dmasrc;
        case GFXREG_DMADEST:
            return m_dmadest;
        case GFXREG_BLTCON:
            return m_bltControlReg;
        case GFXREG_BLTSRCWH:
            return m_bltSrcWH;
        case GFXREG_BLTSRCRS:
            return m_bltScrRS;
        case GFXREG_BLTDESTXY:
            return m_bltDestXY;
        case GFXREG_BLTSRCADDR:
            return m_bltSrcAddr;
        case GFXREG_BLTSRCXY:
            return m_bltSrcXY;
        case GFXREG_BLTFILLCOL:
            return m_bltFillCol;
        case GFXREG_BLTDEPTH:
            return m_bltDepth;
        default:

            if (address >= 0x300 && address < 0x700)
            {
                // Pallete registers
                return m_palette[(address - 0x300) >> 2];
            }
    }

    return 0;
}

uint32_t GFXCore::writeMem(uint32_t address, uint32_t value)
{
    (void) value;

    switch (address)
    {
        case GFXREG_FBCON:

            break;
        case GFXREG_DMACON:
            m_dmacon = value;

            if (m_dmacon & GFXREG_DMACON_GOFLAG)
            {
                m_dmaCond.notify_all();
            }

            break;
        case GFXREG_DMASRC:
            m_dmasrc = value;

            break;
        case GFXREG_DMADEST:
            m_dmadest = value;

            break;
        case GFXREG_BLTCON:

            m_bltControlReg = value;

            if (m_bltControlReg & GFXREG_BLTCON_GOFLAG)
            {
                m_bltCond.notify_all();
            }

            break;
        case GFXREG_BLTSRCWH:

            m_bltSrcWH = value;

            break;
        case GFXREG_BLTSRCRS:

            m_bltScrRS = value;

            break;
        case GFXREG_BLTDESTXY:

            m_bltDestXY = value;

            break;
        case GFXREG_BLTSRCADDR:

            m_bltSrcAddr = value;

            break;
        case GFXREG_BLTSRCXY:

            m_bltSrcXY = value;

            break;
        case GFXREG_BLTFILLCOL:

            m_bltFillCol = value;

            break;
        case GFXREG_BLTDEPTH:

            m_bltDepth = value;

            break;
        default:
            if (address >= 0x300 && address < 0x700)
            {
                // Pallete registers
                m_palette[(address - 0x300) >> 2] = value;
            }
    }

    return 0;
}

void* GFXCore::backBufferPtr()
{
    if (!(m_fbcon & 0x1UL))
    {
        return &m_gfxmem[0];
    }
    else {
        return &m_gfxmem[FBSIZE];
    }
}

void GFXCore::blitterThreadFunc()
{

    while (! m_threadExit)
    {
        std::unique_lock<std::mutex> lock(m_bltMutex);
        m_bltCond.wait(lock);

        if (m_bltControlReg & GFXREG_BLTCON_GOFLAG)
        {

            m_bltControlReg &= ~GFXREG_BLTCON_GOFLAG;

            uint32_t func = (m_bltControlReg & GFXREG_BLTCON_BLTFUNC_MASK) >> GFXREG_BLTCON_BLTFUNC_SHIFT;

            switch (func)
            {
                case GFXREG_BLTCON_BLTFUNC_COPY:
                {

                    if ((m_bltControlReg & GFXREG_BLTCON_BLTSRC) == 0)
                    {
                        // Source: user gfx mem

                        uint32_t x = m_bltDestXY & 0xffff;
                        uint32_t y = (m_bltDestXY >> 16) & 0xffff;

                        uint32_t w = m_bltSrcWH & 0xffff;
                        uint32_t h = (m_bltSrcWH >> 16) & 0xffff;

                        uint32_t rs = m_bltScrRS;

                        if ((m_bltControlReg & GFXREG_BLTCON_BLTDEPTH) == 0)
                        {
                            uint8_t* src = (m_bltSrcAddr + USR_MEM_START) + m_gfxmem;

                            // Bounds check here so no nastiness?

                            printf("cpy blt from %x to %p %d %d %d %d %d", m_bltSrcAddr, backBufferPtr(), w, rs, h, x, y);

                            blt_Copy_8BPP_32BPP(src, backBufferPtr(), w, rs, h,
                                                        x, y, m_palette);

                        }
                        else {

                        }

                    }
                    else {

                    }

                    break;
                }
                case GFXREG_BLTCON_BLTFUNC_FILL:
                {
                    uint32_t x = m_bltDestXY & 0xffff;
                    uint32_t y = (m_bltDestXY >> 16) & 0xffff;

                    uint32_t w = m_bltSrcWH & 0xffff;
                    uint32_t h = (m_bltSrcWH >> 16) & 0xffff;

                    if ((m_bltControlReg & GFXREG_BLTCON_BLTDEPTH) == 0)
                    {
                        blt_Fill_8BPP(backBufferPtr(), x, y, w, h, static_cast<uint8_t>(m_bltFillCol & 0xff), m_palette, m_bltDepth);
                    }
                    else {
                        //blt_Fill_32BPP();
                    }

                    break;
                }
            }

            m_nvic->assertIRQ(kGFXBLTCON_IRQ, true);

        }
    }
}

void GFXCore::dmaThreadFunc()
{
    while (! m_threadExit)
    {
        std::unique_lock<std::mutex> lock(m_dmaMutex);
        m_dmaCond.wait(lock);

        if (m_dmacon & GFXREG_DMACON_GOFLAG)
        {
            m_dmacon &= ~GFXREG_DMACON_GOFLAG;

            uint32_t words = (m_dmacon & GFXREG_DMACON_SIZE_MASK) >> GFXREG_DMACON_SIZE_SHIFT;

            uint32_t addrsrc = m_dmasrc & ~0x3UL;
            uint32_t addrdest = (m_dmadest & ~0x3UL) + USR_MEM_START;

            for (uint32_t i = 0; i < words; i++)
            {
                uint32_t w = m_sysbus->readMem(addrsrc);

                if (addrdest < GFX_MEM_SIZE)
                {
                    uint32_t* dst = reinterpret_cast<uint32_t*>(&m_gfxmem[addrdest]);
                    *dst = w;
                }

                addrsrc += 4;
                addrdest += 4;
            }

            m_nvic->assertIRQ(kGFXDMACON_IRQ, true);

        }
    }
}
