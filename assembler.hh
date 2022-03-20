#pragma once

#include <optional>
#include <variant>
#include <vector>

#include "isa.hh"

namespace assembler {
  struct literal_t {
    ssize_t num;
  };

  struct reference_t {
    size_t symbol;
  };

  struct implied_t {
  };

  struct instruction_t {
    std::optional<size_t> symbol;
    isa::op op;
    isa::mode mode;
    std::variant<literal_t, reference_t, implied_t> value;
    size_t location;
  };

  using program_t = std::vector<instruction_t>;
}
