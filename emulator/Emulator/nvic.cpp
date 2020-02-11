#include "nvic.h"

#include "cortexm0cpu.h"

NVIC::NVIC(CortexM0CPU* cpu)    :
    m_cpu(cpu)
{
    m_intEnable = 0x0;
    m_intPending = 0x0; // To do: reset on CPU reset - system bus system wide reset?
}

uint32_t NVIC::readMem(uint32_t address)
{
    switch (address & ~3UL)
    {
        case 0x0:   // NVIC_ISER
            return m_intEnable;
        case 0x80: // NVIC_ICER
            return m_intEnable;
        case 0x100: // NVIC_ISPR
            return m_intPending;
        case 0x280: // NVIC_ICPR
            return m_intPending;
    }
}

uint32_t NVIC::writeMem(uint32_t address, uint32_t value)
{
    switch (address & ~3UL)
    {
        case 0x0:   // NVIC_ISER
            m_intEnable |= value;
            break;
        case 0x80: // NVIC_ICER
            m_intEnable &= ~value;
            break;
        case 0x100: // NVIC_ISPR
            m_intPending |= value;
            break;
        case 0x280: // NVIC_ICPR
            m_intPending &= ~value;
            break;
    }
    return 0;
}

void NVIC::assertIRQ(uint32_t IRQ, bool assert)
{
    // Assert external interupt. If any interrupt flags are masked in and pending, interrupt CPU

    if (assert)
        m_intPending |= (1<<IRQ);
    else {
        m_intPending &= ~(1<<IRQ);
    }

    if (m_intPending & m_intEnable)
        m_cpu->interrupt();
}

uint32_t NVIC::pendingInterrupt()
{
    for (uint32_t i = 0; i < 32; i++)
        if (m_intPending & (1<<i))
            return i;
    return static_cast<uint32_t>(-1);
}
