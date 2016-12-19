#include <Tests/Common/TestGame.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Graphics/TextureCache.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Utils/IO/FileLoader.hpp>
#include <fstream>

void TestGame::onCreate() {
  auto& textureCache = Root::Instance().getTextureCache();
  textureCache.loadFromFile("clouds", "Textures/Box.png");
  textureCache.loadFromFile("test", "Textures/Test2.bmp");

  m_screenLoader.setCurrentScreen(&m_testScreen);
}

void TestGame::onDispose() {
}

void TestGame::onRender() {
}
