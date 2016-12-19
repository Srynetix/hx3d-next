#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

namespace hx3d {
namespace Utils {

FileLoader::FileLoader() {}
FileLoader::~FileLoader() {}

FileHandlerPtr FileLoader::asyncLoad(const std::string& p_path, const File::ContentType p_type) {
  auto loader = MakeUniquePtr<FileHandler>();
  loader->startAsyncLoading(p_path, p_type);

  return loader;
}

File FileLoader::syncLoad(const std::string& p_path, const File::ContentType p_type) {
  FileHandler loader;
  loader.startSyncLoading(p_path, p_type);

  return loader.consumeFile();
}

}
}
