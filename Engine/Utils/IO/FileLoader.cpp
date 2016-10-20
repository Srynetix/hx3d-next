#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

namespace hx3d {
namespace Utils {

FileLoader::FileLoader() {}
FileLoader::~FileLoader() {}

AsyncFileHandlerPtr FileLoader::asyncLoad(const std::string& p_path) {
  auto loader = MakeUniquePtr<AsyncFileHandler>();
  loader->startLoading(p_path);

  return loader;
}

File FileLoader::syncLoad(const std::string& p_path) {
  SyncFileHandler loader;
  loader.startLoading(p_path);

  return loader.getFile();
}

}
}
