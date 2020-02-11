#ifndef WINBONDFLASHMEMORY_H
#define WINBONDFLASHMEMORY_H

#include "spidevice.h"

#include <vector>

class WinBondFlashMemory : public SPIDevice
{
public:
    WinBondFlashMemory();
    ~WinBondFlashMemory();

    virtual void assertChipSelect(bool assert);
    virtual void transceive(uint8_t send, uint8_t* receive);

private:

    enum class State {
      kIDLE = 0,
      kREAD_JEDEC_ID = 1,
      kREAD_DATA = 2
    };

    State m_state;

    std::vector<uint8_t> m_memory;

    bool  m_chipSelect;
    int   m_count;

    uint32_t m_readAddr;
};

#endif // WINBONDFLASHMEMORY_H
