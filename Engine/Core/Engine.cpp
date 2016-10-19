#include <Engine/Core/Engine.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Window/Game.hpp>

#include <EngineConfig.hpp>

using namespace hx3d;

namespace hx3d {
namespace Core {

Engine::Engine():
  m_loader(this) {

  try {
	  const auto& core_logger = HX3D_LOGGER(kCore);
    core_logger.log(Debug::Logger::kInfo, "Loading hx3d %s...", HX3D_VERSION_NAME);

    // Loading config
    core_logger.log(Debug::Logger::kInfo, "Loading engine configuration...");
    m_engineConfigHandler.parseFromFile("EngineConfig.ini");

    // Starting modules
    m_loader.startModule(&m_windowModule);

  } catch (const std::exception& e) {

    const auto& core_logger = HX3D_LOGGER(kCore);
    core_logger.error(e.what());

    m_stackTraceHandler.report();
    throw e;
  }
}

void Engine::runGame(Window::Game* p_game) {
  try {

    p_game->create();
    m_windowModule.runGame(p_game);
    p_game->dispose();

  } catch (const std::exception& e) {

    auto game_logger = HX3D_LOGGER(kGame);
    game_logger.error(e.what());

    m_stackTraceHandler.report();
    throw e;
  }
}

const Utils::INIHandler& Engine::getConfigHandler() const {
  return m_engineConfigHandler;
}

Engine::~Engine() {
  const auto& core_logger = HX3D_LOGGER(kCore);
  core_logger.log(Debug::Logger::kInfo, "Engine shutdown.");

  m_loader.endModule(&m_windowModule);
}

}
}
