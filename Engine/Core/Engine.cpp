#include <Engine/Core/Engine.hpp>
#include <Engine/Core/Root.hpp>

#include <Engine/Game/Game.hpp>

#include <Engine/Window/WindowModule.hpp>

#include <Engine/Utils/Parsers/INIHandler.hpp>

#include <Engine/Debug/Logging.hpp>
#include <Engine/Debug/CrashHandler.hpp>
#include <Engine/Debug/StackTraceHandler.hpp>

#include <EngineConfig.hpp>

namespace hx3d {
namespace Core {

struct Engine::Impl {
  Debug::CrashHandler m_crashHandler;
};

Engine::Engine():
  HX3D_PIMPL_INIT() {}

void Engine::bootEngine() {
  try {
    const auto& core_logger = HX3D_LOGGER(kCore);
    core_logger.info("Loading hx3d %s...", HX3D_VERSION_NAME);
    core_logger.info("Initializing Root...");

    // Initialize and starting Root
    Root::Initialize();
    Root::Instance().Start();

  } catch (const std::exception& e) {
    Root::Instance().AbortOnException(e);
  }
}

void Engine::runGame(Game::Game* p_game) {
  try {
    auto& windowModule = Root::Instance().getModule<Window::WindowModule>();

    p_game->create();
    windowModule.runGame(p_game);
    p_game->dispose();

  } catch (const std::exception& e) {
    Root::Instance().AbortOnException(e);
  }
}

Engine::~Engine() {
  const auto& core_logger = HX3D_LOGGER(kCore);
  core_logger.log(Debug::Logger::kInfo, "Engine shutdown.");

  Root::Release();
}

}
}
