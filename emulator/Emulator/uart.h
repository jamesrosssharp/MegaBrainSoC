#ifndef UART_H
#define UART_H

#include "peripheral.h"

class UART : public Peripheral
{
public:
    UART();

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

};

#endif // UART_H
