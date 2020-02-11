#ifndef SYSCTL_H
#define SYSCTL_H

//
//  Cortex-M0+ System control block (SCB)
//
//

#include "peripheral.h"

class CortexM0CPU;

class SysCtl : public Peripheral
{
public:
    SysCtl(CortexM0CPU* cpu);

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

    uint32_t getVTOR() { return m_vtor; }
    void setVTOR(uint32_t vtor) { m_vtor = vtor; }

private:
    CortexM0CPU* m_cpu;

    uint32_t m_vtor;

};

#endif // SYSCTL_H
