#include <stdint.h>

#include "vectors.h"


void uartputc(char c);
void uartputs(char* string);
void uartputint(uint32_t theInt);
void uartputbyte(uint8_t theByte);

void main()
{
    uint32_t* nvic_ISER = (uint32_t*)0xE000E100;

    uint32_t* spi0 = (uint32_t*)0x10000100;

    uint8_t dmaPayload[8] = {0x9f, 0x00, 0x00, 0x00, 0x00};
    uint8_t dmaRx[8];
    uint8_t dmaPayload2[16] = {0x03, 0x00, 0x00, 0x00};
    uint8_t dmaRx2[16];

    *nvic_ISER = (uint32_t)0x1UL;

    *(uint32_t*)(spi0 + 1) = (uint32_t)dmaPayload;
    *(uint32_t*)(spi0 + 2) = (uint32_t)dmaRx;
    *(uint32_t*)(spi0) = 0x10000 | 5;

    // Halt CPU
    __asm__ __volatile__ (
        "\twfi\n"
    );

    uartputs("JEDEC ID:");
    for (int i = 0; i < 4; i++)
        uartputbyte(dmaRx[i+1]);

    *(uint32_t*)(spi0 + 1) = (uint32_t)dmaPayload2;
    *(uint32_t*)(spi0 + 2) = (uint32_t)dmaRx2;
    *(uint32_t*)(spi0) = 0x10000 | 16;

    __asm__ __volatile__ (
        "\twfi\n"
    );

    uartputs("Flash rom contents:");
    for (int i = 0; i < 4; i++)
        uartputbyte(dmaRx2[i+4]);

    __asm__ __volatile__ (
        "\twfi\n"
    );


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

__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
   .pvStack = (void*)0x1100,
   .pfnReset_Handler = &_start, 
   .IRQ0_handler = &spiIntHandler
};


