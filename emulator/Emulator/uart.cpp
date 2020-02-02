#include "uart.h"

#include <stdio.h>

UART::UART()
{

}

uint32_t UART::readMem(uint32_t address)
{
    switch (address)
    {
        case 0x0:
            // TX FIFO
            return 0; // Always returns 0 when read
        case 0x4:
            // RX Fifo
            return 0;
    }
    return 0;
}

uint32_t UART::writeMem(uint32_t address, uint32_t value)
{
    switch (address)
    {
        case 0x0:
            // TX FIFO
            printf("%c", value & 0xff);
            fflush(0);
            break;
        case 0x4:
            // RX Fifo
            break;
    }

    return 0;
}
