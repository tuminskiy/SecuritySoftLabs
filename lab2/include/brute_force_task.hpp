#pragma once

#include <string_view>
#include <functional>

#include "range_number.hpp"

namespace security_soft {

class brute_force_task {
public:
  using callback_t = std::function<void(std::string_view)>;

  explicit brute_force_task(const range_number& rn, const callback_t& callback);

  void operator() () const;

private:
  range_number rn_;
  callback_t callback_;

  static std::string to_sha256_hex(std::string_view sv);

  static bool is_required_hash(std::string_view hash);
};

} // namespace security_soft