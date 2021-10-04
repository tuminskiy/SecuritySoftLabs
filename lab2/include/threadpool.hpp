#pragma once

#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <future>

namespace security_soft {

class threadpool {
  boost::asio::thread_pool pool_;

public:
  explicit threadpool(std::size_t max_threads);

  template <class F>
  void post(F&& f);

  template <class F>
  auto submit(F&& f) -> std::future<decltype(f())>;

  void wait();
};


template <class F>
void threadpool::post(F&& f) {
  boost::asio::post(pool_, std::forward<F>(f));
}

template <class F>
auto threadpool::submit(F&& f) -> std::future<decltype(f())> {
  std::promise<decltype(f())> promise;

  auto future = promise.get_future();

  boost::asio::post(pool_,
    [p = std::move(promise), f = std::forward<F>(f)]() mutable {
      p.set_value(f());
    }
  );

  return future;
}

} // namespace security_soft
