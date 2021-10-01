#pragma once

#include <boost/filesystem.hpp>

namespace security_soft {

class filemanager {
public:
  static void create_file(const boost::filesystem::path& filename);

  static void delete_file(const boost::filesystem::path& filename);

  template <class T>
  static void write_to_file(const boost::filesystem::path& filename, const T& data);

  static std::string read_all(const boost::filesystem::path& filename);
};


template <class T>
void filemanager::write_to_file(const boost::filesystem::path& filename, const T& data) {
  boost::filesystem::ofstream fout{filename};
  fout << data;
}

} // namespace security_soft