#pragma once

#include "base_menu.hpp"

namespace security_soft {

class text_menu : public base_menu, public std::enable_shared_from_this<text_menu>  {
public:
  explicit text_menu(menu_sptr parent);

  menu_sptr process() override;

private:
  std::string input_text() const;
};

} // namespace security_soft