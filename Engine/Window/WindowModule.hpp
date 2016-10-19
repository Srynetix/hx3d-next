#pragma once

#include <Engine/Core/Module.hpp>

namespace hx3d {

namespace Core {
  class Engine;
}

namespace Window {

class Window;
class Game;
class WindowModule: public Core::Module {
public:
  virtual void setUp(Core::Engine* p_engine) override;
  virtual void tearDown() override;

  void runGame(Game* p_game);

private:
  Window* m_window;
};

}
}
