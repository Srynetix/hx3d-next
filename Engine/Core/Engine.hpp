#pragma once

#include <Engine/Core/ModuleLoader.hpp>
#include <Engine/Window/WindowModule.hpp>

#include <Engine/Debug/CrashHandler.hpp>
#include <Engine/Debug/StackTraceHandler.hpp>

namespace hx3d {

class Engine {
public:
  Engine();
  ~Engine();

private:
  ModuleLoader m_loader;
  WindowModule m_windowModule;

  CrashHandler m_crashHandler;
  StackTraceHandler m_stackTraceHandler;
};

}
