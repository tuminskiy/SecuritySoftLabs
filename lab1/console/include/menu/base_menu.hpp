#pragma once

#include <list>
#include <string_view>
#include <memory>

namespace security_soft {

class base_menu;

using menu_sptr = std::shared_ptr<base_menu>;

class base_menu {
  std::list<std::string_view> chooses_;

protected:
  menu_sptr parent_;

  [[nodiscard]]
  std::string get_filename() const;

public:
  base_menu(const std::initializer_list<std::string_view>&, menu_sptr parent = nullptr);

  virtual ~base_menu();

  void display() const;

  virtual menu_sptr process() = 0;

  [[nodiscard]]
  virtual char choose() const;
};

} // namespace security_soft