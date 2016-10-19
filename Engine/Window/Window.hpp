#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Graphics/OpenGLContext.hpp>

#include <SDL.h>

namespace hx3d {
namespace Window {

class Game;
class Window {
public:
  Window(const U16 p_width, const U16 p_height, const char* p_title = "Engine");
  ~Window();

  void runGame(Game* p_game);

private:
  U16 m_width;
  U16 m_height;
  const char* m_title;

  SDL_Window* m_window;
  Game* m_game;
  Graphics::OpenGLContext m_context;
};

}
}
