#include <unordered_map>
#include <string>

#include "isa.hh"
#include "mneumonic.hh"

namespace fromstring {
  const std::unordered_map<std::string_view, isa::op>& op() {
    static const std::unordered_map<std::string_view, isa::op> _ = {
      {mneumonic::op::ADC, isa::op::ADC},
      {mneumonic::op::AND, isa::op::AND},
      {mneumonic::op::ASL, isa::op::ASL},
      {mneumonic::op::BBR0, isa::op::BBR0},
      {mneumonic::op::BBR1, isa::op::BBR1},
      {mneumonic::op::BBR2, isa::op::BBR2},
      {mneumonic::op::BBR3, isa::op::BBR3},
      {mneumonic::op::BBR4, isa::op::BBR4},
      {mneumonic::op::BBR5, isa::op::BBR5},
      {mneumonic::op::BBR6, isa::op::BBR6},
      {mneumonic::op::BBR7, isa::op::BBR7},
      {mneumonic::op::BBS0, isa::op::BBS0},
      {mneumonic::op::BBS1, isa::op::BBS1},
      {mneumonic::op::BBS2, isa::op::BBS2},
      {mneumonic::op::BBS3, isa::op::BBS3},
      {mneumonic::op::BBS4, isa::op::BBS4},
      {mneumonic::op::BBS5, isa::op::BBS5},
      {mneumonic::op::BBS6, isa::op::BBS6},
      {mneumonic::op::BBS7, isa::op::BBS7},
      {mneumonic::op::BCC, isa::op::BCC},
      {mneumonic::op::BCS, isa::op::BCS},
      {mneumonic::op::BEQ, isa::op::BEQ},
      {mneumonic::op::BIT, isa::op::BIT},
      {mneumonic::op::BMI, isa::op::BMI},
      {mneumonic::op::BNE, isa::op::BNE},
      {mneumonic::op::BPL, isa::op::BPL},
      {mneumonic::op::BRA, isa::op::BRA},
      {mneumonic::op::BRK, isa::op::BRK},
      {mneumonic::op::BVC, isa::op::BVC},
      {mneumonic::op::BVS, isa::op::BVS},
      {mneumonic::op::CLC, isa::op::CLC},
      {mneumonic::op::CLD, isa::op::CLD},
      {mneumonic::op::CLI, isa::op::CLI},
      {mneumonic::op::CLV, isa::op::CLV},
      {mneumonic::op::CMP, isa::op::CMP},
      {mneumonic::op::CPX, isa::op::CPX},
      {mneumonic::op::CPY, isa::op::CPY},
      {mneumonic::op::DEC, isa::op::DEC},
      {mneumonic::op::DEX, isa::op::DEX},
      {mneumonic::op::DEY, isa::op::DEY},
      {mneumonic::op::EOR, isa::op::EOR},
      {mneumonic::op::INC, isa::op::INC},
      {mneumonic::op::INX, isa::op::INX},
      {mneumonic::op::INY, isa::op::INY},
      {mneumonic::op::JMP, isa::op::JMP},
      {mneumonic::op::JSR, isa::op::JSR},
      {mneumonic::op::LDA, isa::op::LDA},
      {mneumonic::op::LDX, isa::op::LDX},
      {mneumonic::op::LDY, isa::op::LDY},
      {mneumonic::op::LSR, isa::op::LSR},
      {mneumonic::op::NOP, isa::op::NOP},
      {mneumonic::op::ORA, isa::op::ORA},
      {mneumonic::op::PHA, isa::op::PHA},
      {mneumonic::op::PHP, isa::op::PHP},
      {mneumonic::op::PHX, isa::op::PHX},
      {mneumonic::op::PHY, isa::op::PHY},
      {mneumonic::op::PLA, isa::op::PLA},
      {mneumonic::op::PLP, isa::op::PLP},
      {mneumonic::op::PLX, isa::op::PLX},
      {mneumonic::op::PLY, isa::op::PLY},
      {mneumonic::op::RMB0, isa::op::RMB0},
      {mneumonic::op::RMB1, isa::op::RMB1},
      {mneumonic::op::RMB2, isa::op::RMB2},
      {mneumonic::op::RMB3, isa::op::RMB3},
      {mneumonic::op::RMB4, isa::op::RMB4},
      {mneumonic::op::RMB5, isa::op::RMB5},
      {mneumonic::op::RMB6, isa::op::RMB6},
      {mneumonic::op::RMB7, isa::op::RMB7},
      {mneumonic::op::ROL, isa::op::ROL},
      {mneumonic::op::ROR, isa::op::ROR},
      {mneumonic::op::RTI, isa::op::RTI},
      {mneumonic::op::RTS, isa::op::RTS},
      {mneumonic::op::SBC, isa::op::SBC},
      {mneumonic::op::SEC, isa::op::SEC},
      {mneumonic::op::SED, isa::op::SED},
      {mneumonic::op::SEI, isa::op::SEI},
      {mneumonic::op::SMB0, isa::op::SMB0},
      {mneumonic::op::SMB1, isa::op::SMB1},
      {mneumonic::op::SMB2, isa::op::SMB2},
      {mneumonic::op::SMB3, isa::op::SMB3},
      {mneumonic::op::SMB4, isa::op::SMB4},
      {mneumonic::op::SMB5, isa::op::SMB5},
      {mneumonic::op::SMB6, isa::op::SMB6},
      {mneumonic::op::SMB7, isa::op::SMB7},
      {mneumonic::op::STA, isa::op::STA},
      {mneumonic::op::STP, isa::op::STP},
      {mneumonic::op::STX, isa::op::STX},
      {mneumonic::op::STY, isa::op::STY},
      {mneumonic::op::STZ, isa::op::STZ},
      {mneumonic::op::TAX, isa::op::TAX},
      {mneumonic::op::TAY, isa::op::TAY},
      {mneumonic::op::TRB, isa::op::TRB},
      {mneumonic::op::TSB, isa::op::TSB},
      {mneumonic::op::TSX, isa::op::TSX},
      {mneumonic::op::TXA, isa::op::TXA},
      {mneumonic::op::TXS, isa::op::TXS},
      {mneumonic::op::TYA, isa::op::TYA},
      {mneumonic::op::WAI, isa::op::WAI},
    };
    return _;
  }

  const std::unordered_map<std::string_view, isa::mode>& mode() {
    static const std::unordered_map<std::string_view, isa::mode> _ {
      {mneumonic::mode::A, isa::mode::A},
      {mneumonic::mode::AII, isa::mode::AII},
      {mneumonic::mode::AIX, isa::mode::AIX},
      {mneumonic::mode::AIY, isa::mode::AIY},
      {mneumonic::mode::AI, isa::mode::AI},
      {mneumonic::mode::ACC, isa::mode::ACC},
      {mneumonic::mode::IMM, isa::mode::IMM},
      {mneumonic::mode::I, isa::mode::I},
      {mneumonic::mode::R, isa::mode::R},
      {mneumonic::mode::S, isa::mode::S},
      {mneumonic::mode::ZP, isa::mode::ZP},
      {mneumonic::mode::ZPII, isa::mode::ZPII},
      {mneumonic::mode::ZPX, isa::mode::ZPX},
      {mneumonic::mode::ZPY, isa::mode::ZPY},
      {mneumonic::mode::ZPI, isa::mode::ZPI},
      {mneumonic::mode::ZPIY, isa::mode::ZPIY},
    };
    return _;
  }
}
