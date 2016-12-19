#include <Engine/Utils/Parsers/INIHandler.hpp>
#include <Engine/Utils/Parsers/INIParser.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Utils/IO/File.hpp>

#include <Engine/Core/Root.hpp>

namespace hx3d {
namespace Utils {

struct INIHandler::Impl {
  File m_file;
  INIParser m_parser;
};

INIHandler::INIHandler():
  m_impl(Utils::MakeUniquePtr<Impl>())
{}

INIHandler::~INIHandler() = default;

void INIHandler::parseFromFile(const std::string& p_path) {
  auto& loader = Root::Instance().getFileLoader();

  m_impl->m_file = loader.syncLoad(p_path);
  m_impl->m_parser.parse(m_impl->m_file.getStrContent());
}

const INIParser& INIHandler::getParser() const {
  return m_impl->m_parser;
}

}
}
