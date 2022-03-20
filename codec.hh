#pragma once

#include <cstdint>
#include <map>
#include <tuple>

#include "isa.hh"

namespace codec {
  extern const std::map<std::tuple<isa::op, isa::mode>, uint8_t>& encode();
  const std::map<uint8_t, std::tuple<isa::op, isa::mode>>& decode();
}
