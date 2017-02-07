#pragma once

#include <Engine/Game/Game.hpp>
#include <SmashGame/Common/Scenes/SplashScene.hpp>
#include <SmashGame/Common/Scenes/StageScene.hpp>

using namespace hx3d;

class SmashGame: public Game::Game {
protected:
  virtual void onCreate() override;
  virtual void onDispose() override;
  virtual void onRender() override;

  SplashScene m_splashScene;
  StageScene m_stageScene;
};
