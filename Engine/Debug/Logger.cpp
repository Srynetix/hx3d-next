#include <Engine/Debug/Logger.hpp>
#include <Engine/Debug/Logging.hpp>

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
