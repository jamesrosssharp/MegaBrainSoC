// AUTO Generated: do not edit

#include "cortexm0cpu.h"
#include <string>

bool CortexM0CPU::decodeInstructionHelper(uint16_t thumbInstruction)
{
	switch (thumbInstruction & 0xffc0)
	{
		// MOVS Rd, Rm
		case 0x0:
		{
			decode_movs_rd_rm(thumbInstruction);
			return true;
		}
		// ADCS Rd, Rd, Rm
		case 0x4140:
		{
			decode_adcs_rd_rd_rm(thumbInstruction);
			return true;
		}
		// SBCS Rd, Rd, Rm
		case 0x4180:
		{
			decode_sbcs_rd_rd_rm(thumbInstruction);
			return true;
		}
		// RSBS Rd, Rn, #0
		case 0x4240:
		{
			decode_rsbs_rd_rn_0(thumbInstruction);
			return true;
		}
		// MULS Rd, Rm, Rd
		case 0x4340:
		{
			decode_muls_rd_rm_rd(thumbInstruction);
			return true;
		}
		// CMP Rn, Rm
		case 0x4280:
		{
			decode_cmp_rn_rm(thumbInstruction);
			return true;
		}
		// CMN Rn, Rm
		case 0x42c0:
		{
			decode_cmn_rn_rm(thumbInstruction);
			return true;
		}
		// ANDS Rd, Rd, Rm
		case 0x4000:
		{
			decode_ands_rd_rd_rm(thumbInstruction);
			return true;
		}
		// EORS Rd, Rd, Rm
		case 0x4040:
		{
			decode_eors_rd_rd_rm(thumbInstruction);
			return true;
		}
		// ORRS Rd, Rd, Rm
		case 0x4300:
		{
			decode_orrs_rd_rd_rm(thumbInstruction);
			return true;
		}
		// BICS Rd, Rd, Rm
		case 0x4380:
		{
			decode_bics_rd_rd_rm(thumbInstruction);
			return true;
		}
		// MVNS Rd, Rm
		case 0x43c0:
		{
			decode_mvns_rd_rm(thumbInstruction);
			return true;
		}
		// TST Rn, Rm
		case 0x4200:
		{
			decode_tst_rn_rm(thumbInstruction);
			return true;
		}
		// LSLS Rd, Rd, Rs
		case 0x4080:
		{
			decode_lsls_rd_rd_rs(thumbInstruction);
			return true;
		}
		// LSRS Rd, Rd, Rs
		case 0x40c0:
		{
			decode_lsrs_rd_rd_rs(thumbInstruction);
			return true;
		}
		// ASRS Rd, Rd, Rs
		case 0x4100:
		{
			decode_asrs_rd_rd_rs(thumbInstruction);
			return true;
		}
		// RORS Rd, Rd, Rs
		case 0x41c0:
		{
			decode_rors_rd_rd_rs(thumbInstruction);
			return true;
		}
		// SXTH Rd, Rm
		case 0xb200:
		{
			decode_sxth_rd_rm(thumbInstruction);
			return true;
		}
		// SXTB Rd, Rm
		case 0xb240:
		{
			decode_sxtb_rd_rm(thumbInstruction);
			return true;
		}
		// UXTH Rd, Rm
		case 0xb280:
		{
			decode_uxth_rd_rm(thumbInstruction);
			return true;
		}
		// UXTB Rd, Rm
		case 0xb2c0:
		{
			decode_uxtb_rd_rm(thumbInstruction);
			return true;
		}
		// REV Rd, Rm
		case 0xba00:
		{
			decode_rev_rd_rm(thumbInstruction);
			return true;
		}
		// REV16 Rd, Rm
		case 0xba40:
		{
			decode_rev16_rd_rm(thumbInstruction);
			return true;
		}
		// REVSH Rd, Rm
		case 0xbac0:
		{
			decode_revsh_rd_rm(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xf800)
	{
		// MOVS Rd, #<imm>
		case 0x2000:
		{
			decode_movs_rd_imm_(thumbInstruction);
			return true;
		}
		// ADDS Rd, Rd, #<imm>
		case 0x3000:
		{
			decode_adds_rd_rd_imm_(thumbInstruction);
			return true;
		}
		// ADD Rd, SP, #<imm>
		case 0xa800:
		{
			decode_add_rd_sp_imm_(thumbInstruction);
			return true;
		}
		// ADR Rd, <label>
		case 0xa000:
		{
			decode_adr_rd_label_(thumbInstruction);
			return true;
		}
		// SUBS Rd, Rd, #<imm>
		case 0x3800:
		{
			decode_subs_rd_rd_imm_(thumbInstruction);
			return true;
		}
		// CMP Rn, #<imm>
		case 0x2800:
		{
			decode_cmp_rn_imm_(thumbInstruction);
			return true;
		}
		// LSLS Rd, Rm, #<shift>
		case 0x0:
		{
			decode_lsls_rd_rm_shift_(thumbInstruction);
			return true;
		}
		// LSRS Rd, Rm, #<shift>
		case 0x800:
		{
			decode_lsrs_rd_rm_shift_(thumbInstruction);
			return true;
		}
		// ASRS Rd, Rm, #<shift>
		case 0x1000:
		{
			decode_asrs_rd_rm_shift_(thumbInstruction);
			return true;
		}
		// LDR Rd, [Rn, #<imm>]
		case 0x6800:
		{
			decode_ldr_rd_rn_imm_(thumbInstruction);
			return true;
		}
		// LDRH Rd, [Rn, #<imm>]
		case 0x8800:
		{
			decode_ldrh_rd_rn_imm_(thumbInstruction);
			return true;
		}
		// LDRB Rd, [Rn, #<imm>]
		case 0x7800:
		{
			decode_ldrb_rd_rn_imm_(thumbInstruction);
			return true;
		}
		// LDR Rd, <label>
		case 0x4800:
		{
			decode_ldr_rd_label_(thumbInstruction);
			return true;
		}
		// LDR Rd, [SP, #<imm>]
		case 0x9800:
		{
			decode_ldr_rd_sp_imm_(thumbInstruction);
			return true;
		}
		// LDM Rn!, {<loreglist>}
		case 0xc800:
		{
			decode_ldm_rn_loreglist_(thumbInstruction);
			return true;
		}
		// Encoding 0xc800 already found
		// LDM Rn, {<loreglist>}
		// STR Rd, [Rn, #<imm>]
		case 0x6000:
		{
			decode_str_rd_rn_imm_(thumbInstruction);
			return true;
		}
		// STRH Rd, [Rn, #<imm>]
		case 0x8000:
		{
			decode_strh_rd_rn_imm_(thumbInstruction);
			return true;
		}
		// STRB Rd, [Rn, #<imm>]
		case 0x7000:
		{
			decode_strb_rd_rn_imm_(thumbInstruction);
			return true;
		}
		// STR Rd, [SP, #<imm>]
		case 0x9000:
		{
			decode_str_rd_sp_imm_(thumbInstruction);
			return true;
		}
		// STM Rn!, {<loreglist>}
		case 0xc000:
		{
			decode_stm_rn_loreglist_(thumbInstruction);
			return true;
		}
		// B <label>
		case 0xe000:
		{
			decode_b_label_(thumbInstruction);
			return true;
		}
		// BL <label>
		case 0xf000:
		{
			decode_bl_label_(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xfe00)
	{
		// ADDS Rd, Rn, #<imm>
		case 0x1c00:
		{
			decode_adds_rd_rn_imm_(thumbInstruction);
			return true;
		}
		// ADDS Rd, Rn, Rm
		case 0x1800:
		{
			decode_adds_rd_rn_rm(thumbInstruction);
			return true;
		}
		// SUBS Rd, Rn, Rm
		case 0x1a00:
		{
			decode_subs_rd_rn_rm(thumbInstruction);
			return true;
		}
		// SUBS Rd, Rn, #<imm>
		case 0x1e00:
		{
			decode_subs_rd_rn_imm_(thumbInstruction);
			return true;
		}
		// LDR Rd, [Rn, Rm]
		case 0x5800:
		{
			decode_ldr_rd_rn_rm_(thumbInstruction);
			return true;
		}
		// LDRH Rd, [Rn, Rm]
		case 0x5a00:
		{
			decode_ldrh_rd_rn_rm_(thumbInstruction);
			return true;
		}
		// LDRSH Rd, [Rn, Rm]
		case 0x5e00:
		{
			decode_ldrsh_rd_rn_rm_(thumbInstruction);
			return true;
		}
		// LDRB Rd, [Rn, Rm]
		case 0x5c00:
		{
			decode_ldrb_rd_rn_rm_(thumbInstruction);
			return true;
		}
		// LDRSB Rd, [Rn, Rm]
		case 0x5600:
		{
			decode_ldrsb_rd_rn_rm_(thumbInstruction);
			return true;
		}
		// STR Rd, [Rn, Rm]
		case 0x5000:
		{
			decode_str_rd_rn_rm_(thumbInstruction);
			return true;
		}
		// STRH Rd, [Rn, Rm]
		case 0x5200:
		{
			decode_strh_rd_rn_rm_(thumbInstruction);
			return true;
		}
		// STRB Rd, [Rn, Rm]
		case 0x5400:
		{
			decode_strb_rd_rn_rm_(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xff00)
	{
		// MOV Rd, Rm
		case 0x4600:
		{
			decode_mov_rd_rm(thumbInstruction);
			return true;
		}
		// ADD Rd, Rd, Rm
		case 0x4400:
		{
			decode_add_rd_rd_rm(thumbInstruction);
			return true;
		}
		// PUSH {<loreglist>}
		case 0xb400:
		{
			decode_push_loreglist_(thumbInstruction);
			return true;
		}
		// PUSH {<loreglist>, LR}
		case 0xb500:
		{
			decode_push_loreglist_lr_(thumbInstruction);
			return true;
		}
		// POP {<loreglist>}
		case 0xbc00:
		{
			decode_pop_loreglist_(thumbInstruction);
			return true;
		}
		// POP {<loreglist>, PC}
		case 0xbd00:
		{
			decode_pop_loreglist_pc_(thumbInstruction);
			return true;
		}
		// SVC #<imm>
		case 0xdf00:
		{
			decode_svc_imm_(thumbInstruction);
			return true;
		}
		// BKPT #<imm>
		case 0xbe00:
		{
			decode_bkpt_imm_(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xffff)
	{
		// SEV
		case 0xbf40:
		{
			decode_sev(thumbInstruction);
			return true;
		}
		// WFE
		case 0xbf20:
		{
			decode_wfe(thumbInstruction);
			return true;
		}
		// WFI
		case 0xbf30:
		{
			decode_wfi(thumbInstruction);
			return true;
		}
		// YIELD[g]
		case 0xbf10:
		{
			decode_yield_g_(thumbInstruction);
			return true;
		}
		// NOP
		case 0xbf00:
		{
			decode_nop(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xff80)
	{
		// ADD SP, SP, #<imm>
		case 0xb000:
		{
			decode_add_sp_sp_imm_(thumbInstruction);
			return true;
		}
		// SUB SP, SP, #<imm>
		case 0xb080:
		{
			decode_sub_sp_sp_imm_(thumbInstruction);
			return true;
		}
		// BX Rm
		case 0x4700:
		{
			decode_bx_rm(thumbInstruction);
			return true;
		}
		// BLX Rm
		case 0x4780:
		{
			decode_blx_rm(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xffe0)
	{
		// CPSID i
		case 0xb660:
		{
			decode_cpsid_i(thumbInstruction);
			return true;
		}
		// Encoding 0xb660 already found
		// CPSIE i
		// MRS Rd, <specreg>
		case 0xf3e0:
		{
			decode_mrs_rd_specreg_(thumbInstruction);
			return true;
		}
		// MSR <specreg>, Rn
		case 0xf380:
		{
			decode_msr_specreg_rn(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xfff0)
	{
		// ISB
		case 0xf3b0:
		{
			decode_isb(thumbInstruction);
			return true;
		}
		// Encoding 0xf3b0 already found
		// DMB
		// Encoding 0xf3b0 already found
		// DSB
		default: break;
	}
	switch (thumbInstruction & 0xf000)
	{
		// B<cc> <label>
		case 0xd000:
		{
			decode_b_cc_label_(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xff07)
	{
		// ADD PC, PC, Rm
		case 0x4407:
		{
			decode_add_pc_pc_rm(thumbInstruction);
			return true;
		}
		default: break;
	}
	switch (thumbInstruction & 0xff8e)
	{
		// MOV PC, Rm
		case 0x468e:
		{
			decode_mov_pc_rm(thumbInstruction);
			return true;
		}
		default: break;
	}
	 return false;
}

std::string CortexM0CPU::disassembleInstructionHelper(uint16_t thumbInstruction, uint16_t thumbInstruction2)
{
	std::string disasString;
	switch (thumbInstruction & 0xffc0)
	{
		// MOVS Rd, Rm
		case 0x0:
		{
			disasString = disas_movs_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ADCS Rd, Rd, Rm
		case 0x4140:
		{
			disasString = disas_adcs_rd_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// SBCS Rd, Rd, Rm
		case 0x4180:
		{
			disasString = disas_sbcs_rd_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// RSBS Rd, Rn, #0
		case 0x4240:
		{
			disasString = disas_rsbs_rd_rn_0(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// MULS Rd, Rm, Rd
		case 0x4340:
		{
			disasString = disas_muls_rd_rm_rd(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// CMP Rn, Rm
		case 0x4280:
		{
			disasString = disas_cmp_rn_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// CMN Rn, Rm
		case 0x42c0:
		{
			disasString = disas_cmn_rn_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ANDS Rd, Rd, Rm
		case 0x4000:
		{
			disasString = disas_ands_rd_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// EORS Rd, Rd, Rm
		case 0x4040:
		{
			disasString = disas_eors_rd_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ORRS Rd, Rd, Rm
		case 0x4300:
		{
			disasString = disas_orrs_rd_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// BICS Rd, Rd, Rm
		case 0x4380:
		{
			disasString = disas_bics_rd_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// MVNS Rd, Rm
		case 0x43c0:
		{
			disasString = disas_mvns_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// TST Rn, Rm
		case 0x4200:
		{
			disasString = disas_tst_rn_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LSLS Rd, Rd, Rs
		case 0x4080:
		{
			disasString = disas_lsls_rd_rd_rs(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LSRS Rd, Rd, Rs
		case 0x40c0:
		{
			disasString = disas_lsrs_rd_rd_rs(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ASRS Rd, Rd, Rs
		case 0x4100:
		{
			disasString = disas_asrs_rd_rd_rs(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// RORS Rd, Rd, Rs
		case 0x41c0:
		{
			disasString = disas_rors_rd_rd_rs(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// SXTH Rd, Rm
		case 0xb200:
		{
			disasString = disas_sxth_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// SXTB Rd, Rm
		case 0xb240:
		{
			disasString = disas_sxtb_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// UXTH Rd, Rm
		case 0xb280:
		{
			disasString = disas_uxth_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// UXTB Rd, Rm
		case 0xb2c0:
		{
			disasString = disas_uxtb_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// REV Rd, Rm
		case 0xba00:
		{
			disasString = disas_rev_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// REV16 Rd, Rm
		case 0xba40:
		{
			disasString = disas_rev16_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// REVSH Rd, Rm
		case 0xbac0:
		{
			disasString = disas_revsh_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xf800)
	{
		// MOVS Rd, #<imm>
		case 0x2000:
		{
			disasString = disas_movs_rd_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ADDS Rd, Rd, #<imm>
		case 0x3000:
		{
			disasString = disas_adds_rd_rd_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ADD Rd, SP, #<imm>
		case 0xa800:
		{
			disasString = disas_add_rd_sp_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ADR Rd, <label>
		case 0xa000:
		{
			disasString = disas_adr_rd_label_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// SUBS Rd, Rd, #<imm>
		case 0x3800:
		{
			disasString = disas_subs_rd_rd_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// CMP Rn, #<imm>
		case 0x2800:
		{
			disasString = disas_cmp_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LSLS Rd, Rm, #<shift>
		case 0x0:
		{
			disasString = disas_lsls_rd_rm_shift_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LSRS Rd, Rm, #<shift>
		case 0x800:
		{
			disasString = disas_lsrs_rd_rm_shift_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ASRS Rd, Rm, #<shift>
		case 0x1000:
		{
			disasString = disas_asrs_rd_rm_shift_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDR Rd, [Rn, #<imm>]
		case 0x6800:
		{
			disasString = disas_ldr_rd_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDRH Rd, [Rn, #<imm>]
		case 0x8800:
		{
			disasString = disas_ldrh_rd_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDRB Rd, [Rn, #<imm>]
		case 0x7800:
		{
			disasString = disas_ldrb_rd_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDR Rd, <label>
		case 0x4800:
		{
			disasString = disas_ldr_rd_label_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDR Rd, [SP, #<imm>]
		case 0x9800:
		{
			disasString = disas_ldr_rd_sp_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDM Rn!, {<loreglist>}
		case 0xc800:
		{
			disasString = disas_ldm_rn_loreglist_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// Encoding 0xc800 already found
		// LDM Rn, {<loreglist>}
		// STR Rd, [Rn, #<imm>]
		case 0x6000:
		{
			disasString = disas_str_rd_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// STRH Rd, [Rn, #<imm>]
		case 0x8000:
		{
			disasString = disas_strh_rd_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// STRB Rd, [Rn, #<imm>]
		case 0x7000:
		{
			disasString = disas_strb_rd_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// STR Rd, [SP, #<imm>]
		case 0x9000:
		{
			disasString = disas_str_rd_sp_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// STM Rn!, {<loreglist>}
		case 0xc000:
		{
			disasString = disas_stm_rn_loreglist_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// B <label>
		case 0xe000:
		{
			disasString = disas_b_label_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// BL <label>
		case 0xf000:
		{
			disasString = disas_bl_label_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xfe00)
	{
		// ADDS Rd, Rn, #<imm>
		case 0x1c00:
		{
			disasString = disas_adds_rd_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ADDS Rd, Rn, Rm
		case 0x1800:
		{
			disasString = disas_adds_rd_rn_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// SUBS Rd, Rn, Rm
		case 0x1a00:
		{
			disasString = disas_subs_rd_rn_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// SUBS Rd, Rn, #<imm>
		case 0x1e00:
		{
			disasString = disas_subs_rd_rn_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDR Rd, [Rn, Rm]
		case 0x5800:
		{
			disasString = disas_ldr_rd_rn_rm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDRH Rd, [Rn, Rm]
		case 0x5a00:
		{
			disasString = disas_ldrh_rd_rn_rm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDRSH Rd, [Rn, Rm]
		case 0x5e00:
		{
			disasString = disas_ldrsh_rd_rn_rm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDRB Rd, [Rn, Rm]
		case 0x5c00:
		{
			disasString = disas_ldrb_rd_rn_rm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// LDRSB Rd, [Rn, Rm]
		case 0x5600:
		{
			disasString = disas_ldrsb_rd_rn_rm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// STR Rd, [Rn, Rm]
		case 0x5000:
		{
			disasString = disas_str_rd_rn_rm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// STRH Rd, [Rn, Rm]
		case 0x5200:
		{
			disasString = disas_strh_rd_rn_rm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// STRB Rd, [Rn, Rm]
		case 0x5400:
		{
			disasString = disas_strb_rd_rn_rm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xff00)
	{
		// MOV Rd, Rm
		case 0x4600:
		{
			disasString = disas_mov_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// ADD Rd, Rd, Rm
		case 0x4400:
		{
			disasString = disas_add_rd_rd_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// PUSH {<loreglist>}
		case 0xb400:
		{
			disasString = disas_push_loreglist_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// PUSH {<loreglist>, LR}
		case 0xb500:
		{
			disasString = disas_push_loreglist_lr_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// POP {<loreglist>}
		case 0xbc00:
		{
			disasString = disas_pop_loreglist_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// POP {<loreglist>, PC}
		case 0xbd00:
		{
			disasString = disas_pop_loreglist_pc_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// SVC #<imm>
		case 0xdf00:
		{
			disasString = disas_svc_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// BKPT #<imm>
		case 0xbe00:
		{
			disasString = disas_bkpt_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xffff)
	{
		// SEV
		case 0xbf40:
		{
			disasString = disas_sev(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// WFE
		case 0xbf20:
		{
			disasString = disas_wfe(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// WFI
		case 0xbf30:
		{
			disasString = disas_wfi(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// YIELD[g]
		case 0xbf10:
		{
			disasString = disas_yield_g_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// NOP
		case 0xbf00:
		{
			disasString = disas_nop(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xff80)
	{
		// ADD SP, SP, #<imm>
		case 0xb000:
		{
			disasString = disas_add_sp_sp_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// SUB SP, SP, #<imm>
		case 0xb080:
		{
			disasString = disas_sub_sp_sp_imm_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// BX Rm
		case 0x4700:
		{
			disasString = disas_bx_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// BLX Rm
		case 0x4780:
		{
			disasString = disas_blx_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xffe0)
	{
		// CPSID i
		case 0xb660:
		{
			disasString = disas_cpsid_i(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// Encoding 0xb660 already found
		// CPSIE i
		// MRS Rd, <specreg>
		case 0xf3e0:
		{
			disasString = disas_mrs_rd_specreg_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// MSR <specreg>, Rn
		case 0xf380:
		{
			disasString = disas_msr_specreg_rn(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xfff0)
	{
		// ISB
		case 0xf3b0:
		{
			disasString = disas_isb(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		// Encoding 0xf3b0 already found
		// DMB
		// Encoding 0xf3b0 already found
		// DSB
		default: break;
	}
	switch (thumbInstruction & 0xf000)
	{
		// B<cc> <label>
		case 0xd000:
		{
			disasString = disas_b_cc_label_(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xff07)
	{
		// ADD PC, PC, Rm
		case 0x4407:
		{
			disasString = disas_add_pc_pc_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	switch (thumbInstruction & 0xff8e)
	{
		// MOV PC, Rm
		case 0x468e:
		{
			disasString = disas_mov_pc_rm(thumbInstruction, thumbInstruction2);
			return disasString;
		}
		default: break;
	}
	return std::string("UNKNOWN INSTRUCTION");
}



// MOVS Rd, #<imm>
// decode_movs_rd_imm_(thumbInstruction);
// disasString = disas_movs_rd_imm_(thumbInstruction, thumbInstruction2);
// MOVS Rd, Rm
// decode_movs_rd_rm(thumbInstruction);
// disasString = disas_movs_rd_rm(thumbInstruction, thumbInstruction2);
// MOV Rd, Rm
// decode_mov_rd_rm(thumbInstruction);
// disasString = disas_mov_rd_rm(thumbInstruction, thumbInstruction2);
// MOV PC, Rm
// decode_mov_pc_rm(thumbInstruction);
// disasString = disas_mov_pc_rm(thumbInstruction, thumbInstruction2);
// ADDS Rd, Rn, #<imm>
// decode_adds_rd_rn_imm_(thumbInstruction);
// disasString = disas_adds_rd_rn_imm_(thumbInstruction, thumbInstruction2);
// ADDS Rd, Rn, Rm
// decode_adds_rd_rn_rm(thumbInstruction);
// disasString = disas_adds_rd_rn_rm(thumbInstruction, thumbInstruction2);
// ADD Rd, Rd, Rm
// decode_add_rd_rd_rm(thumbInstruction);
// disasString = disas_add_rd_rd_rm(thumbInstruction, thumbInstruction2);
// ADD PC, PC, Rm
// decode_add_pc_pc_rm(thumbInstruction);
// disasString = disas_add_pc_pc_rm(thumbInstruction, thumbInstruction2);
// ADDS Rd, Rd, #<imm>
// decode_adds_rd_rd_imm_(thumbInstruction);
// disasString = disas_adds_rd_rd_imm_(thumbInstruction, thumbInstruction2);
// ADCS Rd, Rd, Rm
// decode_adcs_rd_rd_rm(thumbInstruction);
// disasString = disas_adcs_rd_rd_rm(thumbInstruction, thumbInstruction2);
// ADD SP, SP, #<imm>
// decode_add_sp_sp_imm_(thumbInstruction);
// disasString = disas_add_sp_sp_imm_(thumbInstruction, thumbInstruction2);
// ADD Rd, SP, #<imm>
// decode_add_rd_sp_imm_(thumbInstruction);
// disasString = disas_add_rd_sp_imm_(thumbInstruction, thumbInstruction2);
// ADR Rd, <label>
// decode_adr_rd_label_(thumbInstruction);
// disasString = disas_adr_rd_label_(thumbInstruction, thumbInstruction2);
// SUBS Rd, Rn, Rm
// decode_subs_rd_rn_rm(thumbInstruction);
// disasString = disas_subs_rd_rn_rm(thumbInstruction, thumbInstruction2);
// SUBS Rd, Rn, #<imm>
// decode_subs_rd_rn_imm_(thumbInstruction);
// disasString = disas_subs_rd_rn_imm_(thumbInstruction, thumbInstruction2);
// SUBS Rd, Rd, #<imm>
// decode_subs_rd_rd_imm_(thumbInstruction);
// disasString = disas_subs_rd_rd_imm_(thumbInstruction, thumbInstruction2);
// SBCS Rd, Rd, Rm
// decode_sbcs_rd_rd_rm(thumbInstruction);
// disasString = disas_sbcs_rd_rd_rm(thumbInstruction, thumbInstruction2);
// SUB SP, SP, #<imm>
// decode_sub_sp_sp_imm_(thumbInstruction);
// disasString = disas_sub_sp_sp_imm_(thumbInstruction, thumbInstruction2);
// RSBS Rd, Rn, #0
// decode_rsbs_rd_rn_0(thumbInstruction);
// disasString = disas_rsbs_rd_rn_0(thumbInstruction, thumbInstruction2);
// MULS Rd, Rm, Rd
// decode_muls_rd_rm_rd(thumbInstruction);
// disasString = disas_muls_rd_rm_rd(thumbInstruction, thumbInstruction2);
// CMP Rn, Rm
// decode_cmp_rn_rm(thumbInstruction);
// disasString = disas_cmp_rn_rm(thumbInstruction, thumbInstruction2);
// CMN Rn, Rm
// decode_cmn_rn_rm(thumbInstruction);
// disasString = disas_cmn_rn_rm(thumbInstruction, thumbInstruction2);
// CMP Rn, #<imm>
// decode_cmp_rn_imm_(thumbInstruction);
// disasString = disas_cmp_rn_imm_(thumbInstruction, thumbInstruction2);
// ANDS Rd, Rd, Rm
// decode_ands_rd_rd_rm(thumbInstruction);
// disasString = disas_ands_rd_rd_rm(thumbInstruction, thumbInstruction2);
// EORS Rd, Rd, Rm
// decode_eors_rd_rd_rm(thumbInstruction);
// disasString = disas_eors_rd_rd_rm(thumbInstruction, thumbInstruction2);
// ORRS Rd, Rd, Rm
// decode_orrs_rd_rd_rm(thumbInstruction);
// disasString = disas_orrs_rd_rd_rm(thumbInstruction, thumbInstruction2);
// BICS Rd, Rd, Rm
// decode_bics_rd_rd_rm(thumbInstruction);
// disasString = disas_bics_rd_rd_rm(thumbInstruction, thumbInstruction2);
// MVNS Rd, Rm
// decode_mvns_rd_rm(thumbInstruction);
// disasString = disas_mvns_rd_rm(thumbInstruction, thumbInstruction2);
// TST Rn, Rm
// decode_tst_rn_rm(thumbInstruction);
// disasString = disas_tst_rn_rm(thumbInstruction, thumbInstruction2);
// LSLS Rd, Rm, #<shift>
// decode_lsls_rd_rm_shift_(thumbInstruction);
// disasString = disas_lsls_rd_rm_shift_(thumbInstruction, thumbInstruction2);
// LSLS Rd, Rd, Rs
// decode_lsls_rd_rd_rs(thumbInstruction);
// disasString = disas_lsls_rd_rd_rs(thumbInstruction, thumbInstruction2);
// LSRS Rd, Rm, #<shift>
// decode_lsrs_rd_rm_shift_(thumbInstruction);
// disasString = disas_lsrs_rd_rm_shift_(thumbInstruction, thumbInstruction2);
// LSRS Rd, Rd, Rs
// decode_lsrs_rd_rd_rs(thumbInstruction);
// disasString = disas_lsrs_rd_rd_rs(thumbInstruction, thumbInstruction2);
// ASRS Rd, Rm, #<shift>
// decode_asrs_rd_rm_shift_(thumbInstruction);
// disasString = disas_asrs_rd_rm_shift_(thumbInstruction, thumbInstruction2);
// ASRS Rd, Rd, Rs
// decode_asrs_rd_rd_rs(thumbInstruction);
// disasString = disas_asrs_rd_rd_rs(thumbInstruction, thumbInstruction2);
// RORS Rd, Rd, Rs
// decode_rors_rd_rd_rs(thumbInstruction);
// disasString = disas_rors_rd_rd_rs(thumbInstruction, thumbInstruction2);
// LDR Rd, [Rn, #<imm>]
// decode_ldr_rd_rn_imm_(thumbInstruction);
// disasString = disas_ldr_rd_rn_imm_(thumbInstruction, thumbInstruction2);
// LDRH Rd, [Rn, #<imm>]
// decode_ldrh_rd_rn_imm_(thumbInstruction);
// disasString = disas_ldrh_rd_rn_imm_(thumbInstruction, thumbInstruction2);
// LDRB Rd, [Rn, #<imm>]
// decode_ldrb_rd_rn_imm_(thumbInstruction);
// disasString = disas_ldrb_rd_rn_imm_(thumbInstruction, thumbInstruction2);
// LDR Rd, [Rn, Rm]
// decode_ldr_rd_rn_rm_(thumbInstruction);
// disasString = disas_ldr_rd_rn_rm_(thumbInstruction, thumbInstruction2);
// LDRH Rd, [Rn, Rm]
// decode_ldrh_rd_rn_rm_(thumbInstruction);
// disasString = disas_ldrh_rd_rn_rm_(thumbInstruction, thumbInstruction2);
// LDRSH Rd, [Rn, Rm]
// decode_ldrsh_rd_rn_rm_(thumbInstruction);
// disasString = disas_ldrsh_rd_rn_rm_(thumbInstruction, thumbInstruction2);
// LDRB Rd, [Rn, Rm]
// decode_ldrb_rd_rn_rm_(thumbInstruction);
// disasString = disas_ldrb_rd_rn_rm_(thumbInstruction, thumbInstruction2);
// LDRSB Rd, [Rn, Rm]
// decode_ldrsb_rd_rn_rm_(thumbInstruction);
// disasString = disas_ldrsb_rd_rn_rm_(thumbInstruction, thumbInstruction2);
// LDR Rd, <label>
// decode_ldr_rd_label_(thumbInstruction);
// disasString = disas_ldr_rd_label_(thumbInstruction, thumbInstruction2);
// LDR Rd, [SP, #<imm>]
// decode_ldr_rd_sp_imm_(thumbInstruction);
// disasString = disas_ldr_rd_sp_imm_(thumbInstruction, thumbInstruction2);
// LDM Rn!, {<loreglist>}
// decode_ldm_rn_loreglist_(thumbInstruction);
// disasString = disas_ldm_rn_loreglist_(thumbInstruction, thumbInstruction2);
// LDM Rn, {<loreglist>}
// decode_ldm_rn_loreglist_(thumbInstruction);
// disasString = disas_ldm_rn_loreglist_(thumbInstruction, thumbInstruction2);
// STR Rd, [Rn, #<imm>]
// decode_str_rd_rn_imm_(thumbInstruction);
// disasString = disas_str_rd_rn_imm_(thumbInstruction, thumbInstruction2);
// STRH Rd, [Rn, #<imm>]
// decode_strh_rd_rn_imm_(thumbInstruction);
// disasString = disas_strh_rd_rn_imm_(thumbInstruction, thumbInstruction2);
// STRB Rd, [Rn, #<imm>]
// decode_strb_rd_rn_imm_(thumbInstruction);
// disasString = disas_strb_rd_rn_imm_(thumbInstruction, thumbInstruction2);
// STR Rd, [Rn, Rm]
// decode_str_rd_rn_rm_(thumbInstruction);
// disasString = disas_str_rd_rn_rm_(thumbInstruction, thumbInstruction2);
// STRH Rd, [Rn, Rm]
// decode_strh_rd_rn_rm_(thumbInstruction);
// disasString = disas_strh_rd_rn_rm_(thumbInstruction, thumbInstruction2);
// STRB Rd, [Rn, Rm]
// decode_strb_rd_rn_rm_(thumbInstruction);
// disasString = disas_strb_rd_rn_rm_(thumbInstruction, thumbInstruction2);
// STR Rd, [SP, #<imm>]
// decode_str_rd_sp_imm_(thumbInstruction);
// disasString = disas_str_rd_sp_imm_(thumbInstruction, thumbInstruction2);
// STM Rn!, {<loreglist>}
// decode_stm_rn_loreglist_(thumbInstruction);
// disasString = disas_stm_rn_loreglist_(thumbInstruction, thumbInstruction2);
// PUSH {<loreglist>}
// decode_push_loreglist_(thumbInstruction);
// disasString = disas_push_loreglist_(thumbInstruction, thumbInstruction2);
// PUSH {<loreglist>, LR}
// decode_push_loreglist_lr_(thumbInstruction);
// disasString = disas_push_loreglist_lr_(thumbInstruction, thumbInstruction2);
// POP {<loreglist>}
// decode_pop_loreglist_(thumbInstruction);
// disasString = disas_pop_loreglist_(thumbInstruction, thumbInstruction2);
// POP {<loreglist>, PC}
// decode_pop_loreglist_pc_(thumbInstruction);
// disasString = disas_pop_loreglist_pc_(thumbInstruction, thumbInstruction2);
// B<cc> <label>
// decode_b_cc_label_(thumbInstruction);
// disasString = disas_b_cc_label_(thumbInstruction, thumbInstruction2);
// B <label>
// decode_b_label_(thumbInstruction);
// disasString = disas_b_label_(thumbInstruction, thumbInstruction2);
// BL <label>
// decode_bl_label_(thumbInstruction);
// disasString = disas_bl_label_(thumbInstruction, thumbInstruction2);
// BX Rm
// decode_bx_rm(thumbInstruction);
// disasString = disas_bx_rm(thumbInstruction, thumbInstruction2);
// BLX Rm
// decode_blx_rm(thumbInstruction);
// disasString = disas_blx_rm(thumbInstruction, thumbInstruction2);
// SXTH Rd, Rm
// decode_sxth_rd_rm(thumbInstruction);
// disasString = disas_sxth_rd_rm(thumbInstruction, thumbInstruction2);
// SXTB Rd, Rm
// decode_sxtb_rd_rm(thumbInstruction);
// disasString = disas_sxtb_rd_rm(thumbInstruction, thumbInstruction2);
// UXTH Rd, Rm
// decode_uxth_rd_rm(thumbInstruction);
// disasString = disas_uxth_rd_rm(thumbInstruction, thumbInstruction2);
// UXTB Rd, Rm
// decode_uxtb_rd_rm(thumbInstruction);
// disasString = disas_uxtb_rd_rm(thumbInstruction, thumbInstruction2);
// REV Rd, Rm
// decode_rev_rd_rm(thumbInstruction);
// disasString = disas_rev_rd_rm(thumbInstruction, thumbInstruction2);
// REV16 Rd, Rm
// decode_rev16_rd_rm(thumbInstruction);
// disasString = disas_rev16_rd_rm(thumbInstruction, thumbInstruction2);
// REVSH Rd, Rm
// decode_revsh_rd_rm(thumbInstruction);
// disasString = disas_revsh_rd_rm(thumbInstruction, thumbInstruction2);
// SVC #<imm>
// decode_svc_imm_(thumbInstruction);
// disasString = disas_svc_imm_(thumbInstruction, thumbInstruction2);
// CPSID i
// decode_cpsid_i(thumbInstruction);
// disasString = disas_cpsid_i(thumbInstruction, thumbInstruction2);
// CPSIE i
// decode_cpsie_i(thumbInstruction);
// disasString = disas_cpsie_i(thumbInstruction, thumbInstruction2);
// MRS Rd, <specreg>
// decode_mrs_rd_specreg_(thumbInstruction);
// disasString = disas_mrs_rd_specreg_(thumbInstruction, thumbInstruction2);
// MSR <specreg>, Rn
// decode_msr_specreg_rn(thumbInstruction);
// disasString = disas_msr_specreg_rn(thumbInstruction, thumbInstruction2);
// BKPT #<imm>
// decode_bkpt_imm_(thumbInstruction);
// disasString = disas_bkpt_imm_(thumbInstruction, thumbInstruction2);
// SEV
// decode_sev(thumbInstruction);
// disasString = disas_sev(thumbInstruction, thumbInstruction2);
// WFE
// decode_wfe(thumbInstruction);
// disasString = disas_wfe(thumbInstruction, thumbInstruction2);
// WFI
// decode_wfi(thumbInstruction);
// disasString = disas_wfi(thumbInstruction, thumbInstruction2);
// YIELD[g]
// decode_yield_g_(thumbInstruction);
// disasString = disas_yield_g_(thumbInstruction, thumbInstruction2);
// NOP
// decode_nop(thumbInstruction);
// disasString = disas_nop(thumbInstruction, thumbInstruction2);
// ISB
// decode_isb(thumbInstruction);
// disasString = disas_isb(thumbInstruction, thumbInstruction2);
// DMB
// decode_dmb(thumbInstruction);
// disasString = disas_dmb(thumbInstruction, thumbInstruction2);
// DSB
// decode_dsb(thumbInstruction);
// disasString = disas_dsb(thumbInstruction, thumbInstruction2);
