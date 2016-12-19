#pragma once

#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/IO/FileHandler.hpp>

namespace hx3d {
namespace Utils {

class FileLoader {
public:
  FileLoader();
  ~FileLoader();

  FileHandlerPtr asyncLoad(const std::string& p_path, const File::ContentType p_type = File::kASCII);
  File syncLoad(const std::string& p_path, const File::ContentType p_type = File::kASCII);
};

}
}
