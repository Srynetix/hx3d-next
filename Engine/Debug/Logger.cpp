#include <Engine/Debug/Logger.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Core/Exceptions/CriticalError.hpp>

#include <iostream>
#include <iomanip>

namespace hx3d {
namespace Debug {

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

void Logger::logmessage(const bool p_newline, const bool p_criticalExcept, const Level p_level, const std::string& p_message) const {
  if (p_level < kWarn) {
    std::cout << "[" << std::fixed << std::setprecision(4) << Logging::getElapsedSeconds() << "] <" << m_name << "> " << GetLevelDisplay(p_level) << ": " << p_message;

    if (p_newline) {
      std::cout << std::endl;
    }
  }

  else {

    if (p_criticalExcept && p_level == kCritical) {
      throw Exceptions::CriticalError(p_message);
    } else {
      std::cerr << "[" << std::fixed << std::setprecision(4) << Logging::getElapsedSeconds() << "] <" << m_name << "> " << GetLevelDisplay(p_level) << ": " << p_message;

      if (p_newline) {
        std::cerr << std::endl;
      }
    }
  }
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
}
