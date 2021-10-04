#include "threadpool.hpp"

namespace security_soft {

threadpool::threadpool(std::size_t max_threads)
  : pool_{ max_threads }
{}

void threadpool::wait() { pool_.wait(); }

} // namespace security_soft
