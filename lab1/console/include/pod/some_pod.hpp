#pragma once

#include <string>

#include "textformat.hpp"

namespace security_soft {

struct some_pod {
  int id;
  std::string name;
  std::vector<double> some_doubles;
};

some_pod deserialize(const boost::property_tree::ptree& ptree, parse::to<some_pod>);

boost::property_tree::ptree serialize(const some_pod& data);


} // namespace security_soft