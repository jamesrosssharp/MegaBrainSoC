#include "winbondflashmemory.h"

#include <iostream>
#include <fstream>

//
//  Emulate the winbond W25Q64JV
//

WinBondFlashMemory::WinBondFlashMemory()
{

    m_memory.resize(8*1024*1024); // Flash is

    std::ifstream from;

    from.open("../../code/FlashROM/main.bin", std::ios::binary);

    if (!from.is_open())
    {
        throw std::runtime_error("Cannot open Flash ROM!");
    }

    uint32_t i = 0;
    while (! from.eof())
    {
        uint8_t byte;
        from.read(reinterpret_cast<char*>(&byte), 1);
        m_memory[i++] = byte;
    }

}

WinBondFlashMemory::~WinBondFlashMemory()
{

}

void WinBondFlashMemory::assertChipSelect(bool assert)
{

    if (assert)
        m_state = State::kIDLE;

    m_chipSelect = !assert;
}

void WinBondFlashMemory::transceive(uint8_t send, uint8_t* receive)
{

    if (! m_chipSelect)
    {
        switch(m_state)
        {
            case State::kIDLE:

                switch(send)
                {
                    case 0x9f:
                        m_state = State::kREAD_JEDEC_ID;
                        m_count = 0;
                        break;
                    case 0x03:
                        m_state = State::kREAD_DATA;
                        m_count = 0;
                        break;
                }

                break;
            case State::kREAD_JEDEC_ID:

                switch (m_count++)
                {
                    case 0:
                        *receive = 0xef;
                        break;
                    case 1:
                        *receive = 0x40;
                        break;
                    case 2:
                        *receive = 0x17;
                        break;
                    default:
                        *receive = 0x00;
                }

                break;
            case State::kREAD_DATA:


                switch (m_count++)
                {
                    case 0:
                        m_readAddr = 0;
                        m_readAddr |= send;
                        break;
                    case 1:
                        m_readAddr <<= 8;
                        m_readAddr |= send;
                        break;
                    case 2:
                        m_readAddr <<= 8;
                        m_readAddr |= send;
                        break;
                    default:
                        printf("Winbnd read: %x\n", m_readAddr);
                        *receive = m_memory.at(m_readAddr & 0x07fffff);
                        m_readAddr++;
                        break;
                }

                break;
        }
    }

}


