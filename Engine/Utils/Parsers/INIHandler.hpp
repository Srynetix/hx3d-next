#pragma once

#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/Parsers/INIParser.hpp>

namespace hx3d {
namespace Utils {

class INIHandler {
public:
  INIHandler();

  void parseFromFile(const std::string& p_path);

  const INIParser& getParser() const;

private:
  File m_file;
  INIParser m_parser;
};

}
}
