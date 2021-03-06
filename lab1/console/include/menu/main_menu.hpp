#pragma once

#include "base_menu.hpp"

namespace security_soft {

class main_menu : public base_menu, public std::enable_shared_from_this<main_menu> {
public:
  main_menu();

  menu_sptr process() override;
};

} // namespace security_soft