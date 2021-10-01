#pragma once

#include "base_menu.hpp"

namespace security_soft {

class error_menu : public base_menu {
public:
  explicit error_menu(std::string_view msg, menu_sptr parent);

  menu_sptr process() override;
};


} // namespace security_soft