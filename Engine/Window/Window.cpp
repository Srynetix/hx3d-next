#include <Engine/Window/Window.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Window/Game.hpp>

#include <Engine/Core/Globals.hpp>
#include <Engine/Core/Root.hpp>

#include <Engine/Math/Random.hpp>

namespace hx3d {
namespace Window {

Window::Window(const U16 p_width, const U16 p_height, const std::string& p_title, const bool p_fullScreen):
  m_width(p_width), m_height(p_height), m_title(p_title), m_window(nullptr)
{
  const auto& logger = HX3D_LOGGER(kWindow);
  m_context.setUp();

  m_window = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_width, p_height, SDL_WINDOW_OPENGL | (p_fullScreen ? SDL_WINDOW_FULLSCREEN : 0));
  if (m_window == nullptr) {
    logger.critical("Could not create window: %s", SDL_GetError());
    exit(1);
  }

  m_context.createContext(m_window);
  m_context.setViewport(m_width, m_height);

  Graphics::OpenGLContext::disableFlag(GL_CULL_FACE);
  // Graphics::OpenGLContext::enableFlag(GL_DEPTH_TEST);

  // Blend
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  HX3D_GLOB_SET("win.width", p_width);
  HX3D_GLOB_SET("win.height", p_height);
  HX3D_GLOB_SET("win.displayFPS", true);
  HX3D_GLOB_SET("win.maxFPS", 60);
  HX3D_GLOB_SET("win.minFPS", 10);

  HX3D_GL_ERROR("post context");
}

void Window::runGame(Game* p_game) {
  bool running = true;

  F32 prevTime = SDL_GetTicks() / 1000.f;
  F32 fpsRefreshLimit = 1.f; // seconds
  F32 fpsCurrentRefresh = 0.f;

  while (running) {

    // Event fetching
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    // Framerate fixing
    S32 maxFPS = HX3D_GLOB_GET("win.maxFPS", S32);
    S32 minFPS = HX3D_GLOB_GET("win.minFPS", S32);
    F32 minFrameTime = 1.f/minFPS;
    F32 maxFrameTime = 1.f/maxFPS;

    F32 currTime = SDL_GetTicks() / 1000.f;
    F32 diff = currTime - prevTime;

    if (diff >= minFrameTime) {
      diff = minFrameTime;
    }

    if (diff < maxFrameTime) {
      diff = maxFrameTime;
    }

    p_game->update(diff);
    p_game->render();

    prevTime = currTime;
    fpsCurrentRefresh += diff;

    // FPS display
    if (fpsCurrentRefresh >= fpsRefreshLimit) {
      if (HX3D_GLOB_GET("win.displayFPS", bool)) {
        static std::string str;
        str = Text::Format("{} [FPS: {}]", m_title, static_cast<U32>(1.f/diff));
        SDL_SetWindowTitle(m_window, str.c_str());
      }

      fpsCurrentRefresh = 0.f;
    }

    m_context.swapWindow(m_window);
  }
}

Window::~Window() {
  m_context.tearDown();

  if (m_window) {
    SDL_DestroyWindow(m_window);
  }
}

}
}
