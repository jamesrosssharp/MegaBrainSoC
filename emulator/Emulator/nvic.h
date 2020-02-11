#ifndef NVIC_H
#define NVIC_H

#include "peripheral.h"

class CortexM0CPU;

class NVIC : public Peripheral
{
public:
    NVIC(CortexM0CPU* cpu);

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

    // Called by peripherals on their external IRQs to signal interrupt. 32 external interrupts supported by cortex-m0 plus.
    void assertIRQ(uint32_t IRQ, bool assert);

    uint32_t pendingInterrupt();

private:
    CortexM0CPU* m_cpu;

    uint32_t m_intEnable;
    uint32_t m_intPending;

};

#endif // NVIC_H
