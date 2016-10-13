#pragma once

#include <cstdarg>

namespace hx3d {

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

  void log(const Level p_level, const char* p_message, ...) const;
  void rawLog(const Level p_level, const char* p_message, ...) const;

  void error(const char* p_message, ...) const;
  void critical(const char* p_message, ...) const;
  void debug(const char* p_message, ...) const;
  void verbose(const char* p_message, ...) const;
  void warn(const char* p_message, ...) const;
  void info(const char* p_message, ...) const;

  static const char* GetLevelDisplay(const Level p_level);

private:
  void logv(const bool p_newline, const bool p_criticalExcept, const Level p_level, const char* p_message, va_list p_args) const;

  const char* m_name;
  Level m_level;
};

}
