#pragma once

#include <Engine/Game/Game.hpp>
#include <Tests/Common/Scenes/TestScene.hpp>
#include <Tests/Common/Scenes/GUIScene.hpp>
#include <Tests/Common/Scenes/TweenScene.hpp>

using namespace hx3d;

class TestGame: public Game::Game {
protected:
  virtual void onCreate() override;
  virtual void onDispose() override;
  virtual void onRender() override;

private:
  // TestScene m_testScene;
  // GUIScene m_guiScene;
  TweenScene m_tweenScene;
};
