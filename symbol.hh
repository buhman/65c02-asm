#include <string_view>

#include "assembler.hh"

namespace symbol {

size_t get(assembler::symbol_strings_t& symbol_strings, std::string_view s);

bool resolve(size_t link_location, assembler::program_t& program, assembler::symbol_table_t& symbol_table);

}
