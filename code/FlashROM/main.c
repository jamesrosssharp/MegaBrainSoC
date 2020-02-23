#include <stdint.h>

#include "vectors.h"

#include "Assets/MegaBrain3_asset.h"

void uartputc(char c);
void uartputs(char* string);
void uartputint(uint32_t theInt);
void uartputbyte(uint8_t theByte);

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


void main()
{
    uartputs("Hello world!\n");

    uint32_t* nvic_ISER = (uint32_t*)0xE000E100;
    uint8_t* gfxbase = (uint8_t*)0x10010000; // uint8_t so we can add byte pointers

    // Set palette
    for (int i =0 ; i < 256; i++)
        *(volatile uint32_t*)(gfxbase + (0x300) + (i<<2)) = MegaBrain3_palette[i];

    // Register interrupts with NVIC

    *nvic_ISER = (uint32_t)0x0eUL;
    
    // Clear screen

    *(volatile uint32_t*)(gfxbase + GFXREG_BLTDESTXY)  = 0x0;
    *(volatile  uint32_t*)(gfxbase + GFXREG_BLTSRCWH)   = (360 << 16) | (640);
    *(volatile uint32_t*)(gfxbase + GFXREG_BLTFILLCOL) = 0x00;
    *(volatile uint32_t*)(gfxbase + GFXREG_BLTDEPTH)   = 0x00;

    *(gfxbase + GFXREG_BLTCON) = 0x00000009;

    __asm__ __volatile__ (
        "\twfi\n"
    );

    uartputs("Screen cleared!\n");
   
    // DMA gfx over to gfx ram

    *(volatile uint32_t*)(gfxbase + GFXREG_DMASRC) = (uint32_t)MegaBrain3_data;
    *(volatile uint32_t*)(gfxbase + GFXREG_DMADEST) = 0;
    *(volatile uint32_t*)(gfxbase + GFXREG_DMACON) = (MegaBrain3_width * MegaBrain3_height / 4) | 0x10000;

   __asm__ __volatile__ (
        "\twfi\n"
    );

    uartputs("DMA complete!\n");
  
    *(volatile uint32_t*)(gfxbase + GFXREG_BLTDESTXY)  = (128 << 16) | (64);
    *(volatile  uint32_t*)(gfxbase + GFXREG_BLTSRCWH)   = (MegaBrain3_height << 16) | (MegaBrain3_width);
    *(volatile uint32_t*)(gfxbase + GFXREG_BLTFILLCOL) = 0x00;
    *(volatile uint32_t*)(gfxbase + GFXREG_BLTDEPTH)   = 0x00;
    *(volatile uint32_t*)(gfxbase + GFXREG_BLTSRCADDR) = 0x00;
    *(volatile uint32_t*)(gfxbase + GFXREG_BLTSRCRS) = MegaBrain3_width;

    *(gfxbase + GFXREG_BLTCON) = 0x00000001;

 
    while (1);
}

__attribute__((naked)) void _start() {
    main();
}

void uartputc(char c)
{
    uint32_t* uartTx = (uint32_t*)0x10000000;

    *uartTx = c;
}

void uartputs(char* string)
{
    uint32_t* uartTx = (uint32_t*)0x10000000;

    while(*string)
        *uartTx = *(string++);

}

void uartputint(uint32_t theInt)
{
	static char convertBuffer[] = "0123456789abcdef";

    //uartputc('0');
    //uartputc('x');

    for (int i = 0; i < 8; i++)
    {
        uint8_t hex = (theInt >> ((7 - i)*4)) & 0x0f;
        uartputc(convertBuffer[hex]);
    }
}

void uartputbyte(uint8_t theByte)
{
	static char convertBuffer[] = "0123456789abcdef";

    //uartputc('0');
    //uartputc('x');

    for (int i = 0; i < 2; i++)
    {
        uint8_t hex = (theByte >> ((1 - i)*4)) & 0x0f;
        uartputc(convertBuffer[hex]);
    }
}



void spiIntHandler()
{
    uartputs("SPI Int\n");
}

void fbconHandler()
{
    uint32_t* nvic_ICPR = (uint32_t*)(0xE000E380);
    *nvic_ICPR = 0x2UL;
}

void bltConHandler()
{
    uint32_t* nvic_ICPR = (uint32_t*)(0xE000E380);
    *nvic_ICPR = 0x4UL;
}

void dmaConHandler()
{   
     uint32_t* nvic_ICPR = (uint32_t*)(0xE000E380);
    *nvic_ICPR = 0x8UL;
}

__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
   .pvStack = (void*)0x1100,
   .pfnReset_Handler = &_start, 
   .IRQ0_handler = &spiIntHandler,
   .IRQ1_handler = &fbconHandler,
   .IRQ2_handler = &bltConHandler,
   .IRQ3_handler = &dmaConHandler
};


