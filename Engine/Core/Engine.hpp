#pragma once

#include <Engine/Core/ModuleLoader.hpp>
#include <Engine/Window/WindowModule.hpp>

#include <Engine/Debug/CrashHandler.hpp>
#include <Engine/Debug/StackTraceHandler.hpp>
#include <Engine/Utils/Parsers/INIHandler.hpp>

namespace hx3d {

namespace Window {
  class Game;
}

namespace Core {

class Engine {
public:
  Engine();
  ~Engine();

  void runGame(Window::Game* p_game);

private:
  ModuleLoader m_loader;

  Debug::CrashHandler m_crashHandler;
  Debug::StackTraceHandler m_stackTraceHandler;

  Window::WindowModule m_windowModule;
};

}
}
