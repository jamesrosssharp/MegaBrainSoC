#ifndef MEGABRAIN_H
#define MEGABRAIN_H

#include "cortexm0cpu.h"
#include "rom.h"
#include "systembus.h"
#include "ddrcontroller.h"
#include "uart.h"
#include "sram.h"

#include <thread>
#include <mutex>
#include <condition_variable>

class MegaBrain
{
public:
    MegaBrain();
    ~MegaBrain();

    void start();
    void pause();

    void singleStep();
    std::string dumpRegisters();
    std::string dumpDisas();
    std::string dumpMemory(uint32_t address);

    void hardReset();

private:
    void threadFunc();

private:
    CortexM0CPU m_cpu;
    ROM m_rom;
    SystemBus m_bus;
    DDRController m_ddr;
    UART        m_uart;
    SRAM        m_sram;

    std::mutex m_mutex;
    std::condition_variable m_cond;

    volatile bool m_threadExit;
    bool m_pause;

    std::thread m_thread;
};

#endif // MEGABRAIN_H
