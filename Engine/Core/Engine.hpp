#pragma once

#include <Engine/Utils/Memory/SmartPtrs.hpp>

namespace hx3d {

namespace Game {
  class Game;
}

namespace Core {

class Engine {
public:
  Engine();
  ~Engine();

  void bootEngine();
  void runGame(Game::Game* p_game);

private:
  HX3D_PIMPL
};

}
}
