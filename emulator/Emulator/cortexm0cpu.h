#ifndef CORTEXM0CPU_H
#define CORTEXM0CPU_H

#include "systembus.h"
#include <cstdint>

#include <string>

class MegaBrain;

class CortexM0CPU
{
public:
    CortexM0CPU(MegaBrain* brain);

    void registerSystemBus(SystemBus* bus);

    void clockTick();

    void reset();

    static constexpr int kNRegs = 16;

    static constexpr int kPC = 15;
    static constexpr int kLR = 14;
    static constexpr int kSP = 13;

    std::string dumpRegisters();
    std::string dumpDisas();

    void setStepOver();

private:

    uint16_t readWordFromBus(uint32_t address);
    uint8_t  readByteFromBus(uint32_t address);
    void     writeWordToBus(uint32_t address, uint16_t word);
    void     writeByteToBus(uint32_t address, uint8_t byte);
    void     decodeAndExecute(uint16_t thumbInstruction);

    bool     decodeInstructionHelper(uint16_t thumbInstruction);
    std::string disassembleInstructionHelper(uint16_t thumbInstruction, uint16_t thumbInstruction2);

    void printRegisters();

    void decode_movs_rd_imm_(uint16_t thumbInstruction);
    std::string disas_movs_rd_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void decode_movs_rd_rm(uint16_t thumbInstruction);
    std::string disas_movs_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void decode_mov_rd_rm(uint16_t thumbInstruction);
    std::string disas_mov_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_mov_pc_rm(uint16_t thumbInstruction);
    std::string disas_mov_pc_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_adds_rd_rn_imm_(uint16_t thumbInstruction);
    std::string disas_adds_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_adds_rd_rn_rm(uint16_t thumbInstruction);
    std::string disas_adds_rd_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_add_rd_rd_rm(uint16_t thumbInstruction);
    std::string disas_add_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_add_pc_pc_rm(uint16_t thumbInstruction);
    std::string disas_add_pc_pc_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_adds_rd_rd_imm_(uint16_t thumbInstruction);
    std::string disas_adds_rd_rd_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_adcs_rd_rd_rm(uint16_t thumbInstruction);
    std::string disas_adcs_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_add_sp_sp_imm_(uint16_t thumbInstruction);
    std::string disas_add_sp_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_add_rd_sp_imm_(uint16_t thumbInstruction);
    std::string disas_add_rd_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_adr_rd_label_(uint16_t thumbInstruction);
    std::string disas_adr_rd_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_subs_rd_rn_rm(uint16_t thumbInstruction);
    std::string disas_subs_rd_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_subs_rd_rn_imm_(uint16_t thumbInstruction);
    std::string disas_subs_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_subs_rd_rd_imm_(uint16_t thumbInstruction);
    std::string disas_subs_rd_rd_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_sbcs_rd_rd_rm(uint16_t thumbInstruction);
    std::string disas_sbcs_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_sub_sp_sp_imm_(uint16_t thumbInstruction);
    std::string disas_sub_sp_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_rsbs_rd_rn_0(uint16_t thumbInstruction);
    std::string disas_rsbs_rd_rn_0(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_muls_rd_rm_rd(uint16_t thumbInstruction);
    std::string disas_muls_rd_rm_rd(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_cmp_rn_rm(uint16_t thumbInstruction);
    std::string disas_cmp_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_cmn_rn_rm(uint16_t thumbInstruction);
    std::string disas_cmn_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_cmp_rn_imm_(uint16_t thumbInstruction);
    std::string disas_cmp_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ands_rd_rd_rm(uint16_t thumbInstruction);
    std::string disas_ands_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_eors_rd_rd_rm(uint16_t thumbInstruction);
    std::string disas_eors_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_orrs_rd_rd_rm(uint16_t thumbInstruction);
    std::string disas_orrs_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_bics_rd_rd_rm(uint16_t thumbInstruction);
    std::string disas_bics_rd_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_mvns_rd_rm(uint16_t thumbInstruction);
    std::string disas_mvns_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_tst_rn_rm(uint16_t thumbInstruction);
    std::string disas_tst_rn_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_lsls_rd_rm_shift_(uint16_t thumbInstruction);
    std::string disas_lsls_rd_rm_shift_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_lsls_rd_rd_rs(uint16_t thumbInstruction);
    std::string disas_lsls_rd_rd_rs(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_lsrs_rd_rm_shift_(uint16_t thumbInstruction);
    std::string disas_lsrs_rd_rm_shift_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_lsrs_rd_rd_rs(uint16_t thumbInstruction);
    std::string disas_lsrs_rd_rd_rs(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_asrs_rd_rm_shift_(uint16_t thumbInstruction);
    std::string disas_asrs_rd_rm_shift_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_asrs_rd_rd_rs(uint16_t thumbInstruction);
    std::string disas_asrs_rd_rd_rs(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_rors_rd_rd_rs(uint16_t thumbInstruction);
    std::string disas_rors_rd_rd_rs(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldr_rd_rn_imm_(uint16_t thumbInstruction);
    std::string disas_ldr_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldrh_rd_rn_imm_(uint16_t thumbInstruction);
    std::string disas_ldrh_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldrb_rd_rn_imm_(uint16_t thumbInstruction);
    std::string disas_ldrb_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldr_rd_rn_rm_(uint16_t thumbInstruction);
    std::string disas_ldr_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldrh_rd_rn_rm_(uint16_t thumbInstruction);
    std::string disas_ldrh_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldrsh_rd_rn_rm_(uint16_t thumbInstruction);
    std::string disas_ldrsh_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldrb_rd_rn_rm_(uint16_t thumbInstruction);
    std::string disas_ldrb_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldrsb_rd_rn_rm_(uint16_t thumbInstruction);
    std::string disas_ldrsb_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldr_rd_label_(uint16_t thumbInstruction);
    std::string disas_ldr_rd_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldr_rd_sp_imm_(uint16_t thumbInstruction);
    std::string disas_ldr_rd_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_ldm_rn_loreglist_(uint16_t thumbInstruction);
    std::string disas_ldm_rn_loreglist_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_str_rd_rn_imm_(uint16_t thumbInstruction);
    std::string disas_str_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_strh_rd_rn_imm_(uint16_t thumbInstruction);
    std::string disas_strh_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_strb_rd_rn_imm_(uint16_t thumbInstruction);
    std::string disas_strb_rd_rn_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_str_rd_rn_rm_(uint16_t thumbInstruction);
    std::string disas_str_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_strh_rd_rn_rm_(uint16_t thumbInstruction);
    std::string disas_strh_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_strb_rd_rn_rm_(uint16_t thumbInstruction);
    std::string disas_strb_rd_rn_rm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_str_rd_sp_imm_(uint16_t thumbInstruction);
    std::string disas_str_rd_sp_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_stm_rn_loreglist_(uint16_t thumbInstruction);
    std::string disas_stm_rn_loreglist_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_push_loreglist_(uint16_t thumbInstruction);
    std::string disas_push_loreglist_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_push_loreglist_lr_(uint16_t thumbInstruction);
    std::string disas_push_loreglist_lr_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_pop_loreglist_(uint16_t thumbInstruction);
    std::string disas_pop_loreglist_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_pop_loreglist_pc_(uint16_t thumbInstruction);
    std::string disas_pop_loreglist_pc_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_b_cc_label_(uint16_t thumbInstruction);
    std::string disas_b_cc_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_b_label_(uint16_t thumbInstruction);
    std::string disas_b_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_bl_label_(uint16_t thumbInstruction);
    std::string disas_bl_label_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_bx_rm(uint16_t thumbInstruction);
    std::string disas_bx_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_blx_rm(uint16_t thumbInstruction);
    std::string disas_blx_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_sxth_rd_rm(uint16_t thumbInstruction);
    std::string disas_sxth_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_sxtb_rd_rm(uint16_t thumbInstruction);
    std::string disas_sxtb_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_uxth_rd_rm(uint16_t thumbInstruction);
    std::string disas_uxth_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_uxtb_rd_rm(uint16_t thumbInstruction);
    std::string disas_uxtb_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_rev_rd_rm(uint16_t thumbInstruction);
    std::string disas_rev_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_rev16_rd_rm(uint16_t thumbInstruction);
    std::string disas_rev16_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_revsh_rd_rm(uint16_t thumbInstruction);
    std::string disas_revsh_rd_rm(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_svc_imm_(uint16_t thumbInstruction);
    std::string disas_svc_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_cpsid_i(uint16_t thumbInstruction);
    std::string disas_cpsid_i(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_cpsie_i(uint16_t thumbInstruction);
    std::string disas_cpsie_i(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_mrs_rd_specreg_(uint16_t thumbInstruction);
    std::string disas_mrs_rd_specreg_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_msr_specreg_rn(uint16_t thumbInstruction);
    std::string disas_msr_specreg_rn(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_bkpt_imm_(uint16_t thumbInstruction);
    std::string disas_bkpt_imm_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_sev(uint16_t thumbInstruction);
    std::string disas_sev(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_wfe(uint16_t thumbInstruction);
    std::string disas_wfe(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_wfi(uint16_t thumbInstruction);
    std::string disas_wfi(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_yield_g_(uint16_t thumbInstruction);
    std::string disas_yield_g_(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_nop(uint16_t thumbInstruction);
    std::string disas_nop(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_isb(uint16_t thumbInstruction);
    std::string disas_isb(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_dmb(uint16_t thumbInstruction);
    std::string disas_dmb(uint16_t thumbInstruction, uint16_t thumbInstruction2);
    void  decode_dsb(uint16_t thumbInstruction);
    std::string disas_dsb(uint16_t thumbInstruction, uint16_t thumbInstruction2);

private:

    SystemBus* m_bus;

    uint32_t m_registers[16];

    bool m_flagZ;
    bool m_flagC;
    bool m_flagN;
    bool m_flagV;

    uint32_t m_cyclesWait;

    MegaBrain* m_brain;

    uint32_t m_stepOverPC;

};

#endif // CORTEXM0CPU_H
