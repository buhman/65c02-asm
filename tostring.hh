#include <map>
#include <string>

#include "codec.hh"
#include "mneumonic.hh"

namespace tostring {
  extern const std::unordered_map<op_t, std::string_view> op;

  extern const std::unordered_map<amode_t, std::string_view> mode;
}
