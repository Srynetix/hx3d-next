#include <Engine/Debug/Logging.hpp>
#include <Engine/Core/Exceptions/KeyNotFound.hpp>

#include <iostream>

namespace hx3d {
namespace Debug {

std::chrono::time_point<std::chrono::system_clock> Logging::m_startingTimePoint = std::chrono::system_clock::now();

Logging::Logging() {
  m_loggers[kCore]              = new Logger("Core", Logger::kVerbose);
  m_loggers[kWindow]            = new Logger("Window", Logger::kVerbose);
  m_loggers[kGraphics]          = new Logger("Graphics", Logger::kVerbose);
  m_loggers[kGraphicsLowLevel]  = new Logger("GraphicsLowLevel", Logger::kError);
  m_loggers[kFont]              = new Logger("Font", Logger::kVerbose);
  m_loggers[kGame]		          = new Logger("Game", Logger::kVerbose);
  m_loggers[kUtils]             = new Logger("Utils", Logger::kVerbose);
  m_loggers[kTests]             = new Logger("Tests", Logger::kVerbose);
  m_loggers[kIO]                = new Logger("IO", Logger::kVerbose);
  m_loggers[kResources]         = new Logger("Resources", Logger::kVerbose);
  m_loggers[kUI]                = new Logger("UI", Logger::kVerbose);
}

Logging::~Logging() {
  for (auto& pair: m_loggers) {
    if (pair.second) {
      delete pair.second;
    }
  }
}

void Logging::setLoggerLevel(const Category p_category, const Logger::Level p_level) {
  auto logger = m_loggers.find(p_category);
  if (logger != m_loggers.end()) {
    logger->second->setLogLevel(p_level);
  }
}

const Logger& Logging::getLogger(const Category p_category) const {
  auto logger = m_loggers.find(p_category);
  if (logger != m_loggers.end()) {
    return *(logger->second);
  }

  throw Exceptions::KeyNotFound<Logger, Category>(p_category);
}

F32 Logging::getElapsedSeconds() {
  auto now = std::chrono::system_clock::now();
  return (F32)(std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startingTimePoint).count() / 1000.f);
}

}
}
