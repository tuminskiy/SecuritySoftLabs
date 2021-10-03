#include "textformat.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <sstream>

namespace security_soft {


text_format::text_format(const boost::property_tree::ptree& ptree) : ptree_(ptree) { }

void text_format::save_as_json(const boost::filesystem::path& filename) const {
  boost::filesystem::ofstream fout(filename);
  boost::property_tree::write_json(fout, ptree_);
}

void text_format::save_as_xml(const boost::filesystem::path& filename) const {
  boost::filesystem::ofstream fout(filename);
  boost::property_tree::write_xml(fout, ptree_);
}


} // namespace security_soft

