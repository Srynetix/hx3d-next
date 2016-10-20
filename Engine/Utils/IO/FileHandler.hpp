#pragma once

#include <Engine/Utils/IO/File.hpp>

#include <thread>
#include <mutex>
#include <memory>

namespace hx3d {
namespace Utils {

template <bool Async>
class FileHandler {
public:
  FileHandler();
  ~FileHandler();

  void startLoading(const std::string& p_path);

  bool isFileReady() const;
  File getFile();

private:
  bool m_ready;
  File m_file;

  mutable std::thread m_thread;
  mutable std::mutex m_mutex;

  void loadFile(const std::string& p_path);
};

typedef FileHandler<true>                 AsyncFileHandler;
typedef FileHandler<false>                SyncFileHandler;
typedef std::unique_ptr<AsyncFileHandler> AsyncFileHandlerPtr;

}
}

#include <Engine/Utils/IO/FileHandler.inl.hpp>
