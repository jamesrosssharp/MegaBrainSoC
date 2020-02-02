#include <stdint.h>


void uartputs(char* string);

__attribute__((naked)) void _start() {

     __asm__ __volatile__ (
        "\tmovs r0, #0x11\n"
        "\tlsl  r1, r0, #8\n"
        "\tmov  r13, r1\n" 
    );

    uartputs("Hello world!\n");

    // Halt CPU
    __asm__ __volatile__ (
        "\twfi\n"
    );

}

void uartputs(char* string)
{
    uint32_t* uartTx = (uint32_t*)0x10000000;

    while(*string)
        *uartTx = *(string++);

}


