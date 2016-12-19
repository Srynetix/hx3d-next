#pragma once

#include <Engine/Debug/Logger.hpp>
#include <Engine/Core/Types.hpp>
#include <Engine/Utils/SingletonHolder.hpp>

#include <chrono>
#include <map>

namespace hx3d {
namespace Debug {

class Logging {
public:
  enum Category {
    kWindow = 0,

    kGraphics,
    kGraphicsLowLevel,
    kFont,
    kResources,

    kCore,
    kGame,
    kTests,
    kUtils,
    kIO,
    kUnknown
  };

  Logging();
  ~Logging();

  void setLoggerLevel(const Category p_category, const Logger::Level p_level);
  const Logger& getLogger(const Category p_category) const;

  static F32 getElapsedSeconds();

private:
  std::map<const Category, Logger*> m_loggers;

  static std::chrono::time_point<std::chrono::system_clock> m_startingTimePoint;
};

typedef Utils::SingletonHolder<Logging> SLogging;

}
}

#ifndef HX3D_LOGGER
  #define HX3D_LOGGER(e) hx3d::Debug::SLogging::Instance().getLogger(hx3d::Debug::Logging::##e)
#endif
