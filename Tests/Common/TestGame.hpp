#pragma once

#include <Engine/Window/Game.hpp>
#include <Tests/Common/TestScreen.hpp>

using namespace hx3d;

class TestGame: public Window::Game {
protected:
  virtual void onCreate() override;
  virtual void onDispose() override;

private:
  TestScreen m_testScreen;
};
