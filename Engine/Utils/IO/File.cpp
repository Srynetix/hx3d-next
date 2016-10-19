#include <Engine/Utils/IO/File.hpp>
#include <Engine/Core/Exceptions/FileNotFound.hpp>

#include <fstream>
#include <sstream>

namespace hx3d {
namespace Utils {

File::File():
  m_data(""),
  m_size(0)
  {}

File::~File() {
}

File::File(const File& p_file):
  m_data(p_file.m_data), m_size(p_file.m_size)
  {}

File& File::operator=(const File& p_file) {
  if (&p_file != this) {
    m_data = p_file.m_data;
    m_size = p_file.m_size;
  }

  return *this;
}

const std::string& File::getContent() const {
  return m_data;
}

const size_t File::getSize() const {
  return m_size;
}

File File::loadTextFile(const std::string& p_path) {
  std::string path(getAssetsPath() + p_path);

  std::ifstream file(path);
  if (file) {
    std::ostringstream oss("");
    oss << file.rdbuf();

    std::string content = oss.str();

    File ofile;
    ofile.m_size = content.size();
    ofile.m_data.resize(content.size());
    ofile.m_data = content;

    file.close();

    return ofile;
  }

  throw Exceptions::FileNotFound(path);
}

std::string File::getAssetsPath() {
  return "Assets/";
}

}
}
