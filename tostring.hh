#include <map>
#include <string>

#include "codec.hh"
#include "mneumonic.hh"

namespace tostring {
  const std::unordered_map<isa::op, std::string_view>& op();
  const std::unordered_map<isa::mode, std::string_view>& mode();
}
