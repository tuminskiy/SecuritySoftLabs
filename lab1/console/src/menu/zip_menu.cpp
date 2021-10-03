#include "menu/zip_menu.hpp"
#include "menu/error_menu.hpp"
#include "filemanager.hpp"

#include <iostream>

namespace security_soft {

using namespace std::string_view_literals;

zip_menu::zip_menu(menu_sptr parent) : base_menu({
  "1. Create zip archive"sv,
  "2. Add file to zip archive"sv,
  "3. Get file info from zip archive"sv,
  "4. Remove file from zip archive"sv,
  "5. Remove zip archive"sv,
  "8. Previous menu"sv,
  "0. Exit"sv
}, std::move(parent)) {}

menu_sptr zip_menu::process()  {
  auto self = shared_from_this();
  menu_sptr next_menu = self;

  switch (choose()) {
    case '1': {
      filemanager::create_archive(get_filename() + ".zip");
    } break;

    case '2': {
      std::cout << "Archive - ";
      const auto archive = get_filename() + ".zip";
      filemanager::add_file_to_archive(archive, get_filename());
    } break;

    case '3': {
      std::cout << "Archive - ";
      const auto archive = get_filename() + ".zip";
      const file_info info = filemanager::get_file_info(archive, get_filename());
      std::cout << "Name: " << info.name << '\n'
                << "Timestamp: " << info.timestamp << '\n'
                << "Index: " << info.index << '\n'
                << "Crc: " << info.crc << '\n';
    } break;

    case '4': {
      std::cout << "Archive - ";
      const auto archive = get_filename() + ".zip";
      filemanager::delete_file_from_archive(archive, get_filename());
    } break;

    case '5': {
      filemanager::delete_file(get_filename() + ".zip");
    } break;

    case '8': {
      next_menu = parent_;
    } break;

    case '0': {
      next_menu = nullptr;
    } break;

    default: {
      next_menu = std::make_shared<error_menu>("Invalid choose"sv, self);
    } break;
  }

  return next_menu;
}

} // namespace security_soft