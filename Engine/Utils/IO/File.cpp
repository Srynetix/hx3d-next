#include <Engine/Utils/IO/File.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Core/Exceptions/FileNotFound.hpp>

#include <fstream>
#include <sstream>

namespace hx3d {
namespace Utils {

File::File():
  m_data(nullptr),
  m_string(""),
  m_size(0),
  m_type(kBinary)
  {}

File::~File() {}

File::File(File&& p_file) {
  m_size = p_file.m_size;
  m_data = p_file.m_data;
  m_string = p_file.m_string;
  m_type = p_file.m_type;

  p_file.m_size = 0;
  p_file.m_data = nullptr;
  p_file.m_string = "";
}

File& File::operator=(File&& p_file) {
  if (&p_file != this) {
    m_size = p_file.m_size;
    m_data = p_file.m_data;
    m_string = p_file.m_string;
    m_type = p_file.m_type;

    p_file.m_size = 0;
    p_file.m_data = nullptr;
    p_file.m_string = "";
  }

  return *this;
}

const std::string& File::getStrContent() const {
  return m_string;
}

char* File::getContent() const {
  return m_data;
}

unsigned char* File::getUContent() const {
  return reinterpret_cast<unsigned char*>(m_data);
}

const size_t File::getSize() const {
  return m_size;
}

void File::setRawValues(char* p_data, const size_t p_size, const ContentType p_type) {
  m_data = p_data;
  m_type = p_type;
  m_size = p_size;

  m_string = std::string(m_data, m_size);
}

File File::loadFile(const std::string& p_path, const ContentType p_type) {
  File ofile;
  std::string path(getAssetsPath() + p_path);

  std::ifstream file(path, (p_type == kASCII ? std::ios::in : std::ios::binary | std::ios::ate));
  if (file) {
    if (p_type == kASCII) {
      std::ostringstream oss("");
      oss << file.rdbuf();
      ofile.m_string = oss.str();
      ofile.m_size = ofile.m_string.size();

    } else {
      ofile.m_size = file.tellg();
      ofile.m_data = new char[ofile.m_size];

      file.seekg(0, std::ios::beg);
      file.read(ofile.m_data, ofile.m_size);
      file.close();

      ofile.m_string = std::string(ofile.m_data, ofile.m_size);
    }

  } else {
    throw Exceptions::FileNotFound(path);
  }

  ofile.m_type = p_type;
  return ofile;
}

std::string File::getAssetsPath() {
  return "Assets/";
}

}
}
