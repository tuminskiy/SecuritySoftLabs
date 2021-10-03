#include "menu/error_menu.hpp"

#include <utility>

namespace security_soft {

error_menu::error_menu(std::string_view msg, menu_sptr parent)
  : base_menu({msg}, std::move(parent))
{ }

menu_sptr error_menu::process() { return parent_; }

} // namespace security_soft