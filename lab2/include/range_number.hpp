#pragma once

#include <cstddef>

namespace security_soft {

struct range_number {
  std::size_t start;
  std::size_t end;
};


template <class OutputIt>
constexpr OutputIt split_on_chunks(const range_number& rn, std::size_t n_chunk, OutputIt out_it) {
  const std::size_t numbers_in_range = rn.end - rn.start;

  const std::size_t min_chunk_size = numbers_in_range / n_chunk;
  std::size_t n_chunks_aprox_size = numbers_in_range % n_chunk;

  std::size_t next_range_start = rn.start;

  for (std::size_t i = 0; i < n_chunk; ++i) {
    range_number sub_rn {
      next_range_start,
      next_range_start + min_chunk_size - 1
    };

    if (n_chunks_aprox_size > 0) {
      ++sub_rn.end;
      --n_chunks_aprox_size;
    }

    next_range_start = sub_rn.end + 1;
    *out_it++ = sub_rn;
  }

  return out_it;
}


} // namespace security_soft