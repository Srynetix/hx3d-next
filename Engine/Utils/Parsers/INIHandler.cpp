#include <Engine/Utils/Parsers/INIHandler.hpp>

namespace hx3d {
namespace Utils {

INIHandler::INIHandler() {}

void INIHandler::parseFromFile(const std::string& p_path) {
  m_file = File::loadTextFile(p_path);
  m_parser.parse(m_file.getContent());
}

const INIParser& INIHandler::getParser() const {
  return m_parser;
}

}
}
