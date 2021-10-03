#pragma once

#include "base_menu.hpp"

namespace security_soft {

class zip_menu : public base_menu, public std::enable_shared_from_this<zip_menu> {
public:
  explicit zip_menu(menu_sptr parent);

  menu_sptr process() override;
};

} // namespace security_soft