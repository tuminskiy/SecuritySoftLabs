#include "base_menu.hpp"

#include <iterator>
#include <iostream>
#include <utility>

namespace security_soft {

base_menu::base_menu(const std::initializer_list<std::string_view>& il, menu_sptr parent)
  : chooses_(il), parent_(std::move(parent))
{ }

base_menu::~base_menu() = default;

void base_menu::display() const {
  std::copy(
    std::cbegin(chooses_),
    std::cend(chooses_),
    std::ostream_iterator<std::string_view>{ std::cout, "\n" }
  );
}

char base_menu::choose() const {
  char c;

  std::cout << "\n> ";
  std::cin >> c;

  return c;
}

std::string base_menu::get_filename() const {
  std::string filename;

  std::cout << "Enter filename: ";
  std::cin >> filename;

  return filename;
}

} // namespace security_soft