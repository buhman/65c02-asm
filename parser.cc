#include <cassert>
#include <string_view>
#include <functional>
#include <iostream>
#include <variant>

#include "assembler.hh"
#include "addressing_mode.hh"
#include "fromstring.hh"
#include "isa.hh"

static bool tokenize(std::string_view buf, std::function<bool(std::string_view, ssize_t, ssize_t)> cb)
{
  auto it = buf.cbegin();
  std::optional<decltype(it)> token_begin = std::nullopt;

  ssize_t row = 0;
  ssize_t col = 0;

  while (it != buf.cend()) {
    auto c = *it;
    switch (c) {
    case '\n':
    case ' ':
      if (token_begin != std::nullopt) {
        bool ret = cb(buf.substr(*token_begin - buf.cbegin(), it - *token_begin), row, col);
        if (!ret) {
          // cb failed
          return false;
        }
        token_begin = std::nullopt;
      }
      break;
    default:
      if (token_begin == std::nullopt) {
        token_begin = it;
      }
      break;
    }

    if (c == '\n') {
      col = 0;
      row++;
    } else {
      col++;
    };
    it++;
  }

  bool ret = cb("", row + 1, col);
  if (!ret) {
    // cb failed
    return false;
  }

  return true;
}


namespace parser {
  enum class state {
    label_or_op,
    op,
    mode,
    value,
    comment,
    just_comment,
  };
}

using symbol_strings_t = std::unordered_map<std::string_view, size_t>;

namespace parser {

bool parse(std::string_view buf, assembler::program_t& program)
{
  size_t current_symbol = 0;
  symbol_strings_t ss;

  parser::state state = parser::state::label_or_op;

  auto get_symbol = [&](std::string_view s) {
    auto find = ss.find(s);
    if (find == ss.end()) {
      auto insert = ss.insert({s, current_symbol++});
      assert(insert.second);
      return (insert.first)->second;
    } else {
      return find->second;
    }
  };

  assembler::instruction_t current_instruction;
  ssize_t current_row;

  bool inside_comment = false;

  bool parsed = tokenize(buf, [&](std::string_view s, ssize_t row, ssize_t col) -> bool {
    while (true) {
      switch (state) {
      case parser::state::label_or_op:
      {
        current_row = row;
        if (s.back() == ':') {
          std::string_view key = s.substr(0, s.length() - 1);
          auto symbol = get_symbol(key);
          std::cerr << "label `" << symbol << "`\n";
          current_instruction.symbol = symbol;
          state = parser::state::op;
          return true;
        } else if (s.front() == ';') {
          state = parser::state::just_comment;
          continue;
        } else if (s.empty()) {
          // I hate myself for this dirty hack
          return true;
        } else {
          current_instruction.symbol = std::nullopt;
          [[fallthrough]];
        }
      }
      case parser::state::op:
      {
        assert(row == current_row);
        auto op_it = fromstring::op().find(s);
        if (op_it == fromstring::op().end()) {
          std::cerr << "invalid op `" << s << "`\n";
          return false;
        } else {
          current_instruction.op = op_it->second;
          std::cerr << "ok op `" << static_cast<int>(op_it->second) << "`\n";
        }
        state = parser::state::mode;
        return true;
      }
      case parser::state::mode:
      {
        assert(row == current_row);
        auto mode_it = fromstring::mode().find(s);
        if (mode_it == fromstring::mode().end()) {
          std::cerr << "invalid mode `" << s << "`\n";
          return false;
        } else {
          current_instruction.mode = mode_it->second;
          std::cerr << "ok mode `" << static_cast<int>(mode_it->second) << "`\n";
        }
        state = parser::state::value;
        return true;
      }
      case parser::state::value:
      {
        auto am_it = addressing_mode().find(current_instruction.mode);
        assert(am_it != addressing_mode().end());
        if (am_it->second.len == 0) {
          std::cerr << "no value expected\n";
          assembler::implied_t i {};
          current_instruction.value = i;
          state = parser::state::comment;
          continue;
        }

        assert(row == current_row);

        auto parse_integer = [](std::string_view s, int base) -> std::optional<ssize_t> {
          std::string value_str {s.data(), s.length()};
          size_t pos;
          ssize_t value;
          value = std::stoll(value_str, &pos, base);
          if (pos != value_str.length())
            return std::nullopt;
          else
            return value;
        };

        std::optional<ssize_t> literal;
        auto as_literal = [](ssize_t n) -> assembler::literal_t { return {n}; };
        switch (*s.cbegin()) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        {
          literal = parse_integer(s, 16);
          if (literal == std::nullopt) {
            std::cerr << row << ": invalid hex literal\n";
          }
          current_instruction.value = as_literal(*literal);
          std::cerr << "value hex literal `" << *literal << "`\n";
          break;
        }
        case 'h':
        {
          literal = parse_integer(s.substr(1, s.length() - 1), 16);
          if (literal == std::nullopt) {
            std::cerr << row << ": invalid hex literal\n";
          }
          current_instruction.value = as_literal(*literal);
          std::cerr << "value hex literal `" << *literal << "`\n";
          break;
        }
        case 'd':
        {
          literal = parse_integer(s.substr(1, s.length() - 1), 10);
          if (literal == std::nullopt) {
            std::cerr << row << ": invalid dec literal\n";
            return false;
          }
          current_instruction.value = as_literal(*literal);
          std::cerr << "value dec literal `" << *literal << "`\n";
          break;
        }
        case ':':
        {
          std::string_view key = s.substr(1, s.length() - 1);
          assembler::reference_t reference = { get_symbol(key) };
          current_instruction.value = reference;
          std::cerr << "value reference `" << reference.symbol << "`\n";
          break;
        }
        default:
          std::cerr << row << ": invalid base\n";
          return false;
        }

        state = parser::state::comment;
        return true;
      }
      case parser::state::comment:
      {
        if (row != current_row) {
          std::cerr << "push " << (int)current_instruction.op << '\n';
          inside_comment = false;
          program.push_back(current_instruction);
          state = parser::state::label_or_op;
          continue;
        }

        if (*s.cbegin() == ';') {
          inside_comment = true;
          return true;
        } else if (inside_comment) {
          return true;
        } else {
          std::cerr << row << ": expected comment\n";
          return false;
        }
      }
      case parser::state::just_comment:
      {
        if (row != current_row) {
          inside_comment = false;
          state = parser::state::label_or_op;
          continue;
        }

        if (*s.cbegin() == ';') {
          inside_comment = true;
          return true;
        } else if (inside_comment) {
          return true;
        } else {
          std::cerr << "expected comment\n";
          return false;
        }
      }
      }
    }
    return true;
  });

  return parsed;
}

}
