#pragma once

#include <Engine/Utils/Memory/SmartPtrs.hpp>

namespace hx3d {

namespace Window {
  class Game;
}

namespace Core {

class Engine {
public:
  Engine();
  ~Engine();

  void bootEngine();
  void runGame(Window::Game* p_game);

private:
  HX3D_PIMPL
};

}
}
