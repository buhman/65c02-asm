#pragma once

#include <string>

namespace mneumonic {
  namespace mode {
    constexpr std::string_view A    = "a";
    constexpr std::string_view AII  = "(a,x)";
    constexpr std::string_view AIX  = "a,x";
    constexpr std::string_view AIY  = "a,y";
    constexpr std::string_view AI   = "(a)";
    constexpr std::string_view ACC  = "A";
    constexpr std::string_view IMM  = "#";
    constexpr std::string_view I    = "i";
    constexpr std::string_view R    = "r";
    constexpr std::string_view S    = "s";
    constexpr std::string_view ZP   = "zp";
    constexpr std::string_view ZPII = "(zp,x)";
    constexpr std::string_view ZPX  = "zp,x";
    constexpr std::string_view ZPY  = "zp,y";
    constexpr std::string_view ZPI  = "(zp)";
    constexpr std::string_view ZPIY = "(zp),y";
  }
}

namespace mneumonic {
  namespace op {
    constexpr std::string_view ADC  = "ADC";
    constexpr std::string_view AND  = "AND";
    constexpr std::string_view ASL  = "ASL";
    constexpr std::string_view BBR0 = "BBR0";
    constexpr std::string_view BBR1 = "BBR1";
    constexpr std::string_view BBR2 = "BBR2";
    constexpr std::string_view BBR3 = "BBR3";
    constexpr std::string_view BBR4 = "BBR4";
    constexpr std::string_view BBR5 = "BBR5";
    constexpr std::string_view BBR6 = "BBR6";
    constexpr std::string_view BBR7 = "BBR7";
    constexpr std::string_view BBS0 = "BBS0";
    constexpr std::string_view BBS1 = "BBS1";
    constexpr std::string_view BBS2 = "BBS2";
    constexpr std::string_view BBS3 = "BBS3";
    constexpr std::string_view BBS4 = "BBS4";
    constexpr std::string_view BBS5 = "BBS5";
    constexpr std::string_view BBS6 = "BBS6";
    constexpr std::string_view BBS7 = "BBS7";
    constexpr std::string_view BCC  = "BCC";
    constexpr std::string_view BCS  = "BCS";
    constexpr std::string_view BEQ  = "BEQ";
    constexpr std::string_view BIT  = "BIT";
    constexpr std::string_view BMI  = "BMI";
    constexpr std::string_view BNE  = "BNE";
    constexpr std::string_view BPL  = "BPL";
    constexpr std::string_view BRA  = "BRA";
    constexpr std::string_view BRK  = "BRK";
    constexpr std::string_view BVC  = "BVC";
    constexpr std::string_view BVS  = "BVS";
    constexpr std::string_view CLC  = "CLC";
    constexpr std::string_view CLD  = "CLD";
    constexpr std::string_view CLI  = "CLI";
    constexpr std::string_view CLV  = "CLV";
    constexpr std::string_view CMP  = "CMP";
    constexpr std::string_view CPX  = "CPX";
    constexpr std::string_view CPY  = "CPY";
    constexpr std::string_view DEC  = "DEC";
    constexpr std::string_view DEX  = "DEX";
    constexpr std::string_view DEY  = "DEY";
    constexpr std::string_view EOR  = "EOR";
    constexpr std::string_view INC  = "INC";
    constexpr std::string_view INX  = "INX";
    constexpr std::string_view INY  = "INY";
    constexpr std::string_view JMP  = "JMP";
    constexpr std::string_view JSR  = "JSR";
    constexpr std::string_view LDA  = "LDA";
    constexpr std::string_view LDX  = "LDX";
    constexpr std::string_view LDY  = "LDY";
    constexpr std::string_view LSR  = "LSR";
    constexpr std::string_view NOP  = "NOP";
    constexpr std::string_view ORA  = "ORA";
    constexpr std::string_view PHA  = "PHA";
    constexpr std::string_view PHP  = "PHP";
    constexpr std::string_view PHX  = "PHX";
    constexpr std::string_view PHY  = "PHY";
    constexpr std::string_view PLA  = "PLA";
    constexpr std::string_view PLP  = "PLP";
    constexpr std::string_view PLX  = "PLX";
    constexpr std::string_view PLY  = "PLY";
    constexpr std::string_view RMB0 = "RMB0";
    constexpr std::string_view RMB1 = "RMB1";
    constexpr std::string_view RMB2 = "RMB2";
    constexpr std::string_view RMB3 = "RMB3";
    constexpr std::string_view RMB4 = "RMB4";
    constexpr std::string_view RMB5 = "RMB5";
    constexpr std::string_view RMB6 = "RMB6";
    constexpr std::string_view RMB7 = "RMB7";
    constexpr std::string_view ROL  = "ROL";
    constexpr std::string_view ROR  = "ROR";
    constexpr std::string_view RTI  = "RTI";
    constexpr std::string_view RTS  = "RTS";
    constexpr std::string_view SBC  = "SBC";
    constexpr std::string_view SEC  = "SEC";
    constexpr std::string_view SED  = "SED";
    constexpr std::string_view SEI  = "SEI";
    constexpr std::string_view SMB0 = "SMB0";
    constexpr std::string_view SMB1 = "SMB1";
    constexpr std::string_view SMB2 = "SMB2";
    constexpr std::string_view SMB3 = "SMB3";
    constexpr std::string_view SMB4 = "SMB4";
    constexpr std::string_view SMB5 = "SMB5";
    constexpr std::string_view SMB6 = "SMB6";
    constexpr std::string_view SMB7 = "SMB7";
    constexpr std::string_view STA  = "STA";
    constexpr std::string_view STP  = "STP";
    constexpr std::string_view STX  = "STX";
    constexpr std::string_view STY  = "STY";
    constexpr std::string_view STZ  = "STZ";
    constexpr std::string_view TAX  = "TAX";
    constexpr std::string_view TAY  = "TAY";
    constexpr std::string_view TRB  = "TRB";
    constexpr std::string_view TSB  = "TSB";
    constexpr std::string_view TSX  = "TSX";
    constexpr std::string_view TXA  = "TXA";
    constexpr std::string_view TXS  = "TXS";
    constexpr std::string_view TYA  = "TYA";
    constexpr std::string_view WAI  = "WAI";
  }
}
