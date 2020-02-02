#ifndef THUMBINSTRUCTIONS_H
#define THUMBINSTRUCTIONS_H

#include <cstdint>


// Opcodes
constexpr uint16_t ADC_RD_RM_MASK = 0xffc0;
constexpr uint16_t ADC_RD_RM_CODE = 0x4140;

constexpr uint16_t ADD_RD_RN_IMMED3_MASK = 0xfe00;
constexpr uint16_t ADD_RD_RN_IMMED3_CODE = 0x1c00;

constexpr uint16_t ADD_RD_IMMED8_MASK = 0xf800;
constexpr uint16_t ADD_RD_IMMED8_CODE = 0x3000;

constexpr uint16_t ADD_RD_RN_RM_MASK = 0xfe00;
constexpr uint16_t ADD_RD_RN_RM_CODE = 0x1800;

constexpr uint16_t ADD_RD_RM_MASK = 0xff00;
constexpr uint16_t ADD_RD_RM_CODE = 0x4400;

constexpr uint16_t ADD_RD_PC_IMMED8X4_MASK = 0xf800;
constexpr uint16_t ADD_RD_PC_IMMED8X4_CODE = 0xa000;

constexpr uint16_t ADD_RD_SP_IMMED8X4_MASK = 0xf800;
constexpr uint16_t ADD_RD_SP_IMMED8X4_CODE = 0xa800;

constexpr uint16_t ADD_SP_IMMED7_MASK = 0xff80;
constexpr uint16_t ADD_SP_IMMED7_CODE = 0xb000;

constexpr uint16_t AND_RD_RM_MASK = 0xffc0;
constexpr uint16_t AND_RD_RM_CODE = 0x4000;

constexpr uint16_t ASR_RD_RM_IMMED5_MASK = 0xf800;
constexpr uint16_t ASR_RD_RM_IMMED5_CODE = 0x1000;

constexpr uint16_t B_COND_TARGET_MASK = 0xf000;
constexpr uint16_t B_COND_TARGET_CODE = 0xd000;

constexpr uint16_t B_TARGET_MASK = 0xf800;
constexpr uint16_t B_TARGET_CODE = 0xe000;

constexpr uint16_t BIC_RD_RM_MASK = 0xffc0;
constexpr uint16_t BIC_RD_RM_CODE = 0x4380;

constexpr uint16_t BKPT_IMM8_MASK = 0xff00;
constexpr uint16_t BKPT_IMM8_CODE = 0xbe00;

// Conditions

constexpr uint16_t THUMB_COND_EQ = 0x00;
constexpr uint16_t THUMB_COND_NE = 0x01;
constexpr uint16_t THUMB_COND_CSHS = 0x02;
constexpr uint16_t THUMB_COND_CCLO = 0x03;
constexpr uint16_t THUMB_COND_MI = 0x04;
constexpr uint16_t THUMB_COND_PL = 0x05;
constexpr uint16_t THUMB_COND_VS = 0x06;
constexpr uint16_t THUMB_COND_VC = 0x07;
constexpr uint16_t THUMB_COND_HI = 0x08;
constexpr uint16_t THUMB_COND_LS = 0x09;
constexpr uint16_t THUMB_COND_GE = 0x0a;
constexpr uint16_t THUMB_COND_LT = 0x0b;
constexpr uint16_t THUMB_COND_GT = 0x0c;
constexpr uint16_t THUMB_COND_LE = 0x0d;
constexpr uint16_t THUMB_COND_AL = 0x0e;















#endif // THUMBINSTRUCTIONS_H
