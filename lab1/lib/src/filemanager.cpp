#include "filemanager.hpp"
#include "libzippp.h"

#include <fstream>

namespace security_soft {

void filemanager::create_file(const boost::filesystem::path& filename) {
  boost::filesystem::ofstream{filename};
}

void filemanager::delete_file(const boost::filesystem::path& filename) {
  boost::filesystem::remove(filename);
}

void filemanager::create_archive(const boost::filesystem::path& filename) {
  create_file(filename);
  libzippp::ZipArchive zip{filename.string()};
  zip.open(libzippp::ZipArchive::New);
  zip.close();
}

void filemanager::add_file_to_archive(const boost::filesystem::path& archive, const boost::filesystem::path& file) {
  libzippp::ZipArchive zip{archive.string()};
  zip.open(libzippp::ZipArchive::Write);
  zip.addFile(file.filename().string(), file.string());
}

void filemanager::delete_file_from_archive(const boost::filesystem::path& archive, const std::string& filename) {
  libzippp::ZipArchive zip{archive.string()};
  zip.open(libzippp::ZipArchive::Write);
  zip.deleteEntry(filename);
}

file_info filemanager::get_file_info(const boost::filesystem::path& archive, const std::string& filename) {
  libzippp::ZipArchive zip{archive.string()};
  zip.open(libzippp::ZipArchive::ReadOnly);

  const auto entry = zip.getEntry(filename);

  file_info info;

  info.name = entry.getName();
  info.index = entry.getIndex();
  info.timestamp = entry.getDate();
  info.crc = entry.getCRC();

  return info;
}

std::string filemanager::read_all(const boost::filesystem::path& filename) {
  std::string result;
  boost::filesystem::ifstream fin{filename};

  for (std::string line; std::getline(fin, line);) {
    result += line + '\n';
  }

  return result;
}

} // namespace security_soft