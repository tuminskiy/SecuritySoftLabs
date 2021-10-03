#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <set>

#include <QCryptographicHash>
#include <QString>

#include "ranges.hpp"

std::string to_str_n26(std::size_t value);


int main() {
  using namespace security_soft;

  const unsigned int n_chunks = std::thread::hardware_concurrency();

  range_number main_rn {
    551881,   // 'aaaaa'
    14900788, // 'aaaaaa'
  };

  std::vector<range_number> sub_rn(n_chunks);
  chunks(main_rn, n_chunks, std::begin(sub_rn));

  auto pred = [](std::string_view sv) {
    using namespace std::string_view_literals;

    static const std::set<std::string_view> sha256s = {
      "1115dd800feaacefdf481f1f9070374a2a81e27880f187396db67958b207cbad"sv,
      "3a7bd3e2360a3d29eea436fcfb7e44c735d117c42d1c1835420b6b9942dd4f1b"sv,
      "74e1bb62f8dabb8125a58852b63bdf6eaef667cb56ac7f7cdba6d7305c50a22f"sv
    };

    return sha256s.find(sv) != sha256s.end();
  };

  auto create_task = [&pred](const range_number& rn) {
    return [&]() {
      for (auto i = rn.start; i <= rn.end; ++i) {
        const std::string str = to_str_n26(i);
        const QByteArray bytes = str.data();
        const std::string hash = QCryptographicHash::hash(
          bytes,
          QCryptographicHash::Algorithm::Sha256
        ).toHex().toStdString();

        if (pred(hash)) {
          std::cout << str << '\n';
        }
      }
    };
  };

  std::vector<std::thread> thread_pool;
  thread_pool.reserve(n_chunks);

  std::cout << "start\n";

  for (const range_number& rn : sub_rn) {
    std::thread t(create_task(rn));
    thread_pool.push_back(std::move(t));
  }

  for (std::thread& t : thread_pool) {
    t.join();
  }

  std::cout << "end\n";

  return 0;
}

std::string to_str_n26(std::size_t value) {
  static constexpr char n26[] = "0abcdefghijklmnopqrstuvwxyz";
  constexpr std::size_t N = std::size(n26) - 1;

  std::string result;

  while (value != 0) {
    result += n26[value % N];
    value /= N;
  }

  std::reverse(result.begin(), result.end());

  return result;
}