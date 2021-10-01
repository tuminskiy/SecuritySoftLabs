#include "main_menu.hpp"
#include "error_menu.hpp"
#include "text_menu.hpp"
#include "logicdisk.hpp"

#include <iostream>

namespace security_soft {

using namespace std::string_view_literals;

std::ostream& operator<< (std::ostream& os, const logic_disk& disk) {
  return os << "Name: " << disk.name << '\n'
            << "Tag: " << disk.label << '\n'
            << "Filesystem type: " << disk.filesystem_type << '\n'
            << "Size: " << disk.total_bytes << " bytes\n"
            << "Free: " << disk.free_bytes << " bytes\n";
}

main_menu::main_menu() : base_menu({
  "1. Print logic disks info"sv,
  "2. Txt file"sv,
  "3. Json file"sv,
  "4. Xml file"sv,
  "5. Zip file"sv,
  "0. Exit"sv
}) {}

menu_sptr main_menu::process() {
  const char c = choose();

  auto self = shared_from_this();

  menu_sptr next_menu = self;

  switch (c) {
    case '1': {
      show_logic_disks_info();
    } break;

    case '2': {
      next_menu = std::make_shared<text_menu>(self);
    } break;

//    case '3': {
//
//    } break;
//
//    case '4': {
//
//    } break;
//
//    case '5': {
//
//    } break;

    case '0': {
      next_menu = nullptr;
    } break;

    default:
      next_menu = std::make_shared<error_menu>("Invalid choose"sv, shared_from_this());
  }

  return next_menu;
}

void main_menu::show_logic_disks_info() const {
  collect_logic_disks(std::ostream_iterator<logic_disk>{ std::cout, "\n" });
}

} // namespace security_soft