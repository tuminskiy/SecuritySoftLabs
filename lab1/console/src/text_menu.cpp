#include "text_menu.hpp"
#include "error_menu.hpp"
#include "filemanager.hpp"

#include <iostream>
#include <iomanip>
#include <utility>

namespace security_soft {

using namespace std::string_view_literals;

text_menu::text_menu(menu_sptr parent) : base_menu({
  "1. Create txt file"sv,
  "2. Write to txt file"sv,
  "3. Read from txt file"sv,
  "4. Remove file"sv,
  "8. Previous menu"sv,
  "0. Exit"sv
}, std::move(parent)) {}

menu_sptr text_menu::process() {
  const char c = choose();

  menu_sptr next_menu = shared_from_this();

  switch (c) {
    case '1': {
      filemanager::create_file(get_filename());
    } break;

    case '2': {
      const std::string filename = get_filename();
      const std::string text = input_text();
      filemanager::write_to_file(filename, text);
    } break;

    case '3': {
      std::cout << filemanager::read_all(get_filename());
    } break;

    case '4': {
      filemanager::delete_file(get_filename());
    } break;

    case '8': {
      next_menu = parent_;
    } break;

    case '0': {
      next_menu = nullptr;
    } break;

    default:
      next_menu = std::make_shared<error_menu>("Invalid choose"sv, shared_from_this());
  };

  return next_menu;
}

std::string text_menu::input_text() const {
  std::string result;

  std::cout << "Enter the text in quotes: ";
  std::cin >> std::quoted(result);

  return result;
}

} // namespace security_soft