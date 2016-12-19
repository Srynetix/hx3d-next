#include <Engine/Window/WindowModule.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Window/Window.hpp>
#include <Engine/Window/Game.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Utils/Parsers/INIParser.hpp>
#include <Engine/Utils/Parsers/INIHandler.hpp>

#include <SDL.h>

namespace hx3d {
namespace Window {

void WindowModule::setUp() {
  const auto& logger = HX3D_LOGGER(kWindow);

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    logger.error("SDL Init error: %s", SDL_GetError());
    exit(1);
  }

  // Window size and title
  const auto& config_handler = Root::Instance().getEngineConfiguration();
  const auto& config_parser = config_handler.getParser();
  U32 width = config_parser.extract<U32>("window", "width");
  U32 height = config_parser.extract<U32>("window", "height");
  std::string title = config_parser.extract<std::string>("window", "title");
  bool fullscreen = config_parser.extract<bool>("window", "fullscreen");

  m_window = new Window(width, height, title.c_str(), fullscreen);
}

void WindowModule::tearDown() {
  if (m_window)
    delete m_window;

  SDL_Quit();
}

void WindowModule::runGame(Game* p_game) {
  m_window->runGame(p_game);
}

}
}
