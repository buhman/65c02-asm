#include <functional>
#include <unordered_map>

#include "addressing_mode.hh"
#include "isa.hh"

static bool is_uint16(ssize_t n) { return n >= 0 && n <= 65535; }

static bool is_uint8(ssize_t n) { return n >= 0 && n <= 255; }

static bool is_int8(ssize_t n) { return n >= -128 && n <= 127; }

static bool always_valid(ssize_t _) { return true; }

std::unordered_map<isa::mode, addressing_mode_t>& addressing_mode() {
  static std::unordered_map<isa::mode, addressing_mode_t> _ = {
    {isa::mode::A,    { .len = 2, .valid = is_uint16 }},
    {isa::mode::AII,  { .len = 2, .valid = is_uint16 }},
    {isa::mode::AIX,  { .len = 2, .valid = is_uint16 }},
    {isa::mode::AIY,  { .len = 2, .valid = is_uint16 }},
    {isa::mode::AI,   { .len = 2, .valid = is_uint16 }},
    {isa::mode::ACC,  { .len = 0, .valid = always_valid }},
    {isa::mode::IMM,  { .len = 1, .valid = is_uint8 }},
    {isa::mode::I,    { .len = 0, .valid = always_valid }},
    {isa::mode::R,    { .len = 1, .valid = is_int8 }},
    {isa::mode::S,    { .len = 0, .valid = always_valid }},
    {isa::mode::ZP,   { .len = 1, .valid = is_uint8 }},
    {isa::mode::ZPII, { .len = 1, .valid = is_uint8 }},
    {isa::mode::ZPX,  { .len = 1, .valid = is_uint8 }},
    {isa::mode::ZPY,  { .len = 1, .valid = is_uint8 }},
    {isa::mode::ZPI,  { .len = 1, .valid = is_uint8 }},
    {isa::mode::ZPIY, { .len = 1, .valid = is_uint8 }},
  };
  return _;
}
