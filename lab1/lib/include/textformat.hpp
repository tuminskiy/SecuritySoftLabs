#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

namespace security_soft {

namespace parse {

template <class T> class to{};

} // namespace security_soft::parse


class text_format {
  boost::property_tree::ptree ptree_;

public:
  explicit text_format(const boost::property_tree::ptree& ptree);

  template <class T>
  T as() const;

  template <class T>
  static text_format from(const T& data);

  void save_as_json(const boost::filesystem::path& filename) const;

  void save_as_xml(const boost::filesystem::path& filename) const;
};


template <class T>
T text_format::as() const { return deserialize(ptree_, parse::to<T>{}); }

template <class T>
text_format text_format::from(const T& data) { return text_format{ serialize(data) }; }

} // namespace security_soft
