#pragma once

#include <boost/filesystem.hpp>

namespace security_soft {

struct file_info {
  std::string name;
  uint64_t index;
  time_t timestamp;
  int crc;
};

class filemanager {
public:
  static void create_file(const boost::filesystem::path& filename);

  static void delete_file(const boost::filesystem::path& filename);

  static void create_archive(const boost::filesystem::path& filename);

  static void add_file_to_archive(const boost::filesystem::path& archive, const boost::filesystem::path& file);

  static void delete_file_from_archive(const boost::filesystem::path& archive, const std::string& filename);

  static file_info get_file_info(const boost::filesystem::path& archive, const std::string& filename);

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