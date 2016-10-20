#include <Engine/Debug/Logging.hpp>

namespace hx3d {
namespace Utils {

template <bool Async>
FileHandler<Async>::FileHandler() {
  m_ready = false;
}

template <bool Async>
FileHandler<Async>::~FileHandler() {}

template <>
inline void FileHandler<false>::startLoading(const std::string& p_path)
{
  const auto& logger = HX3D_LOGGER(kIO);
  logger.info("Loading sync file `%s`...", p_path);

  m_thread = std::thread(&FileHandler<false>::loadFile, this, p_path);
  m_thread.join();
}

template <>
inline void FileHandler<true>::startLoading(const std::string& p_path)
{
  const auto& logger = HX3D_LOGGER(kIO);
  logger.info("Loading async file `%s`...", p_path);

  m_thread = std::thread(&FileHandler<true>::loadFile, this, p_path);
  m_thread.detach();
}

template <bool Async>
bool FileHandler<Async>::isFileReady() const {
  std::lock_guard<std::mutex> guard(m_mutex);
  
  return m_ready;
}

template <bool Async>
File FileHandler<Async>::getFile() {
  return m_file;
}

template <>
inline void FileHandler<false>::loadFile(const std::string& p_path) {
  m_file = File::loadTextFile(p_path);
  m_ready = true;
}

template <>
inline void FileHandler<true>::loadFile(const std::string& p_path) {
  m_file = File::loadTextFile(p_path);
  m_ready = true;
}

}
}
