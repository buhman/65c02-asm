#pragma once

#include <map>
#include <string>

#include "isa.hh"
#include "codec.hh"
#include "mneumonic.hh"

namespace fromstring {
  const std::unordered_map<std::string_view, isa::op>& op();

  const std::unordered_map<std::string_view, isa::mode>& mode();
}
