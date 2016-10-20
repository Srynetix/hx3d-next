#pragma once

#include <Engine/Core/Module.hpp>

namespace hx3d {
namespace Window {

class Window;
class Game;
class WindowModule: public Core::Module {
public:
  virtual void setUp() override;
  virtual void tearDown() override;

  void runGame(Game* p_game);

private:
  Window* m_window;
};

}
}
