#include <Tests/Common/TestGame.hpp>

void TestGame::onCreate() {
  m_screenLoader.setCurrentScreen(&m_testScreen);
}

void TestGame::onDispose() {
}
