#pragma once

#include "base_menu.hpp"

namespace security_soft {

struct some_pod;

class xml_menu : public base_menu, public std::enable_shared_from_this<xml_menu> {
public:
  explicit xml_menu(menu_sptr parent);

  menu_sptr process() override;

private:
  some_pod get_some_pod() const;
};

} // namespace security_soft