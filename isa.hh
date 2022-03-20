#pragma once

namespace isa {

enum class op {
  ADC,
  AND,
  ASL,
  BBR0,
  BBR1,
  BBR2,
  BBR3,
  BBR4,
  BBR5,
  BBR6,
  BBR7,
  BBS0,
  BBS1,
  BBS2,
  BBS3,
  BBS4,
  BBS5,
  BBS6,
  BBS7,
  BCC,
  BCS,
  BEQ,
  BIT,
  BMI,
  BNE,
  BPL,
  BRA,
  BRK,
  BVC,
  BVS,
  CLC,
  CLD,
  CLI,
  CLV,
  CMP,
  CPX,
  CPY,
  DEC,
  DEX,
  DEY,
  EOR,
  INC,
  INX,
  INY,
  JMP,
  JSR,
  LDA,
  LDX,
  LDY,
  LSR,
  NOP,
  ORA,
  PHA,
  PHP,
  PHX,
  PHY,
  PLA,
  PLP,
  PLX,
  PLY,
  RMB0,
  RMB1,
  RMB2,
  RMB3,
  RMB4,
  RMB5,
  RMB6,
  RMB7,
  ROL,
  ROR,
  RTI,
  RTS,
  SBC,
  SEC,
  SED,
  SEI,
  SMB0,
  SMB1,
  SMB2,
  SMB3,
  SMB4,
  SMB5,
  SMB6,
  SMB7,
  STA,
  STP,
  STX,
  STY,
  STZ,
  TAX,
  TAY,
  TRB,
  TSB,
  TSX,
  TXA,
  TXS,
  TYA,
  WAI,
};

enum class mode {
  A,    // Absolute                    a
  AII,  // Absolute Indexed Indirect   (a,x)
  AIX,  // Absolute Indexed with X     a,x
  AIY,  // Absolute Indexed with Y     a,y
  AI,   // Absolute Indrect            (a)
  ACC,  // Accumulator                 A
  IMM,  // Immediate                   #
  I,    // Implied                     i
  R,    // Program Counter Relative    r
  S,    // Stack                       s
  ZP,   // Zero Page                   zp
  ZPII, // Zero Page Indexed Indirect  (zp,x)
  ZPX,  // Zero Page Indexed with X    zp,x
  ZPY,  // Zero Page Indexed with Y    zp,y
  ZPI,  // Zero Page Indirect          (zp)
  ZPIY, // Zero Page Indirect Indexed with Y (zp),y
};

}
