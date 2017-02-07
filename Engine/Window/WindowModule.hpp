#pragma once

#include <Engine/Core/Module.hpp>

namespace hx3d {

namespace Game {
  class Game;
}

namespace Window {

class Window;
class WindowModule: public Core::Module {
public:
  virtual void setUp() override;
  virtual void tearDown() override;

  Window& getWindow();

  void runGame(Game::Game* p_game);

private:
  Window* m_window;
};

}
}
