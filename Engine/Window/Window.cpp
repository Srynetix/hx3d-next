#include <Engine/Window/Window.hpp>
#include <Engine/Debug/Logging.hpp>

namespace hx3d {

  Window::Window(const U16 p_width, const U16 p_height, const char* p_title):
    m_width(p_width), m_height(p_height), m_title(p_title), m_window(nullptr)
  {
    const auto& logger = Log.getLogger(Logging::kWindow);

    m_context.setUp();

    m_window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_width, p_height, SDL_WINDOW_OPENGL);

    if (m_window == nullptr) {
      logger.critical("Could not create window: %s", SDL_GetError());
      exit(1);
    }

    m_context.createContext(m_window);
    m_context.setViewport(m_width, m_height);

    bool running = true;
    while (running) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          running = false;
        }
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
