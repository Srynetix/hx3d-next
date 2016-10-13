#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Graphics/OpenGLContext.hpp>
#include <SDL.h>

namespace hx3d {

class Window {
public:
  Window(const U16 p_width, const U16 p_height, const char* p_title = "Engine");
  ~Window();

private:
  U16 m_width;
  U16 m_height;
  const char* m_title;

  SDL_Window* m_window;
  OpenGLContext m_context;
};

}
