#include <iostream>
#include <iterator>

#include "main_menu.hpp"

int main() {
  using namespace security_soft;

  char choose = '0';
  menu_sptr current_menu = std::make_shared<main_menu>();

  do {
    current_menu->display();

    current_menu = current_menu->process();
  } while (current_menu);

  return 0;
}
