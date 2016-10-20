#include <Engine/Utils/Parsers/INIHandler.hpp>
#include <Engine/Core/Root.hpp>
#include <Engine/Utils/IO/FileLoader.hpp>

namespace hx3d {
namespace Utils {

INIHandler::INIHandler() {}

void INIHandler::parseFromFile(const std::string& p_path) {
  auto& loader = Root::Instance().getFileLoader();

  m_file = loader.syncLoad(p_path);
  m_parser.parse(m_file.getContent());
}

const INIParser& INIHandler::getParser() const {
  return m_parser;
}

}
}
