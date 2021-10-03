#include "pod/some_pod.hpp"

namespace security_soft {

some_pod deserialize(const boost::property_tree::ptree& ptree, parse::to<some_pod>) {
  some_pod pod;

  pod.id = ptree.get<int>("id");
  pod.name = ptree.get<std::string>("name");

  for (const auto& item : ptree.get_child("some_doubles")) {
    pod.some_doubles.push_back(item.second.get_value<double>());
  }

  return pod;
}

boost::property_tree::ptree serialize(const some_pod& data) {
  boost::property_tree::ptree ptree;

  ptree.put("id", data.id);
  ptree.put("name", data.name);

  boost::property_tree::ptree some_doubles;
  for (const double value : data.some_doubles) {
    boost::property_tree::ptree child;
    child.put("", value);
    some_doubles.push_back({"", child});
  }

  ptree.add_child("some_doubles", some_doubles);

  return ptree;
}

} // namespace security_soft