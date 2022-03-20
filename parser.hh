#pragma once

#include <string_view>

#include "assembler.hh"

namespace parser {
  bool parse(std::string_view buf, assembler::program_t& program);
}
