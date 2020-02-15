#include "gfxcore.h"

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
 *      Reg 0x14    DMA Source (main mem)
 *      Reg 0x18    DMA Dest (gfx mem)
 *
 *  Blitter controller -
 *
 *      (Allows blits from user mem or backbuffer to backbuffer)
 *      Reg 0x20    Control reg
 *      Reg 0x24    Source w, h
 *      Reg 0x28    Source row stride
 *      Reg 0x30    Dest x,y - on current back buffer
 *      Reg 0x34    Source base addr
 *      Reg 0x38    Source x,y - on current back buffer (if applicable)
 *
 *  Sprite channel 0 - 31 : (0x40 - 0x23f)
 *
 *      TODO
 *
 */

// TODO Hardware reg description + include generation

#define GFXREG_FBCON    0x00

#define GFXREG_DMACON   0X10
#define GFXREG_DMASRC   0X14
#define GFXREG_DMADEST  0X18

#define GFXREG_BLTCON         0x20
#define GFXREG_BLTSRCWH       0x24
#define GFXREG_BLTSRCRS       0x28
#define GFXREG_BLTDESTXY      0x30
#define GFXREG_BLTSRCADDR     0x34
#define GFXREG_BLTSRCXY       0x38

GFXCore::GFXCore()
{

}

uint32_t GFXCore::readMem(uint32_t address)
{
    switch (address)
    {
        case GFXREG_FBCON:

            break;
        case GFXREG_DMACON:

            break;
        case GFXREG_DMASRC:

            break;
        case GFXREG_DMADEST:

            break;
        case GFXREG_BLTCON:

            break;
        case GFXREG_BLTSRCWH:

            break;
        case GFXREG_BLTSRCRS:

            break;
        case GFXREG_BLTDESTXY:

            break;
        case GFXREG_BLTSRCADDR:

            break;
        case GFXREG_BLTSRCXY:

            break;
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

            break;
        case GFXREG_DMASRC:

            break;
        case GFXREG_DMADEST:

            break;
        case GFXREG_BLTCON:

            break;
        case GFXREG_BLTSRCWH:

            break;
        case GFXREG_BLTSRCRS:

            break;
        case GFXREG_BLTDESTXY:

            break;
        case GFXREG_BLTSRCADDR:

            break;
        case GFXREG_BLTSRCXY:

            break;
    }

    return 0;
}

