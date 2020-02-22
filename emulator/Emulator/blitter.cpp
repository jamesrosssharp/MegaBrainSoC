#include "blitter.h"

#include <stdio.h>

#define SCR_WIDTH 640
#define SCR_HEIGHT 360

void blt_Fill_32BPP(void* destBuffer, uint32_t destX, uint32_t destY, uint32_t w, uint32_t h, uint32_t fillCol, uint32_t depth)
{
    (void) destBuffer;
    (void) destX;
    (void) destY;
    (void) w;
    (void) h;
    (void) fillCol;
    (void) depth;

    printf("Fill 32bpp\n");
}

void blt_Fill_8BPP(void* destBuffer, uint32_t destX, uint32_t destY,
                   uint32_t w, uint32_t h, uint8_t fillCol, uint32_t* palette, uint32_t depth)
{

    (void) depth;

    uint32_t col = palette[fillCol];
    uint32_t* dest = static_cast<uint32_t*>(static_cast<uint32_t*>(destBuffer) + destX + destY * SCR_WIDTH);
    uint32_t rowstride = SCR_WIDTH - w;

    for (uint32_t i = 0; i < h; i++)
    {
        for (uint32_t j = 0; j < w; j++)
            *dest++ = col;
        dest += rowstride;
    }

    fflush(nullptr);
}
