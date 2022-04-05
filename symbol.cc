#include <string_view>
#include <cassert>
#include <iostream>

#include "assembler.hh"
#include "addressing_mode.hh"

namespace symbol {

size_t get(assembler::symbol_strings_t& symbol_strings, std::string_view s) {
  std::string key {s};
  auto find = symbol_strings.map.find(key);
  if (find == symbol_strings.map.end()) {
    std::cerr << "get new: " << s << ' ' << symbol_strings.current_symbol << '\n';
    auto insert = symbol_strings.map.insert({key, symbol_strings.current_symbol++});
    assert(insert.second);
    return (insert.first)->second;
  } else {
    return find->second;
  }
}

bool resolve(size_t link_location, assembler::program_t& program, assembler::symbol_table_t& symbol_table)
{
  size_t offset = link_location;

  for (auto prog_it = program.begin(); prog_it != program.end(); prog_it++) {
    if (std::holds_alternative<assembler::instruction_t>(*prog_it)) {
      auto& ins = std::get<assembler::instruction_t>(*prog_it);
      ins.location = offset;
      if (ins.symbol != std::nullopt) {
        auto [_, ok] = symbol_table.insert({*(ins.symbol), offset});
        if (!ok) {
          std::cerr << ins.row << ": duplicate symbol\n";
          return false;
        }
      }

      auto am_it = addressing_mode().find(ins.mode);
      assert (am_it != addressing_mode().end());
      offset += 1 + am_it->second.len;
    } else if (std::holds_alternative<assembler::blob_t>(*prog_it)) {
      auto& blob = std::get<assembler::blob_t>(*prog_it);
      blob.location = offset + 4;
      auto [_1, ok1] = symbol_table.insert({blob.symbol.start, offset});
      auto [_2, ok2] = symbol_table.insert({blob.symbol.start_l, (offset >> 0) & 0xff});
      auto [_3, ok3] = symbol_table.insert({blob.symbol.start_h, (offset >> 8) & 0xff});
      auto [_4, ok4] = symbol_table.insert({blob.symbol.size_l, (blob.buf->size() >> 0) & 0xff});
      auto [_5, ok5] = symbol_table.insert({blob.symbol.size_h, (blob.buf->size() >> 8) & 0xff});
      if (!ok1 || !ok2 || !ok3 || !ok4 || !ok5) {
        std::cerr << "duplicate blob symbol\n";
        return false;
      }
      offset += 4 + blob.buf->size();
    } else {
      assert(false);
    }
  }

  return true;
}

}
