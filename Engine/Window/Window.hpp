#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Graphics/OpenGLContext.hpp>
#include <Engine/Input/InputSystem.hpp>

#include <string>
#include <SDL.h>

namespace hx3d {

namespace Game {
  class Game;
}

namespace Window {

class Window {
public:
  Window(const U16 p_width, const U16 p_height, const std::string& p_title = "Engine", const bool p_fullScreen = false);
  ~Window();

  void displayFPS(const bool p_value);
  void runGame(Game::Game* p_game);
  void stop();

  const U16 getCurrentFPS() const;
  Graphics::OpenGLContext& getContext();
  Input::InputSystem& getInput();

private:
  U16 m_width;
  U16 m_height;
  U16 m_currentFPS;
  std::string m_title;
  bool m_running;

  SDL_Window* m_window;
  Game::Game* m_game;
  Graphics::OpenGLContext m_context;
  Input::InputSystem m_inputSystem;
};

}
}
