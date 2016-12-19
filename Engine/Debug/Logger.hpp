#pragma once

#include <Engine/Text/Format.hpp>

#include <mutex>

namespace hx3d {
namespace Debug {

class Logger {
public:
  enum Level {
    kVerbose = 0,
    kDebug,
    kInfo,
    kWarn,
    kError,
    kCritical,
  };

public:
  Logger(const char* p_name, const Level p_defaultLogLevel = kCritical);
  ~Logger();

  void setLogLevel(const Level p_level);
  const Level& getLogLevel() const;


  template <class... Args>
  void log(const Level p_level, const char* p_message, Args&&... p_args) const {
    logv(true, true, p_level, p_message, p_args...);
  }

  template <class... Args>
  void rawLog(const Level p_level, const char* p_message, Args&&... p_args) const {
    logv(false, false, p_level, p_message, p_args...);
  }

  template <class... Args>
  void error(const char* p_message, Args&&... p_args) const {
    logv(true, true, kError, p_message, p_args...);
  }

  template <class... Args>
  void critical(const char* p_message, Args&&... p_args) const {
    logv(true, true, kCritical, p_message, p_args...);
  }

  template <class... Args>
  void debug(const char* p_message, Args&&... p_args) const {
    logv(true, true, kDebug, p_message, p_args...);
  }

  template <class... Args>
  void verbose(const char* p_message, Args&&... p_args) const {
    logv(true, true, kVerbose, p_message, p_args...);
  }

  template <class... Args>
  void warn(const char* p_message, Args&&... p_args) const {
    logv(true, true, kWarn, p_message, p_args...);
  }

  template <class... Args>
  void info(const char* p_message, Args&&... p_args) const {
    logv(true, true, kInfo, p_message, p_args...);
  }

  static const char* GetLevelDisplay(const Level p_level);

private:
  template <class... Args>
  void logv(const bool p_newline, const bool p_criticalExcept, const Level p_level, const char* p_message, Args&&... p_args) const {
    if (p_level < m_level)
      return;

    std::lock_guard<std::mutex> guard(m_mutex);
    logmessage(p_newline, p_criticalExcept, p_level, Text::Format(p_message, p_args...));
  }

  void logmessage(const bool p_newline, const bool p_criticalExcept, const Level p_level, const std::string& p_message) const;

  const char* m_name;
  Level m_level;
  mutable std::mutex m_mutex;
};

}
}
