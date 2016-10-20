#include <Tests/Common/TestGame.hpp>

TestGame::TestGame() {}

void TestGame::onCreate() {
  m_screenLoader.setCurrentScreen(&m_testScreen);
}

void TestGame::onDispose() {
}
