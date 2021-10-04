#pragma once

#include <string>

namespace security_soft {

class ns26 {
  static constexpr char base[] = "0abcdefghijklmnopqrstuvwxyz";
  static constexpr std::size_t N = std::size(base) - 1;

public:
  static std::string to_str(std::size_t value);

  static std::size_t to_value(std::string_view sv);
};

std::size_t operator "" _ns26 (const char *s, std::size_t len);

} // namespace security_soft