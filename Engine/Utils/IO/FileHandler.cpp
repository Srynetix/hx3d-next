#include <Engine/Utils/IO/FileHandler.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Core/Exceptions/FileNotFound.hpp>

#include <thread>
#include <mutex>

namespace hx3d {
namespace Utils {

struct FileHandler::Impl {
  bool m_ready;
  File m_file;

  mutable std::thread m_thread;
  mutable std::mutex m_mutex;

  Impl():
    m_ready(false) {}
};

FileHandler::FileHandler():
  HX3D_PIMPL_INIT() {}

FileHandler::~FileHandler() = default;

bool FileHandler::isFileReady() const {
  std::lock_guard<std::mutex> guard(m_impl->m_mutex);
  return m_impl->m_ready;
}

File&& FileHandler::consumeFile() {
  return std::move(m_impl->m_file);
}

void FileHandler::startSyncLoading(const std::string& p_path, const File::ContentType p_type)
{
  const auto& logger = HX3D_LOGGER(kIO);
  logger.info("Loading sync file `%s`...", p_path);

  m_impl->m_thread = std::thread(&FileHandler::loadFile, this, p_path, p_type);
  m_impl->m_thread.join();
}

void FileHandler::startAsyncLoading(const std::string& p_path, const File::ContentType p_type)
{
  const auto& logger = HX3D_LOGGER(kIO);
  logger.info("Loading async file `%s`...", p_path);

  m_impl->m_thread = std::thread(&FileHandler::loadFile, this, p_path, p_type);
  m_impl->m_thread.detach();
}

void FileHandler::loadFile(const std::string& p_path, const File::ContentType p_type) {
  try {
    m_impl->m_file = File::loadFile(p_path, p_type);
    m_impl->m_ready = true;
  } catch (const Exceptions::FileNotFound& p_exc) {
    Root::Instance().AbortOnException(p_exc);
  }
}

}
}
