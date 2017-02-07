#include <SmashGame/Common/SmashGame.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Graphics/TextureCache.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Utils/IO/FileLoader.hpp>

#include <Engine/Utils/Algorithms/Functools.hpp>

void SmashGame::onCreate() {
  auto& textureCache = Root::Instance().getTextureCache();
  textureCache.loadFromFile("clouds", "Textures/Box.png");
  textureCache.loadFromFile("test", "Textures/Test2.bmp");

  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& noto = fontPackCache.loadFromFile("noto", "Fonts/Noto.zip");
  noto->setDefaultSize(12, 100, 100);

  // m_sceneLoader.setCurrentScene(&m_splashScene);
  m_sceneLoader.setCurrentScene(&m_stageScene);
}

void SmashGame::onDispose() {
}

void SmashGame::onRender() {
}
