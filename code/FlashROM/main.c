#include <stdint.h>

#include "vectors.h"


void uartputc(char c);
void uartputs(char* string);
void uartputint(uint32_t theInt);
void uartputbyte(uint8_t theByte);

void main()
{
    uartputs("Hello world!\n");
    
    __asm__ __volatile__ (
        "\twfi\n"
    );

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

__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
   .pvStack = (void*)0x1100,
   .pfnReset_Handler = &_start, 
   .IRQ0_handler = &spiIntHandler
};


