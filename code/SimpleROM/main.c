#include <stdint.h>


void uartputc(char c);
void uartputs(char* string);
void uartputint(uint32_t theInt);

__attribute__((naked)) void _start() {

     __asm__ __volatile__ (
        "\tmovs r0, #0x11\n"
        "\tlsl  r1, r0, #8\n"
        "\tmov  r13, r1\n" 
    );

    uartputs("Hello world!\n");

    int a = 10;
    int b = 13;
    int c = 71;

    uartputint(a);
    uartputs(" * ");
    uartputint(b);
    uartputs(" + ");
    uartputint(c);
    uartputs(" = ");
    uartputint(a*b + c);
    uartputs("\n");

    int d = 12;
    int e = 3;
    int f = 5;

    uartputs("(12 << 3) - 5 = ");
    uartputint((d << e) - f);
    uartputs("\n");

    int g = 96;
    int h = 72;

    uartputs("96 - 72 = ");
    uartputint(g - h);
    uartputs("\n");

    int j = 65536;
    int k = 16792846;
    
    uartputs("65535 + 16792846 = ");
    uartputint(j + k);
    uartputs("\n");

    // Halt CPU
    __asm__ __volatile__ (
        "\twfi\n"
    );

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
