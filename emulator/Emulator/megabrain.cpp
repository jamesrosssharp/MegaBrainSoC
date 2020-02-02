#include "megabrain.h"

#include <sstream>

#include <iomanip>

MegaBrain::MegaBrain()  :
    m_cpu(this),
    m_bus(&m_cpu, &m_rom, &m_ddr, &m_uart, &m_sram),
    m_threadExit(false),
    m_pause(true),
    m_thread([] (MegaBrain* mb) { mb->threadFunc(); }, this)
{
    m_cpu.registerSystemBus(&m_bus);
}

MegaBrain::~MegaBrain()
{
    m_threadExit = true;
    m_cond.notify_all();
    m_thread.join();
}

void MegaBrain::start()
{
    m_cond.notify_all();
}

void MegaBrain::pause()
{
    m_pause = true;

    if (m_cb)
        m_cb(m_cbdata);
}


void MegaBrain::threadFunc()
{


    while (! m_threadExit)
    {
        if (m_pause)
        {   // Wait until asked to start
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cond.wait(lock);
            m_pause = false;
        }

        m_cpu.clockTick();

        struct timespec tm1, tm2;

        tm1.tv_sec = 0 ; //1

       // tm1.tv_sec = 1;
        tm1.tv_nsec = 20;
        nanosleep(&tm1, &tm2);
    }
}


void MegaBrain::singleStep()
{
    m_cpu.clockTick();
}

std::string MegaBrain::dumpRegisters()
{
    return m_cpu.dumpRegisters();
}

std::string MegaBrain::dumpDisas()
{
    return m_cpu.dumpDisas();
}

std::string MegaBrain::dumpMemory(uint32_t address)
{
    address &= ~3UL;
    std::stringstream ss;

    for (uint32_t addr = address; addr < (address + 16*4);)
    {
       ss << std::hex << std::setw(8) << std::setfill('0') << addr << ":\t";
       for (int i = 0; i < 4; i++)
       {
           ss << std::hex << std::setw(8) << std::setfill('0') << m_bus.readMem(addr) << "\t";
           addr += 4;
       }
       ss << std::endl;
    }

    return ss.str();
}

void MegaBrain::hardReset()
{
    m_cpu.reset();
}

void MegaBrain::stepOver()
{
    m_cpu.setStepOver();
    start();
}
