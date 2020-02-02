#ifndef DDRCONTROLLER_H
#define DDRCONTROLLER_H

#include "peripheral.h"
#include <vector>

class DDRController : public Peripheral
{
public:
    DDRController();

    virtual uint32_t readMem(uint32_t address);
    virtual uint32_t writeMem(uint32_t address, uint32_t value);

private:

    std::vector<uint32_t> m_memory;

};

#endif // DDRCONTROLLER_H
