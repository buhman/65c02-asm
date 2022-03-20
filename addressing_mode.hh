#pragma once

#include <functional>
#include <unordered_map>

#include "isa.hh"

struct addressing_mode_t {
  size_t len;
  std::function<bool(ssize_t)> valid;
};

std::unordered_map<isa::mode, addressing_mode_t>& addressing_mode();
