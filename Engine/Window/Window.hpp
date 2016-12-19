#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Graphics/OpenGLContext.hpp>

#include <string>
#include <SDL.h>

namespace hx3d {
namespace Window {

class Game;
class Window {
public:
  Window(const U16 p_width, const U16 p_height, const std::string& p_title = "Engine", const bool p_fullScreen = false);
  ~Window();

  void displayFPS(const bool p_value);
  void runGame(Game* p_game);

private:
  U16 m_width;
  U16 m_height;
  std::string m_title;

  SDL_Window* m_window;
  Game* m_game;
  Graphics::OpenGLContext m_context;
};

}
}
