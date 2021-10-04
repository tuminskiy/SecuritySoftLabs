#include "ns26.hpp"

#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace security_soft {

std::string ns26::to_str(std::size_t value) {
  if (value == 0)
    return "0";

  const std::size_t n_digits = static_cast<std::size_t>(std::log(value) / std::log(N)) + 1;

  std::string result;
  result.reserve(n_digits);

  while (value != 0) {
    result += base[value % N];
    value /= N;
  }

  std::reverse(result.begin(), result.end());

  return result;
}

std::size_t ns26::to_value(std::string_view sv) {
  std::size_t value = 0;

  for (const char c : sv) {
    const auto first = std::begin(base);
    const auto last = std::end(base);

    auto it = std::find(first, last, c);

    if (it == last)
      throw std::runtime_error("Incorrect digit");

    value *= N;
    value += std::distance(first, it);
  }

  return value;
}

std::size_t operator "" _ns26 (const char *s, std::size_t len) {
  return ns26::to_value(std::string_view(s, len));
}

} // namespace security_soft