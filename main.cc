#include <cassert>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "assembler.hh"
#include "addressing_mode.hh"
#include "codec.hh"
#include "parser.hh"

using symbol_table_t = std::unordered_map<size_t, assembler::program_t::const_iterator>;

bool resolve_symbols(assembler::program_t& program, symbol_table_t& symbol_table)
{
  size_t offset = 0;

  for (auto ins = program.begin(); ins != program.end(); ins++) {
    if (ins->symbol != std::nullopt) {
      auto [_, ok] = symbol_table.insert({*(ins->symbol), ins});
      if (!ok) {
        std::cout << "duplicate symbol\n";
        return false;
      }

      std::cout << *(ins->symbol) << ' ' << offset << '\n';
    }

    ins->location = offset;

    auto am_it = addressing_mode().find(ins->mode);
    assert (am_it != addressing_mode().end());
    offset += 1 + am_it->second.len;
  }

  return true;
}

void serialize_program(const assembler::program_t& program, const symbol_table_t &symbol_table, size_t link_location, std::ostream& out)
{
  char buf[3];

  for (auto ins = program.cbegin(); ins != program.cend(); ins++) {
    std::cerr << "enc " << (int)ins->op << ' ' << (int)ins->mode << '\n';
    auto opcode_it = codec::encode().find({ins->op, ins->mode});
    assert (opcode_it != codec::encode().end());

    buf[0] = opcode_it->second;

    auto am_it = addressing_mode().find(ins->mode);
    assert (am_it != addressing_mode().end());

    auto get_value = [&]() -> ssize_t {
      if (std::holds_alternative<assembler::reference_t>(ins->value)) {
        assembler::reference_t ref = std::get<assembler::reference_t>(ins->value);
        auto sym_it = symbol_table.find(ref.symbol);
        assert (sym_it != symbol_table.end());
        auto ref_ins = sym_it->second;
        if (ins->mode == isa::mode::R) {
          std::cout << "relative\n";
          ssize_t offset = static_cast<ssize_t>(ref_ins->location) - static_cast<ssize_t>(ins->location + 2);
          return offset;
        } else {
          return ref_ins->location + link_location;
        }
      } else if (std::holds_alternative<assembler::literal_t>(ins->value)) {
        assembler::literal_t lit = std::get<assembler::literal_t>(ins->value);
        return lit.num;
      } else if (std::holds_alternative<assembler::implied_t>(ins->value)) {
        assert (std::holds_alternative<assembler::implied_t>(ins->value));
      } else {
        assert (false);
      }
      return 0;
    };

    size_t value = get_value();
    if (!am_it->second.valid(value)) {
      std::cout << "overflow at h" << std::hex << ins->location << '\n';
    }

    std::cout << "value " << std::hex << value << ' ' << am_it->second.len << '\n';

    if (am_it->second.len >= 2)
      buf[2] = (value >> 8) & 0xff;
    if (am_it->second.len >= 1)
      buf[1] = (value >> 0) & 0xff;

    out.write(buf, 1 + am_it->second.len);
  }
}

int main(int argc, char * argv[])
{
  if (argc < 3) {
    std::cerr << "argc < 3\n";
    return -1;
  }

  std::string input_filename {argv[1]};
  std::ifstream is {input_filename, std::ios::binary | std::ios::ate};
  if (!is.is_open()) {
    std::cerr << "failed to open " << input_filename << '\n';
    return -1;
  }

  auto size = is.tellg();
  std::string buf(size, '\0'); // construct string to stream size
  is.seekg(0);
  is.read(buf.data(), size);
  is.close();


  assembler::program_t program;
  symbol_table_t symbol_table;
  bool ok;

  ok = parser::parse(buf, program);
  if (!ok)
    return -1;

  ok = resolve_symbols(program, symbol_table);
  if (!ok)
    return -1;


  std::string output_filename {argv[2]};
  std::ofstream out {output_filename, std::ios::binary};
  if (!out.is_open()) {
    std::cerr << "failed to open " << output_filename << '\n';
    return -1;
  }

  serialize_program(program, symbol_table, 0x8000, out);

  out.close();
  return 0;
}
