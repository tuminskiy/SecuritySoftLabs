#include "menu/json_menu.hpp"
#include "menu/error_menu.hpp"
#include "filemanager.hpp"
#include "pod/some_pod.hpp"

#include <iostream>
#include <utility>
#include <numeric>

namespace security_soft {

using namespace std::string_view_literals;

json_menu::json_menu(menu_sptr parent) : base_menu({
  "1. Create json file"sv,
  "2. Serialize object to json"sv,
  "3. Read json file"sv,
  "4. Remove file"sv,
  "8. Previous menu"sv,
  "0. Exit"sv
}, std::move(parent))
{}

menu_sptr json_menu::process() {
  auto self = shared_from_this();
  menu_sptr next_menu = self;

  switch (choose()) {
    case '1': {
      filemanager::create_file(get_filename() + ".json");
    } break;

    case '2': {
      text_format::from(get_some_pod()).save_as_json(get_filename() + ".json");
    } break;

    case '3': {
      std::cout << filemanager::read_all(get_filename() + ".json");
    } break;

    case '4': {
      filemanager::delete_file(get_filename() + ".json");
    } break;

    case '8': {
      next_menu = parent_;
    } break;

    case '0': {
      next_menu = nullptr;
    } break;

    default: {
      next_menu = std::make_shared<error_menu>("Invalid choose"sv, self);
    }
  }



  return next_menu;
}

some_pod json_menu::get_some_pod() const {
  some_pod result;

  std::cout << "Id: ";
  std::cin >> result.id;

  std::cout << "Name: ";
  std::cin >> result.name;

  result.some_doubles.resize(5, 1);
  std::transform(std::cbegin(result.some_doubles), std::cend(result.some_doubles), std::begin(result.some_doubles),
    [i = 0.1](double value) mutable {
      i += 0.3;
      return value * i;;
    }
  );

  return result;
}

} // namespace security_soft