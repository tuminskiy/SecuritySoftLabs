#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#include "brute_force_task.hpp"
#include "ns26.hpp"


void password_founded(std::string_view sv);


int main() {
  using namespace security_soft;

  range_number main_rn {
    "aaaaa"_ns26,
    "a00000"_ns26
  };

  const unsigned int n_chunks = std::thread::hardware_concurrency();

  std::vector<range_number> sub_rn(n_chunks);
  split_on_chunks(main_rn, n_chunks, std::begin(sub_rn));

  std::vector<std::thread> thread_pool;
  thread_pool.reserve(n_chunks);

  std::cout << "start brute force . . .\n\n";

  for (const range_number& rn : sub_rn) {
    brute_force_task task{ rn, password_founded };

    std::thread t{ std::move(task) };

    thread_pool.push_back(std::move(t));
  }

  for (std::thread& t : thread_pool) {
    t.join();
  }

  std::cout << "\nend brute froce\n";

  return 0;
}


void password_founded(std::string_view sv) {
  static std::mutex mtx;

  std::lock_guard lg{ mtx} ;
  std::cout << "Founded: " << sv << '\n';
}