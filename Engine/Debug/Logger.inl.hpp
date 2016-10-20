#include <Engine/Utils/Format.hpp>
#include <Engine/Core/Exceptions/CriticalError.hpp>

#include <iostream>
#include <iomanip>

namespace hx3d {
namespace Debug {

template <class... Args>
void Logger::log(const Level p_level, const char* p_message, Args&&... p_args) const {
  logv(true, true, p_level, p_message, p_args...);
}

template <class... Args>
void Logger::rawLog(const Level p_level, const char* p_message, Args&&... p_args) const {
  logv(false, false, p_level, p_message, p_args...);
}

template <class... Args>
void Logger::logv(const bool p_newline, const bool p_criticalExcept, const Level p_level, const char* p_message, Args&&... p_args) const {
  if (p_level < m_level)
    return;

  std::lock_guard<std::mutex> guard(m_mutex);

  const std::string content = Utils::Format(p_message, p_args...);

  if (p_level < kWarn) {
    std::cout << "[" << std::fixed << std::setprecision(4) << Logging::getElapsedSeconds() << "] <" << m_name << "> " << GetLevelDisplay(p_level) << ": " << content;

    if (p_newline) {
      std::cout << std::endl;
    }
  }

  else {

    if (p_criticalExcept && p_level == kCritical) {
      throw Exceptions::CriticalError(content);
    } else {
      std::cerr << "[" << std::fixed << std::setprecision(4) << Logging::getElapsedSeconds() << "] <" << m_name << "> " << GetLevelDisplay(p_level) << ": " << content;

      if (p_newline) {
        std::cerr << std::endl;
      }
    }
  }
}

template <class... Args>
void Logger::error(const char* p_message, Args&&... p_args) const {
  logv(true, true, kError, p_message, p_args...);
}

template <class... Args>
void Logger::critical(const char* p_message, Args&&... p_args) const {
  logv(true, true, kCritical, p_message, p_args...);
}

template <class... Args>
void Logger::debug(const char* p_message, Args&&... p_args) const {
  logv(true, true, kDebug, p_message, p_args...);
}

template <class... Args>
void Logger::verbose(const char* p_message, Args&&... p_args) const {
  logv(true, true, kVerbose, p_message, p_args...);
}

template <class... Args>
void Logger::warn(const char* p_message, Args&&... p_args) const {
  logv(true, true, kWarn, p_message, p_args...);
}

template <class... Args>
void Logger::info(const char* p_message, Args&&... p_args) const {
  logv(true, true, kInfo, p_message, p_args...);
}

}
}
