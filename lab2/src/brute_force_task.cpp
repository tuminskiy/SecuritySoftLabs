#include "brute_force_task.hpp"
#include "ns26.hpp"

#include <set>
#include <QCryptographicHash>


namespace security_soft {


brute_force_task::brute_force_task(const range_number& rn, const callback_t& callback)
  : rn_{ rn }
  , callback_{ callback }
{ }


void brute_force_task::operator() () const {
  for (auto i = rn_.start; i < rn_.end; ++i) {
    const std::string password = ns26::to_str(i);
    const std::string hash = to_sha256_hex(password);

    if (is_required_hash(hash)) {
      callback_(password);
      return;
    }
  }
}


std::string brute_force_task::to_sha256_hex(std::string_view sv) {
  const QByteArray bytes = sv.data();

  return QCryptographicHash::hash(bytes,QCryptographicHash::Algorithm::Sha256).toHex().toStdString();
}


bool brute_force_task::is_required_hash(std::string_view hash) {
  using namespace std::string_view_literals;

  static const std::set<std::string_view> sha256s = {
    "1115dd800feaacefdf481f1f9070374a2a81e27880f187396db67958b207cbad"sv,
    "3a7bd3e2360a3d29eea436fcfb7e44c735d117c42d1c1835420b6b9942dd4f1b"sv,
    "74e1bb62f8dabb8125a58852b63bdf6eaef667cb56ac7f7cdba6d7305c50a22f"sv
  };

  return sha256s.find(hash) != sha256s.end();
}

} // namespace security_soft