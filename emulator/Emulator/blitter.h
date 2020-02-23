#ifndef BLITTER_H
#define BLITTER_H

#include <stdint.h>

//
//  TODO: Depth buffer handling
//

void blt_Fill_32BPP(void* destBuffer, uint32_t destX, uint32_t destY, uint32_t w, uint32_t h, uint32_t fillCol, uint32_t depth);
void blt_Fill_8BPP(void* destBuffer, uint32_t destX, uint32_t destY,
                   uint32_t w, uint32_t h, uint8_t fillCol, uint32_t* palette, uint32_t depth);


void blt_Copy_8BPP_32BPP(void* src, void* destBuffer, uint32_t width, uint32_t rs, uint32_t height,
                            uint32_t destX, uint32_t destY, uint32_t* palette);

#endif // BLITTER_H
