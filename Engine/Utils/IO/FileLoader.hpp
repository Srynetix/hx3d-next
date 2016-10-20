#pragma once

#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/IO/FileHandler.hpp>
#include <queue>

namespace hx3d {
namespace Utils {

class FileLoader {
public:
  FileLoader();
  ~FileLoader();

  AsyncFileHandlerPtr asyncLoad(const std::string& p_path);
  File syncLoad(const std::string& p_path);
};

}
}
