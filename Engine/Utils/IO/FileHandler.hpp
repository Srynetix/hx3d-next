#pragma once

#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Utils/IO/File.hpp>

namespace hx3d {
namespace Utils {

class FileHandler {
public:
  FileHandler();
  ~FileHandler();

  void startSyncLoading(const std::string& p_path, const File::ContentType p_type = File::kASCII);
  void startAsyncLoading(const std::string& p_path, const File::ContentType p_type = File::kASCII);

  bool isFileReady() const;
  File&& consumeFile();

private:
  HX3D_PIMPL

  void loadFile(const std::string& p_path, const File::ContentType p_type);
};

using FileHandlerPtr = std::unique_ptr<FileHandler>;

}
}
