#include <cassert>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <memory>

#include "assembler.hh"
#include "addressing_mode.hh"
#include "codec.hh"
#include "parser.hh"
#include "tostring.hh"
#include "symbol.hh"

using namespace std::literals;

void serialize_program(const assembler::program_t& program, const assembler::symbol_table_t &symbol_table, std::ostream& out)
{
  auto serialize_instruction = [&](assembler::instruction_t& ins) -> void {
    //std::cerr << "enc " << (int)ins.op << ' ' << (int)ins.mode << '\n';
    char buf[3];

    auto opcode_it = codec::encode().find({ins.op, ins.mode});
    if (opcode_it == codec::encode().end()) {
      std::cerr << ins.row << ": illegal op,mode: "
                << tostring::op().find(ins.op)->second << ' '
                << tostring::mode().find(ins.mode)->second << '\n';
      return;
    }

    /*
    std::cerr << tostring::op().find(ins.op)->second << ' '
              << tostring::mode().find(ins.mode)->second << ' '
              << std::hex << (int)opcode_it->second << '\n';
    */

    buf[0] = opcode_it->second;

    auto am_it = addressing_mode().find(ins.mode);
    assert (am_it != addressing_mode().end());

    auto get_value = [&]() -> ssize_t {
      if (std::holds_alternative<assembler::reference_t>(ins.value)) {
        assembler::reference_t ref = std::get<assembler::reference_t>(ins.value);
        auto sym_it = symbol_table.find(ref.symbol);
        if (sym_it == symbol_table.end()) {
          std::cerr << "get_value: `" << std::dec << ref.symbol << "` not found\n";
          assert(false);
        }
        auto ref_location = sym_it->second;
        if (ins.mode == isa::mode::R) {
          ssize_t offset = static_cast<ssize_t>(ref_location) - static_cast<ssize_t>(ins.location + 2);
          return offset;
        } else {
          return ref_location;
        }
      } else if (std::holds_alternative<assembler::literal_t>(ins.value)) {
        assembler::literal_t lit = std::get<assembler::literal_t>(ins.value);
        return lit.num;
      } else if (std::holds_alternative<assembler::implied_t>(ins.value)) {
        //assert (std::holds_alternative<assembler::implied_t>(ins.value));
        return 0;
      } else {
        assert (false);
      }
    };

    size_t value = get_value();
    if (!am_it->second.valid(value)) {
      std::cerr << "overflow at " << ins.row << " value: " << value << '\n';
      return;
    }

    //std::cerr << "value " << std::hex << value << ' ' << am_it->second.len << '\n';

    if (am_it->second.len >= 2)
      buf[2] = (value >> 8) & 0xff;
    if (am_it->second.len >= 1)
      buf[1] = (value >> 0) & 0xff;

    out.write(buf, 1 + am_it->second.len);
  };


  for (auto prog_it = program.cbegin(); prog_it != program.cend(); prog_it++) {
    if (std::holds_alternative<assembler::instruction_t>(*prog_it)) {
      auto ins = std::get<assembler::instruction_t>(*prog_it);
      serialize_instruction(ins);
    } else if (std::holds_alternative<assembler::blob_t>(*prog_it)) {
      auto blob = std::get<assembler::blob_t>(*prog_it);
      out.write(blob.buf->data(), blob.buf->size());
    } else {
      assert (false);
    }
  }
}

int main(int argc, char * argv[])
{
  if (argc < 3) {
    std::cerr << "argc < 3\n";
    return -1;
  }

  assembler::program_t program;
  assembler::symbol_strings_t symbol_strings;
  symbol_strings.current_symbol = 0;
  assembler::symbol_table_t symbol_table;

  bool ok;

  for (int i = 1; i < (argc - 1); i++) {
    std::cerr << "input[" << i << "]: " << argv[i] << '\n';
    std::string input_filename {argv[i]};
    std::ifstream is {input_filename, std::ios::binary | std::ios::ate};
    if (!is.is_open()) {
      std::cerr << "failed to open " << input_filename << '\n';
      return -1;
    }

    auto size = is.tellg();
    auto buf = std::make_unique<std::string>(size, '\0'); // construct string to stream size
    is.seekg(0);
    is.read(buf->data(), size);
    is.close();

    std::string_view ext = input_filename.substr(input_filename.size() - 4, 4);
    if (ext == ".asm"s) {
      ok = parser::parse(*buf, program, symbol_strings);
      if (!ok)
        return -1;
    } else if (ext == ".bin"s) {
      std::string name = input_filename.substr(0, input_filename.size() - 4);
      assembler::blob_t blob {
        .symbol = {
          .start = symbol::get(symbol_strings, "_bin_"s + name + "_start"s),
          .start_l = symbol::get(symbol_strings, "_bin_"s + name + "_start_l"s),
          .start_h = symbol::get(symbol_strings, "_bin_"s + name + "_start_h"s),
          .size_l = symbol::get(symbol_strings, "_bin_"s + name + "_size_l"s),
          .size_h = symbol::get(symbol_strings, "_bin_"s + name + "_size_h"s),
        },
        .location = 0xeeee,
        .buf = std::move(buf),
      };
      program.push_back(blob);
    } else {
      std::cerr << "unknown extension: " << ext << '\n';
      return -1;
    }
  }

  //auto link_address = 0xc000;
  auto link_address = 0x0200;

  std::cerr << "link address: " << std::hex << link_address << '\n';

  ok = symbol::resolve(link_address, program, symbol_table);
  if (!ok)
    return -1;

  std::cerr << "output: " << argv[argc - 1] << '\n';
  std::string output_filename {argv[argc - 1]};
  std::ofstream out {output_filename, std::ios::binary};
  if (!out.is_open()) {
    std::cerr << "failed to open " << output_filename << '\n';
    return -1;
  }

  serialize_program(program, symbol_table, out);

  out.close();
  return 0;
}
