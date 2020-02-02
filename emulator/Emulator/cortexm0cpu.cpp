#include "cortexm0cpu.h"
#include "thumbinstructions.h"
#include "megabrain.h"

#include <exception>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>

CortexM0CPU::CortexM0CPU(MegaBrain* brain)  :
    m_bus(nullptr),
    m_brain(brain)
{
    reset();
}

void CortexM0CPU::reset()
{
    for (int i = 0; i < kNRegs; i++)
        m_registers[i] = 0;

    m_flagC = false;
    m_flagN = false;
    m_flagV = false;
    m_flagZ = false;
}

void CortexM0CPU::registerSystemBus(SystemBus* bus)
{
    m_bus = bus;
}

uint16_t CortexM0CPU::readWordFromBus(uint32_t addr)
{

    if (addr & 1)   // TODO: handle this case with appropriate machine exception
        throw std::runtime_error("Unaligned access while fetching instruction!");

    uint32_t dword = m_bus->readMem(addr & ~0x3U);

    if (addr & 2)
    {
        return (dword >> 16);
    }
    else {
        return (dword & 0xffff);
    }

}

uint8_t CortexM0CPU::readByteFromBus(uint32_t addr)
{
    uint32_t dword = m_bus->readMem(addr & ~0x3U);

    switch (addr & 3)
    {
        case 0:
            return (dword & 0xff);
        case 1:
            return ((dword >> 8) & 0xff);
        case 2:
            return ((dword >> 16) & 0xff);
        case 3:
            return ((dword >> 24) & 0xff);
    }
    return 0;
}

void     CortexM0CPU::writeWordToBus(uint32_t addr, uint16_t word)
{

    uint32_t dword = m_bus->readMem(addr & ~0x3U);

    if (addr & 2)
    {
        dword &= 0x0000ffff;
        dword |= static_cast<uint32_t>(word) << 16;

        m_bus->writeMem(addr & ~0x3U, dword);
    }
    else {
        dword &= 0xffff0000;
        dword |= word;

        m_bus->writeMem(addr & ~0x3U, dword);
    }
}

void     CortexM0CPU::writeByteToBus(uint32_t addr, uint8_t byte)
{
    uint32_t dword = m_bus->readMem(addr & ~0x3U);

    switch (addr & 3)
    {
        case 0:
        {
            dword &= 0xffffff00;
            dword |= static_cast<uint32_t>(byte);

            m_bus->writeMem(addr & ~0x3U, dword);
            break;
        }
        case 1:
        {
            dword &= 0xffff00ff;
            dword |= static_cast<uint32_t>(byte) << 8;

            m_bus->writeMem(addr & ~0x3U, dword);
            break;
        }
        case 2:
        {
            dword &= 0xff00ffff;
            dword |= static_cast<uint32_t>(byte) << 16;

            m_bus->writeMem(addr & ~0x3U, dword);
            break;
        }
        case 3:
        {
            dword &= 0x00ffffff;
            dword |= static_cast<uint32_t>(byte) << 24;

            m_bus->writeMem(addr & ~0x3U, dword);
            break;
        }
    }
}

void CortexM0CPU::clockTick()
{
    if (m_bus == nullptr)
        throw std::runtime_error("Bus not initialised!");

    // Fetch instruction.

    uint16_t thumbInstruction = readWordFromBus(m_registers[kPC]);

    m_cyclesWait = 0;
    uint32_t pc = m_registers[kPC];

    // Decode and execute instruction.

    //std::cout << "Thumb instruction: " << std::hex << thumbInstruction << std::endl;

    if (0){
       // disas
        uint16_t thumbInstruction2 = readWordFromBus(pc + 2);

        std::cout << disassembleInstructionHelper(thumbInstruction, thumbInstruction2) << std::endl;
    }

    m_registers[kPC] += 2;
    decodeAndExecute(thumbInstruction);

    //printRegisters();
}

void CortexM0CPU::decodeAndExecute(uint16_t thumbInstruction)
{
    if (!decodeInstructionHelper(thumbInstruction))
        printf("Could not decode instruction %04x\n", thumbInstruction);


}

std::string CortexM0CPU::dumpRegisters()
{
    std::stringstream ss;

    for (int i = 0; i < 8; i++)
        ss << "r" << i << "=" << std::hex << m_registers[i] << " " << std::dec;
    ss << std::endl;
    for (int i = 8; i < 16; i++)
        ss << "r" << i << "=" << std::hex << m_registers[i] << " " << std::dec;
    ss << std::endl;
    ss << "Z = " << m_flagZ << " C = " << m_flagC << " V = " << m_flagV << " N = " << m_flagN << std::endl;

    return ss.str();

}

std::string CortexM0CPU::dumpDisas()
{
    std::stringstream ss;

    for (uint32_t pc = static_cast<uint32_t>(std::max(0, static_cast<int>(m_registers[kPC]) - 2*7)); pc < m_registers[kPC] + 2*7; pc += 2)
    {
        uint16_t thumbInstruction = readWordFromBus(pc);
        uint16_t thumbInstruction2 = readWordFromBus(pc + 2);

        if (pc == m_registers[kPC])
            ss << "==>";
        else
            ss << "   ";

        ss << std::hex << std::setw(6) << std::setfill('0') << (pc << 1) << ":\t";
        ss << std::hex << std::setw(4) << std::setfill('0') << thumbInstruction << "\t";

        ss << disassembleInstructionHelper(thumbInstruction, thumbInstruction2) << std::endl;

    }

    return ss.str();
}


void CortexM0CPU::printRegisters()
{
    for (int i = 0; i < 8; i++)
        printf("r%d=%08x (%d) ", i, m_registers[i], m_registers[i]);
    printf("\n");
    for (int i = 8; i < 16; i++)
        printf("r%d=%08x (%d) ", i, m_registers[i], m_registers[i]);
    printf("Z = %d C = %d V = %d N = %d\n", m_flagZ, m_flagC, m_flagV, m_flagN);
    printf("\n\n");
    fflush(nullptr);
}

// Macros for extracting data

#define IMM8 uint32_t imm8 = (thumbInstruction & 0x00ff);

#define RD_IMM8 uint16_t rd = (thumbInstruction & 0x0700) >> 8; \
    uint32_t imm8 = (thumbInstruction & 0x00ff);

#define RD_RM uint16_t rm = (thumbInstruction & 0x0038) >> 3; \
    uint32_t rd = (thumbInstruction & 0x0007);

#define RD_RM_EXT uint16_t rm = (thumbInstruction & 0x0078) >> 3; \
    uint32_t rd = (thumbInstruction & 0x0007) | ((thumbInstruction & 0x0080) >> 4);

#define RD_RN_IMM uint16_t rn = (thumbInstruction & 0x0038) >> 3; \
    uint32_t rd = (thumbInstruction & 0x0007);\
    uint32_t imm3 = (thumbInstruction & 0x00e0) >> 6;

#define RD_RM_IMM5 uint16_t rm = (thumbInstruction & 0x0038) >> 3; \
    uint32_t rd = (thumbInstruction & 0x0007);\
    uint32_t imm5 = (thumbInstruction & 0x07c0) >> 6;

#define RD_RM_RN uint16_t rm = (thumbInstruction & 0x01c0) >> 7;\
    uint16_t rn = (thumbInstruction & 0x0038) >> 3; \
    uint32_t rd = (thumbInstruction & 0x0007);

#define IMM7 uint16_t imm7 = (thumbInstruction & 0x007f);

#define IMM11 int16_t imm11 = (thumbInstruction & 0x07ff); \
    if (imm11 & 0x400)  \
        imm11 |= (0xfffff800);

#define COND_IMM8 uint16_t cond = (thumbInstruction & 0x0f00) >> 8; \
    int32_t imm8 = static_cast<int8_t>(thumbInstruction & 0x00ff);

#define FETCH32_BIT_INSTRUCTION \
        uint16_t thumbInstruction2 = readWordFromBus(m_registers[kPC]); \
        m_registers[kPC] += 2; \
        m_cyclesWait ++;

// Individual decode functions

//-----------------------------------------------------------------------
// 1. MOVS Rd, #<imm>

void CortexM0CPU::decode_movs_rd_imm_(uint16_t thumbInstruction)
{
    RD_IMM8

    m_registers[rd] = imm8;
    m_flagZ = (imm8 == 0);
}

std::string CortexM0CPU::disas_movs_rd_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    RD_IMM8

    (void) thumbInstruction2;

    std::stringstream ss;
    ss << "MOVS r" << rd << ",#" << imm8;
    return ss.str();
}

//-----------------------------------------------------------------------
// 2. MOVS Rd, Rm

void CortexM0CPU::decode_movs_rd_rm(uint16_t thumbInstruction)
{
    RD_RM
    uint32_t val = m_registers[rm];
    m_flagZ = (val == 0);
    m_flagN = !!(val & (1UL<<31));
    m_registers[rd] = val;
}

std::string CortexM0CPU::disas_movs_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;

    RD_RM
    std::stringstream ss;
    ss << "MOVS r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 3. MOV Rd, Rm

void CortexM0CPU::decode_mov_rd_rm(uint16_t thumbInstruction)
{
    RD_RM_EXT
    uint32_t val = m_registers[rm];
    m_registers[rd] = val;
}

std::string CortexM0CPU::disas_mov_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;

    RD_RM_EXT
    std::stringstream ss;
    ss << "MOV r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 4. MOV PC, Rm

void CortexM0CPU:: decode_mov_pc_rm(uint16_t thumbInstruction)
{
    (void)thumbInstruction;
    printf("Should not get here!\n");
}

std::string CortexM0CPU::disas_mov_pc_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;

    (void)thumbInstruction;
    printf("Should not get here! disas!\n");
    return "";
}

//-----------------------------------------------------------------------
// 5. ADDS Rd, Rn, #<imm>

static void performAdd(uint32_t op1, uint32_t op2,
                       bool carry,
                       bool& carryOut, bool&overflowOut, bool& zout, bool& nout, uint32_t& sumOut)
{
    uint64_t usum = op1 + op2 +
                (carry ? 1UL : 0UL);
    int64_t isum = static_cast<int32_t>(op1) + static_cast<int32_t>(op2) +
                (carry ? 1L : 0L);

    sumOut      = static_cast<uint32_t>(usum);
    carryOut    = (static_cast<uint32_t>(sumOut) == usum) ? 0 : 1;
    overflowOut = (static_cast<int32_t>(sumOut) == isum) ? 0 : 1;
    zout = (sumOut == 0);
    nout = sumOut & (1UL << 31);
}

void CortexM0CPU:: decode_adds_rd_rn_imm_(uint16_t thumbInstruction)
{
    RD_RN_IMM
    uint32_t op1 = m_registers[rn];
    uint32_t op2 = imm3;
    uint32_t sum;

    performAdd(op1, op2, false, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;
}

std::string CortexM0CPU::disas_adds_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;


    RD_RN_IMM
    std::stringstream ss;
    ss << "ADDS r" << rd << ", r" << rn << ", #" << imm3;
    return ss.str();
}

//-----------------------------------------------------------------------
// 6. ADDS Rd, Rn, Rm

void CortexM0CPU:: decode_adds_rd_rn_rm(uint16_t thumbInstruction)
{
    RD_RM_RN
    uint32_t op1 = m_registers[rn];
    uint32_t op2 = m_registers[rm];
    uint32_t sum;

    performAdd(op1, op2, false, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;
}

std::string CortexM0CPU::disas_adds_rd_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;

    RD_RM_RN
    std::stringstream ss;
    ss << "ADDS r" << rd << ", r" << rn << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 7. ADD Rd, Rd, Rm

void CortexM0CPU:: decode_add_rd_rd_rm(uint16_t thumbInstruction)
{
    RD_RM_EXT
    uint32_t op1 = m_registers[rd];
    uint32_t op2 = m_registers[rm];
    uint32_t sum;

    bool dummy1, dummy2, dummy3, dummy4;

    performAdd(op1, op2, false, dummy1, dummy2, dummy3, dummy4, sum);

    m_registers[rd] = sum;
}

std::string CortexM0CPU::disas_add_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_EXT
    std::stringstream ss;
    ss << "ADD r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 8. ADD PC, PC, Rm

void CortexM0CPU:: decode_add_pc_pc_rm(uint16_t thumbInstruction)
{
    (void)thumbInstruction;
    printf("Not implemented!\n");
}

std::string CortexM0CPU::disas_add_pc_pc_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    (void)thumbInstruction;
    printf("Not implemented!\n");
    return "";
}

//-----------------------------------------------------------------------
// 9. ADDS Rd, Rd, #<imm>

void CortexM0CPU:: decode_adds_rd_rd_imm_(uint16_t thumbInstruction)
{
    RD_IMM8
    uint32_t op1 = m_registers[rd];
    uint32_t op2 = imm8;
    uint32_t sum;

    performAdd(op1, op2, false, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;
}

std::string CortexM0CPU::disas_adds_rd_rd_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8
    std::stringstream ss;
    ss << "ADD r" << rd << ", #" << imm8;
    return ss.str();
}

//-----------------------------------------------------------------------
// 10. ADCS Rd, Rd, Rm

void CortexM0CPU:: decode_adcs_rd_rd_rm(uint16_t thumbInstruction)
{
    RD_RM
    uint32_t op1 = m_registers[rd];
    uint32_t op2 = m_registers[rm];
    uint32_t sum;

    performAdd(op1, op2, m_flagC, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;

}

std::string CortexM0CPU::disas_adcs_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "ADCS r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 11. ADD SP, SP, #<imm>

void CortexM0CPU:: decode_add_sp_sp_imm_(uint16_t thumbInstruction)
{
    IMM7

    uint32_t res = m_registers[kSP] + (imm7 << 2);
    m_registers[kSP] = res;
}

std::string CortexM0CPU::disas_add_sp_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    IMM7
    std::stringstream ss;
    ss << "ADD sp, #" << (imm7 << 2);
    return ss.str();
}

//-----------------------------------------------------------------------
// 12. ADD Rd, SP, #<imm>

void CortexM0CPU:: decode_add_rd_sp_imm_(uint16_t thumbInstruction)
{
    RD_IMM8
    uint32_t res = m_registers[kSP] + imm8;
    m_registers[rd] = res;
}

std::string CortexM0CPU::disas_add_rd_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8
    std::stringstream ss;
    ss << "ADD r" << rd << ",SP, #" << imm8;
    return ss.str();
}

//-----------------------------------------------------------------------
// 13.
// ADR Rd, <label>

void CortexM0CPU:: decode_adr_rd_label_(uint16_t thumbInstruction)
{
    RD_IMM8
    uint32_t res = (m_registers[kPC] & 0xfffc) + imm8;
    m_registers[rd] = res;
}

std::string CortexM0CPU::disas_adr_rd_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8
    std::stringstream ss;
    ss << "ADR r" << rd << ", PC, #" << imm8;
    return ss.str();
}

//-----------------------------------------------------------------------
// 14.
// SUBS Rd, Rn, Rm

void CortexM0CPU:: decode_subs_rd_rn_rm(uint16_t thumbInstruction)
{
    RD_RM_RN
    uint32_t op1 = m_registers[rm];
    uint32_t op2 = ~m_registers[rn];
    uint32_t sum;

    performAdd(op1, op2, true, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;

}

std::string CortexM0CPU::disas_subs_rd_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN
    std::stringstream ss;
    ss << "ADDS r" << rd << ", r" << rn << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 15.
// SUBS Rd, Rn, #<imm>

void CortexM0CPU:: decode_subs_rd_rn_imm_(uint16_t thumbInstruction)
{
    RD_RN_IMM
    uint32_t op1 = m_registers[rn];
    uint32_t op2 = ~imm3;
    uint32_t sum;

    performAdd(op1, op2, true, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;

}

std::string CortexM0CPU::disas_subs_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RN_IMM
    std::stringstream ss;
    ss << "SUBS r" << rd << ", r" << rn << ", #" << imm3;
    return ss.str();
}

//-----------------------------------------------------------------------
// 16.
// SUBS Rd, Rd, #<imm>

void CortexM0CPU:: decode_subs_rd_rd_imm_(uint16_t thumbInstruction)
{
    RD_IMM8
    uint32_t op1 = m_registers[rd];
    uint32_t op2 = ~imm8;
    uint32_t sum;

    performAdd(op1, op2, true, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;
}

std::string CortexM0CPU::disas_subs_rd_rd_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8
    std::stringstream ss;
    ss << "SUB r" << rd << ", #" << imm8;
    return ss.str();
}

//-----------------------------------------------------------------------
// 17.
// SBCS Rd, Rd, Rm

void CortexM0CPU:: decode_sbcs_rd_rd_rm(uint16_t thumbInstruction)
{
    RD_RM
    uint32_t op1 = m_registers[rd];
    uint32_t op2 = ~m_registers[rm];
    uint32_t sum;

    performAdd(op1, op2, !m_flagC, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;
}

std::string CortexM0CPU::disas_sbcs_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "SBCS r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 18.
// SUB SP, SP, #<imm>

void CortexM0CPU:: decode_sub_sp_sp_imm_(uint16_t thumbInstruction)
{
    IMM7

    uint32_t res = m_registers[kSP] - (static_cast<uint32_t>(imm7) << 2UL);
    m_registers[kSP] = res;
}

std::string CortexM0CPU::disas_sub_sp_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    IMM7
    std::stringstream ss;
    ss << "SUB sp, #" << (static_cast<uint32_t>(imm7) << 2);
    return ss.str();
}

//-----------------------------------------------------------------------
// 19.
// RSBS Rd, Rn, #0

void CortexM0CPU:: decode_rsbs_rd_rn_0(uint16_t thumbInstruction)
{
    RD_RM
    uint32_t op1 = ~m_registers[rm];
    uint32_t op2 = 0;
    uint32_t sum;

    performAdd(op1, op2, true, m_flagC, m_flagV, m_flagZ, m_flagN, sum);

    m_registers[rd] = sum;
}

std::string CortexM0CPU::disas_rsbs_rd_rn_0(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "RSBS r" << rd << " ,r" << rm << ", #0";
    return ss.str();
}

//-----------------------------------------------------------------------
// 20.
// MULS Rd, Rm, Rd

void CortexM0CPU:: decode_muls_rd_rm_rd(uint16_t thumbInstruction)
{
    RD_RM
    uint32_t result = m_registers[rd] * m_registers[rm];

    m_flagN = result & (1UL << 31);
    m_flagZ = (result == 0);

    m_registers[rd] = result;
}

std::string CortexM0CPU::disas_muls_rd_rm_rd(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "MULS r" << rd << " ,r" << rm << ", r" << rd;
    return ss.str();
}

//-----------------------------------------------------------------------
// 21.
// CMP Rn, Rm

void CortexM0CPU:: decode_cmp_rn_rm(uint16_t thumbInstruction)
{
    RD_RM
    uint32_t op1 = m_registers[rd];
    uint32_t op2 = ~m_registers[rm];
    uint32_t sum;

    performAdd(op1, op2, true, m_flagC, m_flagV, m_flagZ, m_flagN, sum);
}

std::string CortexM0CPU::disas_cmp_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "CMP r" << rd << " ,r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 22.
// CMN Rn, Rm

void CortexM0CPU:: decode_cmn_rn_rm(uint16_t thumbInstruction)
{
    RD_RM
    uint32_t op1 = m_registers[rd];
    uint32_t op2 = m_registers[rm];
    uint32_t sum;

    performAdd(op1, op2, false, m_flagC, m_flagV, m_flagZ, m_flagN, sum);
}

std::string CortexM0CPU::disas_cmn_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "CMP r" << rd << " ,r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 23.
// CMP Rn, #<imm>

void CortexM0CPU:: decode_cmp_rn_imm_(uint16_t thumbInstruction)
{
    RD_IMM8
    uint32_t op1 = m_registers[rd];
    uint32_t op2 = ~imm8;
    uint32_t sum;

    performAdd(op1, op2, true, m_flagC, m_flagV, m_flagZ, m_flagN, sum);
}

std::string CortexM0CPU::disas_cmp_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8
    std::stringstream ss;
    ss << "CMP r" << rd << ", #" << imm8;
    return ss.str();
}

//-----------------------------------------------------------------------
// 24.
// ANDS Rd, Rd, Rm

void CortexM0CPU:: decode_ands_rd_rd_rm(uint16_t thumbInstruction)
{
    RD_RM

    uint32_t res = m_registers[rd] & m_registers[rm];

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    // Carry?

    m_registers[rd] = res;

}

std::string CortexM0CPU::disas_ands_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "ANDS r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 25.
// EORS Rd, Rd, Rm

void CortexM0CPU:: decode_eors_rd_rd_rm(uint16_t thumbInstruction)
{
    RD_RM

    uint32_t res = m_registers[rd] ^ m_registers[rm];

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    // Carry?

    m_registers[rd] = res;
}

std::string CortexM0CPU::disas_eors_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "EORS r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 26.
// ORRS Rd, Rd, Rm

void CortexM0CPU:: decode_orrs_rd_rd_rm(uint16_t thumbInstruction)
{
    RD_RM

    uint32_t res = m_registers[rd] | m_registers[rm];

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    // Carry?

    m_registers[rd] = res;
}

std::string CortexM0CPU::disas_orrs_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "ORRS r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 27.
// BICS Rd, Rd, Rm

void CortexM0CPU:: decode_bics_rd_rd_rm(uint16_t thumbInstruction)
{
    RD_RM

    uint32_t res = m_registers[rd] & (~m_registers[rm]);

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    // Carry?

    m_registers[rd] = res;
}

std::string CortexM0CPU::disas_bics_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "BICS r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 28.
// MVNS Rd, Rm

void CortexM0CPU:: decode_mvns_rd_rm(uint16_t thumbInstruction){
    RD_RM

    uint32_t res = (~m_registers[rm]);

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    // Carry?

    m_registers[rd] = res;
}

std::string CortexM0CPU::disas_mvns_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "MVNS r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 29.
// TST Rn, Rm

void CortexM0CPU:: decode_tst_rn_rm(uint16_t thumbInstruction)
{
    RD_RM

    uint32_t res = m_registers[rd] & m_registers[rm];

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    // Carry?

}

std::string CortexM0CPU::disas_tst_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "TST r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 30.
// LSLS Rd, Rm, #<shift>

void CortexM0CPU:: decode_lsls_rd_rm_shift_(uint16_t thumbInstruction)
{
    RD_RM_IMM5

    uint64_t res = m_registers[rm] << imm5;

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    m_flagC = (res & (1UL << 32));

    m_registers[rd] = static_cast<uint32_t>(res);
}

std::string CortexM0CPU::disas_lsls_rd_rm_shift_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5
    std::stringstream ss;
    ss << "LSLS r" << rd << ", r" << rm << ", #" << imm5;
    return ss.str();
}

//-----------------------------------------------------------------------
// 31.
// LSLS Rd, Rd, Rs


void CortexM0CPU:: decode_lsls_rd_rd_rs(uint16_t thumbInstruction)
{
    RD_RM

    uint64_t res = m_registers[rd] << (m_registers[rm] & 31);

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    m_flagC = (res & (1UL << 32));

    m_registers[rd] = static_cast<uint32_t>(res);
}

std::string CortexM0CPU::disas_lsls_rd_rd_rs(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "LSLS r" << rd << ", r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 32. LSRS Rd, Rm, #<shift>

void CortexM0CPU:: decode_lsrs_rd_rm_shift_(uint16_t thumbInstruction)
{
    RD_RM_IMM5

    uint32_t shift;
    if (imm5 == 0)
        shift = 32;
    else {
        shift = imm5;
    }

    uint64_t res = m_registers[rm] >> shift;

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    m_flagC = (m_registers[rm] & (1UL));

    m_registers[rd] = static_cast<uint32_t>(res);
}

std::string CortexM0CPU::disas_lsrs_rd_rm_shift_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5
    std::stringstream ss;
    ss << "LSRS r" << rd << ", r" << rm << ", #" << imm5;
    return ss.str();
}

//-----------------------------------------------------------------------
// 33. LSRS Rd, Rd, Rs

void CortexM0CPU:: decode_lsrs_rd_rd_rs(uint16_t thumbInstruction)
{
    RD_RM

    uint64_t res = m_registers[rd] >> (m_registers[rm] & 31);

    m_flagZ = (res == 0);
    m_flagN = (res & (1UL << 31));
    m_flagC = (m_registers[rm] & 1UL);

    m_registers[rd] = static_cast<uint32_t>(res);
}

std::string CortexM0CPU::disas_lsrs_rd_rd_rs(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "LSRS r" << rd << ", r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 34.
// ASRS Rd, Rm, #<shift>

void CortexM0CPU::decode_asrs_rd_rm_shift_(uint16_t thumbInstruction)
{
    RD_RM_IMM5

    uint32_t shift;
    if (imm5 == 0)
        shift = 32;
    else {
        shift = imm5;
    }

    int64_t res = static_cast<int64_t>(m_registers[rm]) >> shift;

    m_flagZ = (res == 0);
    m_flagN = (res & (1L << 31));
    m_flagC = (m_registers[rm] & (1UL));

    m_registers[rd] = static_cast<uint32_t>(res);
}

std::string CortexM0CPU::disas_asrs_rd_rm_shift_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5
    std::stringstream ss;
    ss << "ASRS r" << rd << ", r" << rm << ", #" << imm5;
    return ss.str();
}

//-----------------------------------------------------------------------
// 35.
// ASRS Rd, Rd, Rs

void CortexM0CPU::decode_asrs_rd_rd_rs(uint16_t thumbInstruction)
{
    RD_RM

    uint32_t shift = m_registers[rm] & 31;

    int64_t res = static_cast<int64_t>(m_registers[rd]) >> shift;

    m_flagZ = (res == 0);
    m_flagN = (res & (1L << 31));
    m_flagC = (m_registers[rm] & 1UL);

    m_registers[rd] = static_cast<uint32_t>(res);
}

std::string CortexM0CPU::disas_asrs_rd_rd_rs(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "ASRS r" << rd << ", r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 36.
// RORS Rd, Rd, Rs

void CortexM0CPU::decode_rors_rd_rd_rs(uint16_t thumbInstruction)
{
    RD_RM

    uint32_t shift = m_registers[rm];

    uint64_t res = (m_registers[rd] >> shift) |
                   (m_registers[rd] << (32 - shift));

    m_flagZ = (res == 0);
    m_flagN = (res & (1L << 31));
    m_flagC = (res & (1L << 31));

    m_registers[rd] = static_cast<uint32_t>(res);
}

std::string CortexM0CPU::disas_rors_rd_rd_rs(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM
    std::stringstream ss;
    ss << "RORS r" << rd << ", r" << rd << ", r" << rm;
    return ss.str();
}

//-----------------------------------------------------------------------
// 37.
// LDR Rd, [Rn, #<imm>]

void CortexM0CPU::decode_ldr_rd_rn_imm_(uint16_t thumbInstruction)
{
    RD_RM_IMM5

    uint32_t addr = m_registers[rm] + (imm5<<2);
    uint32_t word = m_bus->readMem(addr & ~0x3U);

    m_registers[rd] = word;
}

std::string CortexM0CPU::disas_ldr_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5

    std::stringstream ss;
    ss << "LDR r" << rd << ", [r" << rm << ", #" << (imm5<<2) << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 38.
// LDRH Rd, [Rn, #<imm>]

void CortexM0CPU::decode_ldrh_rd_rn_imm_(uint16_t thumbInstruction)
{
    RD_RM_IMM5

    uint32_t addr = m_registers[rm] + (imm5<<1);
    uint32_t word = readWordFromBus(addr);

    m_registers[rd] = word;
}

std::string CortexM0CPU::disas_ldrh_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5

    std::stringstream ss;
    ss << "LDRH r" << rd << ", [r" << rm << ", #" << (imm5<<1) << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 39.
// LDRB Rd, [Rn, #<imm>]

void CortexM0CPU::decode_ldrb_rd_rn_imm_(uint16_t thumbInstruction)
{
    RD_RM_IMM5

    uint32_t addr = m_registers[rm] + imm5;
    uint32_t word = readByteFromBus(addr);

    m_registers[rd] = word;
}

std::string CortexM0CPU::disas_ldrb_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5

    std::stringstream ss;
    ss << "LDRB r" << rd << ", [r" << rm << ", #" << imm5 << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 40.
// LDR Rd, [Rn, Rm]

void CortexM0CPU::decode_ldr_rd_rn_rm_(uint16_t thumbInstruction)
{
    RD_RM_RN

    uint32_t addr = m_registers[rm] + m_registers[rn];
    uint32_t word = m_bus->readMem(addr & ~0x3U);

    m_registers[rd] = word;

}

std::string CortexM0CPU::disas_ldr_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN

    std::stringstream ss;
    ss << "LDR r" << rd << ", [r" << rm << ", r" << rn << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 41.
// LDRH Rd, [Rn, Rm]

void CortexM0CPU::decode_ldrh_rd_rn_rm_(uint16_t thumbInstruction)
{
    RD_RM_RN

    uint32_t addr = m_registers[rm] + m_registers[rn];
    uint32_t word = readWordFromBus(addr);

    m_registers[rd] = word;
}

std::string CortexM0CPU::disas_ldrh_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN

    std::stringstream ss;
    ss << "LDRH r" << rd << ", [r" << rm << ", r" << rn << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 42.
// LDRSH Rd, [Rn, Rm]

void CortexM0CPU::decode_ldrsh_rd_rn_rm_(uint16_t thumbInstruction)
{
    RD_RM_RN

    uint32_t addr = m_registers[rm] + m_registers[rn];
    int32_t word = static_cast<int32_t>(readWordFromBus(addr));

    m_registers[rd] = static_cast<uint32_t>(word);
}

std::string CortexM0CPU::disas_ldrsh_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN

    std::stringstream ss;
    ss << "LDRSH r" << rd << ", [r" << rm << ", r" << rn << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 43.
// LDRB Rd, [Rn, Rm]

void CortexM0CPU:: decode_ldrb_rd_rn_rm_(uint16_t thumbInstruction)
{
    RD_RM_RN

    uint32_t addr = m_registers[rm] + m_registers[rn];
    uint32_t word = readByteFromBus(addr);

    m_registers[rd] = word;
}

std::string CortexM0CPU::disas_ldrb_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN

    std::stringstream ss;
    ss << "LDRB r" << rd << ", [r" << rm << ", r" << rn << "]";
    return ss.str();

}

//-----------------------------------------------------------------------
// 44.
// LDRSB Rd, [Rn, Rm]

void CortexM0CPU:: decode_ldrsb_rd_rn_rm_(uint16_t thumbInstruction)
{
    RD_RM_RN

    uint32_t addr = m_registers[rm] + m_registers[rn];
    int32_t word = static_cast<int8_t>(readByteFromBus(addr));

    m_registers[rd] = static_cast<uint32_t>(word);
}

std::string CortexM0CPU::disas_ldrsb_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN

    std::stringstream ss;
    ss << "LDRSB r" << rd << ", [r" << rm << ", r" << rn << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 45.
// LDR Rd, <label>


void CortexM0CPU:: decode_ldr_rd_label_(uint16_t thumbInstruction)
{
    RD_IMM8

    uint32_t addr = m_registers[kPC] + (imm8 << 2);
    uint32_t word = m_bus->readMem(addr & ~0x3U);
    m_registers[rd] = word;
}

std::string CortexM0CPU::disas_ldr_rd_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8

    std::stringstream ss;
    ss << "LDR r" << rd << ", [PC, #" << (imm8 << 2) << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 46.
// LDR Rd, [SP, #<imm>]

void CortexM0CPU:: decode_ldr_rd_sp_imm_(uint16_t thumbInstruction)
{
    RD_IMM8

    uint32_t addr = m_registers[kSP] + (imm8 << 2);
    uint32_t word = m_bus->readMem(addr & ~0x3U);
    m_registers[rd] = word;
}

std::string CortexM0CPU::disas_ldr_rd_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8

    std::stringstream ss;
    ss << "LDR r" << rd << ", [SP, #" << (imm8 << 2) << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 47.
// LDM Rn(!), {<loreglist>}

void CortexM0CPU:: decode_ldm_rn_loreglist_(uint16_t thumbInstruction)
{
    RD_IMM8

    uint32_t addr = m_registers[rd];

    for (int i = 0; i < 8; i ++)
    {
        if (imm8 & (1<<i))
        {
            m_registers[i] = m_bus->readMem(addr & ~0x3U);
            addr += 4;
            m_cyclesWait++;
        }
    }

    if (!(imm8 & (1<<rd)))
        m_registers[rd] = addr;
}

std::string CortexM0CPU::disas_ldm_rn_loreglist_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8

    std::stringstream ss;

    if (imm8 & (1<<rd))
        ss << "LDM r" << rd;
    else {
        ss << "LDM r" << rd << "!";
    }

    for (int i = 0; i < 8; i++)
        if (imm8 & (1<<i))
            ss << ", r" << i;

    return ss.str();
}

//-----------------------------------------------------------------------
// 48.
// STR Rd, [Rn, #<imm>]

void CortexM0CPU:: decode_str_rd_rn_imm_(uint16_t thumbInstruction)
{
    RD_RM_IMM5
    uint32_t address = m_registers[rm] + (imm5 << 2);

    m_bus->writeMem(address, m_registers[rd]);
}

std::string CortexM0CPU::disas_str_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5

    std::stringstream ss;
    ss << "STR r" << rd << ", [r" << rm << ", #" << (imm5<<2) << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 49.
// STRH Rd, [Rn, #<imm>]

void CortexM0CPU:: decode_strh_rd_rn_imm_(uint16_t thumbInstruction)
{
    RD_RM_IMM5
    uint32_t address = m_registers[rm] + (imm5 << 1);

    writeWordToBus(address, static_cast<uint16_t>(m_registers[rd] & 0xffff));
}

std::string CortexM0CPU::disas_strh_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5

    std::stringstream ss;
    ss << "STRH r" << rd << ", [r" << rm << ", #" << (imm5  << 1) << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 50.
// STRB Rd, [Rn, #<imm>]


void CortexM0CPU:: decode_strb_rd_rn_imm_(uint16_t thumbInstruction)
{
    RD_RM_IMM5
    uint32_t address = m_registers[rm] + imm5;

    writeByteToBus(address, static_cast<uint8_t>(m_registers[rd] & 0xff));
}

std::string CortexM0CPU::disas_strb_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_IMM5

    std::stringstream ss;
    ss << "STRB r" << rd << ", [r" << rm << ", #" << imm5 << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 51.
// STR Rd, [Rn, Rm]

void CortexM0CPU:: decode_str_rd_rn_rm_(uint16_t thumbInstruction)
{
    RD_RM_RN
    uint32_t address = m_registers[rm] + m_registers[rn];

    m_bus->writeMem(address, m_registers[rd]);
}

std::string CortexM0CPU::disas_str_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN

    std::stringstream ss;
    ss << "STR r" << rd << ", [r" << rm << ", r" << rn << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 52.
// STRH Rd, [Rn, Rm]

void CortexM0CPU:: decode_strh_rd_rn_rm_(uint16_t thumbInstruction)
{
    RD_RM_RN
    uint32_t address = m_registers[rm] + m_registers[rn];

    writeWordToBus(address, static_cast<uint16_t>(m_registers[rd] & 0xffff));

}

std::string CortexM0CPU::disas_strh_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN

    std::stringstream ss;
    ss << "STRH r" << rd << ", [r" << rm << ", r" << rn << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 53.
// STRB Rd, [Rn, Rm]

void CortexM0CPU:: decode_strb_rd_rn_rm_(uint16_t thumbInstruction)
{
    RD_RM_RN
    uint32_t address = m_registers[rm] + m_registers[rn];

    writeByteToBus(address, static_cast<uint8_t>(m_registers[rd] & 0xff));
}

std::string CortexM0CPU::disas_strb_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_RM_RN

    std::stringstream ss;
    ss << "STRB r" << rd << ", [r" << rm << ", r" << rn << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 54.
// STR Rd, [SP, #<imm>]

void CortexM0CPU:: decode_str_rd_sp_imm_(uint16_t thumbInstruction)
{
    RD_IMM8
    uint32_t address = m_registers[kSP] + imm8;

    m_bus->writeMem(address, m_registers[rd]);

}

std::string CortexM0CPU::disas_str_rd_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8

    std::stringstream ss;
    ss << "STR r" << rd << ", [SP, #" << imm8 << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 55.
// STM Rn!, {<loreglist>}

void CortexM0CPU:: decode_stm_rn_loreglist_(uint16_t thumbInstruction)
{
    RD_IMM8

    uint32_t addr = m_registers[rd];

    for (int i = 0; i < 8; i ++)
    {
        if (imm8 & (1<<i))
        {
            m_bus->writeMem(addr & ~0x3U, m_registers[i]);
            addr += 4;
            m_cyclesWait++;
        }
    }

    m_registers[rd] = addr;

}

std::string CortexM0CPU::disas_stm_rn_loreglist_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    RD_IMM8

    std::stringstream ss;

    ss << "STM r" << rd << "!";

    for (int i = 0; i < 8; i++)
        if (imm8 & (1<<i))
            ss << ", r" << i;

    return ss.str();
}

//-----------------------------------------------------------------------
// 56.
// PUSH {<loreglist>}

void CortexM0CPU:: decode_push_loreglist_(uint16_t thumbInstruction)
{
    IMM8

    uint32_t addr = m_registers[kSP];

    for (int i = 7; i >= 0; i --)
    {
        if (imm8 & (1<<i))
        {
            addr -= 4;
            m_bus->writeMem(addr & ~0x3U, m_registers[i]);
            m_cyclesWait++;
        }
    }

    m_registers[kSP] = addr;
}

std::string CortexM0CPU::disas_push_loreglist_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    IMM8

    std::stringstream ss;

    ss << "PUSH";

    for (int i = 0; i < 8; i++)
        if (imm8 & (1<<i))
        {
            if (i)
                ss << ", ";
            ss << "r" << i;
        }

    return ss.str();
}

//-----------------------------------------------------------------------
// 57.
// PUSH {<loreglist>, LR}

void CortexM0CPU:: decode_push_loreglist_lr_(uint16_t thumbInstruction)
{
    IMM8

    uint32_t addr = m_registers[kSP];

    addr -= 4;

    m_bus->writeMem(addr & ~0x3U, m_registers[kLR]);

    for (int i = 7; i >= 0; i --)
    {
        if (imm8 & (1<<i))
        {
            addr -= 4;
            m_bus->writeMem(addr & ~0x3U, m_registers[i]);
            m_cyclesWait++;
        }
    }

    m_registers[kSP] = addr;
}

std::string CortexM0CPU::disas_push_loreglist_lr_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    IMM8

    std::stringstream ss;

    ss << "PUSH";

    for (int i = 0; i < 8; i++)
        if (imm8 & (1<<i))
        {
            if (i)
                ss << ", ";
            ss << "r" << i;
        }

    ss << ", LR";

    return ss.str();
}

//-----------------------------------------------------------------------
// 58.

void CortexM0CPU:: decode_pop_loreglist_(uint16_t thumbInstruction)
{
    IMM8

    uint32_t addr = m_registers[kSP];

    for (int i = 0; i < 8; i ++)
    {
        if (imm8 & (1<<i))
        {
            m_registers[i] = m_bus->readMem(addr);
            addr += 4;
            m_cyclesWait++;
        }
    }

    m_registers[kSP] = addr;
}

std::string CortexM0CPU::disas_pop_loreglist_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    IMM8

    std::stringstream ss;

    ss << "POP";

    for (int i = 0; i < 8; i++)
        if (imm8 & (1<<i))
        {
            if (i)
                ss << ", ";
            ss << "r" << i;
        }

    return ss.str();
}

//-----------------------------------------------------------------------
// 59.

void CortexM0CPU:: decode_pop_loreglist_pc_(uint16_t thumbInstruction)
{
    IMM8

    uint32_t addr = m_registers[kSP];

    for (int i = 0; i < 8; i ++)
    {
        if (imm8 & (1<<i))
        {
            m_registers[i] = m_bus->readMem(addr);
            addr += 4;
            m_cyclesWait++;
        }
    }

    m_registers[kPC] = m_bus->readMem(addr);
    addr += 4;

    m_registers[kSP] = addr;

}

std::string CortexM0CPU::disas_pop_loreglist_pc_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    IMM8

    std::stringstream ss;

    ss << "POP";

    for (int i = 0; i < 8; i++)
        if (imm8 & (1<<i))
        {
            if (i)
                ss << ", ";
            ss << "r" << i;
        }

    ss << ", PC";

    return ss.str();
}

//-----------------------------------------------------------------------
// 60.
// B<cc> <label>

static bool branchTaken(uint16_t cond, bool C, bool V, bool Z, bool N)
{

    switch (cond)
    {
        //0000 EQ Equal Z == 1
        case 0:
            return Z;
        //0001 NE Not equal Z == 0
        case 1:
            return !Z;
        //0010 CS a Carry set C == 1
        case 2:
            return C;
        //0011 CC b Carry clear C == 0
        case 3:
            return !C;
        //0100 MI Minus, negative N == 1
        case 4:
            return N;
        //0101 PL Plus, positive or zero N == 0
        case 5:
            return !N;
        //0110 VS Overflow V == 1
        case 6:
            return V;
        //0111 VC No overflow V == 0
        case 7:
            return !V;
        //1000 HI Unsigned higher C == 1 and Z == 0
        case 8:
            return C && !Z;
        //1001 LS Unsigned lower or same C == 0 or Z == 1
        case 9:
            return !C && Z;
        //1010 GE Signed greater than or equal N == V
        case 10:
            return N == V;
        //1011 LT Signed less than N != V
        case 11:
            return N != V;
        //1100 GT Signed greater than Z == 0 and N == V
        case 12:
            return !Z && (N == V);
        //1101 LE Signed less than or equal Z == 1 or N != V
        case 13:
            return Z || (N != V);
        //1110 c None ( AL ) d Always (unconditional) Any
        case 14:
            return true;
    }

    return false;
}

std::string getCondStr(uint32_t cc)
{
    switch (cc)
    {
        //0000 EQ Equal Z == 1
        case 0:
            return "EQ";
        //0001 NE Not equal Z == 0
        case 1:
            return "NE";
        //0010 CS a Carry set C == 1
        case 2:
            return "CS";
        //0011 CC b Carry clear C == 0
        case 3:
            return "CC";
        //0100 MI Minus, negative N == 1
        case 4:
            return "MI";
        //0101 PL Plus, positive or zero N == 0
        case 5:
            return "PL";
        //0110 VS Overflow V == 1
        case 6:
            return "VS";
        //0111 VC No overflow V == 0
        case 7:
            return "VC";
        //1000 HI Unsigned higher C == 1 and Z == 0
        case 8:
            return "HI";
        //1001 LS Unsigned lower or same C == 0 or Z == 1
        case 9:
            return "LS";
        //1010 GE Signed greater than or equal N == V
        case 10:
            return "GE";
        //1011 LT Signed less than N != V
        case 11:
            return "LT";
        //1100 GT Signed greater than Z == 0 and N == V
        case 12:
            return "GT";
        //1101 LE Signed less than or equal Z == 1 or N != V
        case 13:
            return "LE";
        //1110 c None ( AL ) d Always (unconditional) Any
        case 14:
            return "AL";
    }

    return "?";
}

void CortexM0CPU:: decode_b_cc_label_(uint16_t thumbInstruction)
{
    COND_IMM8

    int32_t addr = static_cast<int8_t>(imm8);
    addr <<= 1;

    if (addr < 0)
        addr += 2;

    if (branchTaken(cond, m_flagC, m_flagV, m_flagZ, m_flagN))
            m_registers[kPC] += static_cast<uint32_t>(addr);

}

std::string CortexM0CPU::disas_b_cc_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    COND_IMM8

    std::stringstream ss;
    ss << "B." << getCondStr(cond) << " [PC, #" << (imm8 << 1) << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 61.
// B <label>

void CortexM0CPU:: decode_b_label_(uint16_t thumbInstruction)
{
    IMM11


    int32_t address = static_cast<int32_t>(imm11) << 1;
    address += 2;

    m_registers[kPC] += static_cast<uint32_t>(address);

}

std::string CortexM0CPU::disas_b_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;
    IMM11

    std::stringstream ss;
    ss << "B" << " [PC, #" << (static_cast<int32_t>(imm11) << 1) << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 62.

void CortexM0CPU:: decode_bl_label_(uint16_t thumbInstruction)
{
    FETCH32_BIT_INSTRUCTION

    uint32_t S = (thumbInstruction & (1UL << 10)) >> 10;
    uint32_t J1 = (thumbInstruction2 & (1UL << 13)) >> 13;
    uint32_t J2 = (thumbInstruction2 & (1UL << 11)) >> 11;

    uint32_t I1 = (J1 ^ S) ? 0 : 1;
    uint32_t I2 = (J2 ^ S) ? 0 : 1;

    uint32_t imm10 = thumbInstruction & 0x3ff;
    uint32_t imm11 = thumbInstruction2 & 0x7ff;


    uint32_t address = (S << 24) | (I1 << 23) | (I2 << 22) | (imm10 << 12) | (imm11 << 1);


    if (S)
        address |= 0xfe00;

    int32_t offset = static_cast<int32_t>(address);

    m_registers[kLR] = m_registers[kPC];
    m_registers[kPC] += static_cast<uint32_t>(offset);

}

std::string CortexM0CPU::disas_bl_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    (void) thumbInstruction2;

    uint32_t S = (thumbInstruction & (1UL << 10)) >> 10;
    uint32_t J1 = (thumbInstruction2 & (1UL << 13)) >> 13;
    uint32_t J2 = (thumbInstruction2 & (1UL << 11)) >> 11;

    uint32_t I1 = (J1 ^ S) ? 0 : 1;
    uint32_t I2 = (J2 ^ S) ? 0 : 1;

    uint32_t imm10 = thumbInstruction & 0x3ff;
    uint32_t imm11 = thumbInstruction2 & 0x7ff;


    uint32_t address = (S << 24) | (I1 << 23) | (I2 << 22) | (imm10 << 12) | (imm11 << 1);

    if (S)
        address |= 0xfe00;

    int32_t offset = static_cast<int32_t>(address);

    std::stringstream ss;
    ss << "BX"  << " [PC, #" << offset << "]";
    return ss.str();
}

//-----------------------------------------------------------------------
// 63.

void CortexM0CPU:: decode_bx_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_bx_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 64.

void CortexM0CPU:: decode_blx_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_blx_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 65.

void CortexM0CPU:: decode_sxth_rd_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_sxth_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 66.

void CortexM0CPU:: decode_sxtb_rd_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_sxtb_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 67.

void CortexM0CPU:: decode_uxth_rd_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_uxth_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 68.

void CortexM0CPU:: decode_uxtb_rd_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_uxtb_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 69.

void CortexM0CPU:: decode_rev_rd_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_rev_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 70.

void CortexM0CPU:: decode_rev16_rd_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_rev16_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 71.

void CortexM0CPU:: decode_revsh_rd_rm(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_revsh_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 72.

void CortexM0CPU:: decode_svc_imm_(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_svc_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 73.

void CortexM0CPU:: decode_cpsid_i(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_cpsid_i(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 74.

void CortexM0CPU:: decode_cpsie_i(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_cpsie_i(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 75.

void CortexM0CPU:: decode_mrs_rd_specreg_(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_mrs_rd_specreg_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 76.

void CortexM0CPU:: decode_msr_specreg_rn(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_msr_specreg_rn(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 77.

void CortexM0CPU:: decode_bkpt_imm_(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_bkpt_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 78.

void CortexM0CPU:: decode_sev(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_sev(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 79.

void CortexM0CPU:: decode_wfe(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_wfe(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 80.

void CortexM0CPU:: decode_wfi(uint16_t thumbInstruction)
{
    m_brain->pause();
}

std::string CortexM0CPU::disas_wfi(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    std::stringstream ss;
    ss << "WFI";
    return ss.str();
}

//-----------------------------------------------------------------------
// 81.

void CortexM0CPU:: decode_yield_g_(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_yield_g_(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 82.

void CortexM0CPU:: decode_nop(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_nop(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 83.

void CortexM0CPU:: decode_isb(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_isb(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 84.

void CortexM0CPU:: decode_dmb(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_dmb(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------
// 85.

void CortexM0CPU:: decode_dsb(uint16_t thumbInstruction)
{

}

std::string CortexM0CPU::disas_dsb(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
    return "";

}

//-----------------------------------------------------------------------

