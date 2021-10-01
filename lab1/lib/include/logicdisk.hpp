#pragma once

#include <string>
#include <QStorageInfo>

namespace security_soft {

struct logic_disk {
  std::string name;
  std::string label;
  std::string filesystem_type;
  uint64_t total_bytes;
  uint64_t free_bytes;
};

template <class OutputIt>
OutputIt collect_logic_disks(OutputIt out_it) {
  const auto disks = QStorageInfo::mountedVolumes();

  auto transformer = [](const QStorageInfo& info) {
    logic_disk disk;

    disk.name = info.name().toStdString();
    disk.label = info.rootPath().toStdString();
    disk.filesystem_type = info.fileSystemType().toStdString();
    disk.total_bytes = info.bytesTotal();
    disk.free_bytes = info.bytesFree();

    return disk;
  };

  return std::transform(std::cbegin(disks), std::cend(disks), out_it, transformer);
}

} // namespace security_soft