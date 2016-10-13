#include <Engine/Window/WindowModule.hpp>

#include <Engine/Window/Window.hpp>
#include <Engine/Debug/Logging.hpp>

#include <SDL.h>

namespace hx3d {

void WindowModule::setUp() {
  const auto& logger = Log.getLogger(Logging::kWindow);

  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    logger.error("SDL Init error: %s", SDL_GetError());
    exit(1);
  }

  m_window = new Window(1024, 768);
}

void WindowModule::tearDown() {
  if (m_window)
    delete m_window;

  SDL_Quit();
}

}
