#include <Engine/Core/Engine.hpp>
#include <Engine/Debug/Logging.hpp>

#include <EngineConfig.hpp>

using namespace hx3d;
const Logger& g_coreLogger = Log.getLogger(Logging::kCore);

namespace hx3d {

Engine::Engine() {
  try {

    g_coreLogger.log(Logger::kInfo, "Loading hx3d %s...", HX3D_VERSION_NAME);
    m_loader.startModule(&m_windowModule);

  } catch (const std::exception& e) {

    auto core_logger = Log.getLogger(Logging::kCore);
    core_logger.error(e.what());

    m_stackTraceHandler.report();
    throw e;
  }
}

Engine::~Engine() {
  g_coreLogger.log(Logger::kInfo, "Engine shutdown.");

  m_loader.endModule(&m_windowModule);
}

}
