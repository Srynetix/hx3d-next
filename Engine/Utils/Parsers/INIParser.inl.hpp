namespace hx3d {
namespace Utils {

template <class Type>
Type INIParser::extract(const std::string& p_section, const std::string& p_key) const {
  const auto& section = m_definitions.find(p_section);
  if (section == m_definitions.cend())
    throw Exceptions::KeyNotFound<INIParser, const std::string&>(p_section, "Section lookup");

  const auto& key = section->second.find(p_key);
  if (key == section->second.cend())
    throw Exceptions::KeyNotFound<INIParser, const std::string&>(p_key, "Key lookup");

  return Convert<Type>(key->second);
}

}
}
