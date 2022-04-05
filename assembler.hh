#pragma once

#include <optional>
#include <variant>
#include <vector>
#include <memory>
#include <unordered_map>

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
    ssize_t row; // debug
  };

  struct blob_t {
    struct {
      size_t start;
      size_t start_l;
      size_t start_h;
      size_t size_l;
      size_t size_h;
    } symbol;
    size_t location;
    std::shared_ptr<std::string> buf;
  };

  using program_t = std::vector<std::variant<instruction_t, blob_t>>;

  struct symbol_strings_t {
    size_t current_symbol;
    std::unordered_map<std::string, size_t> map;
  };

  using symbol_table_t = std::unordered_map<size_t, size_t>;
}
