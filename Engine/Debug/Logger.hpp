#pragma once

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
  void log(const Level p_level, const char* p_message, Args&&... p_args) const;
  template <class... Args>
  void rawLog(const Level p_level, const char* p_message, Args&&... p_args) const;

  template <class... Args>
  void error(const char* p_message, Args&&... p_args) const;
  template <class... Args>
  void critical(const char* p_message, Args&&... p_args) const;
  template <class... Args>
  void debug(const char* p_message, Args&&... p_args) const;
  template <class... Args>
  void verbose(const char* p_message, Args&&... p_args) const;
  template <class... Args>
  void warn(const char* p_message, Args&&... p_args) const;
  template <class... Args>
  void info(const char* p_message, Args&&... p_args) const;

  static const char* GetLevelDisplay(const Level p_level);

private:
  template <class... Args>
  void logv(const bool p_newline, const bool p_criticalExcept, const Level p_level, const char* p_message, Args&&... p_args) const;

  const char* m_name;
  Level m_level;
};

}
}

#include <Engine/Debug/Logger.inl.hpp>
