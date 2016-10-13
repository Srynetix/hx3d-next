#include <Engine/Debug/Logger.hpp>
#include <Engine/Debug/String.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Core/Exceptions/CriticalError.hpp>

#include <iostream>
#include <iomanip>

namespace hx3d {

Logger::Logger(const char* p_name, const Level p_defaultLogLevel):
  m_name(p_name), m_level(p_defaultLogLevel)
{}

Logger::~Logger() {}

void Logger::setLogLevel(const Level p_level) {
  m_level = p_level;
}

const Logger::Level& Logger::getLogLevel() const {
  return m_level;
}

void Logger::log(const Level p_level, const char* p_message, ...) const {
  va_list ap;
  va_start(ap, p_message);
  logv(true, true, p_level, p_message, ap);
  va_end(ap);
}

void Logger::rawLog(const Level p_level, const char* p_message, ...) const {
  va_list ap;
  va_start(ap, p_message);
  logv(false, false, p_level, p_message, ap);
  va_end(ap);
}

void Logger::logv(const bool p_newline, const bool p_criticalExcept, const Level p_level, const char* p_message, va_list p_args) const {
  if (p_level < m_level)
    return;

  const std::string content = format(p_message, p_args);

  if (p_level < kWarn) {
    std::cout << "[" << std::fixed << std::setprecision(4) << Log.getElapsedSeconds() << "] " << GetLevelDisplay(p_level) << ": " << content;

    if (p_newline) {
      std::cout << std::endl;
    }
  }

  else {
    std::cerr << "[" << std::fixed << std::setprecision(4) << Log.getElapsedSeconds() << "] " << GetLevelDisplay(p_level) << ": " << content;

    if (p_newline) {
      std::cerr << std::endl;
    }

    if (p_criticalExcept && p_level == kCritical) {
      throw exceptions::CriticalError(content);
    }
  }
}

void Logger::error(const char* p_message, ...) const {
  va_list ap;
  va_start(ap, p_message);
  logv(true, true, kError, p_message, ap);
  va_end(ap);
}

void Logger::critical(const char* p_message, ...) const {
  va_list ap;
  va_start(ap, p_message);
  logv(true, true, kCritical, p_message, ap);
  va_end(ap);
}

void Logger::debug(const char* p_message, ...) const {
  va_list ap;
  va_start(ap, p_message);
  logv(true, true, kDebug, p_message, ap);
  va_end(ap);
}

void Logger::verbose(const char* p_message, ...) const {
  va_list ap;
  va_start(ap, p_message);
  logv(true, true, kVerbose, p_message, ap);
  va_end(ap);
}

void Logger::warn(const char* p_message, ...) const {
  va_list ap;
  va_start(ap, p_message);
  logv(true, true, kWarn, p_message, ap);
  va_end(ap);
}

void Logger::info(const char* p_message, ...) const {
  va_list ap;
  va_start(ap, p_message);
  logv(true, true, kInfo, p_message, ap);
  va_end(ap);
}

////////////////////

const char* Logger::GetLevelDisplay(const Level p_level) {
  switch (p_level) {
    case kError:
      return "ERROR";
      break;
    case kCritical:
      return "CRITICAL";
      break;
    case kDebug:
      return "DEBUG";
      break;
    case kVerbose:
      return "VERBOSE";
      break;
    case kWarn:
      return "WARN";
      break;
    case kInfo:
      return "INFO";
      break;
    default:
      return "UNKNOWN";
      break;
  }
}

}
