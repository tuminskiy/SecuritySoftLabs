#include "filemanager.hpp"



namespace security_soft {


void filemanager::create_file(const boost::filesystem::path& filename) {
  boost::filesystem::ofstream{filename};
}

void filemanager::delete_file(const boost::filesystem::path& filename) {
  boost::filesystem::remove(filename);
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