#pragma once

#include <Engine/Debug/Logger.hpp>
#include <Engine/Core/Types.hpp>

#include <chrono>
#include <map>

namespace hx3d {

class Logging {
public:
  enum Category {
    kWindow = 0,
    kGraphics,
    kCore,
    kGame,
    kTests,
    kUnknown
  };

  Logging();
  ~Logging();

  void setLoggerLevel(const Category p_category, const Logger::Level p_level);
  const Logger& getLogger(const Category p_category) const;

  const F32 getElapsedSeconds() const;

private:
  std::map<const Category, Logger*> m_loggers;
  std::chrono::time_point<std::chrono::system_clock> m_startingTimePoint;
};

static Logging Log;

}
