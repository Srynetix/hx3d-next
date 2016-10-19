#include <Engine/Window/ScreenLoader.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Window/Screen.hpp>

namespace hx3d {
namespace Window {

ScreenLoader::ScreenLoader():
  m_currentScreen(nullptr) {}

ScreenLoader::~ScreenLoader() {
  disposeCurrentScreen();
}

void ScreenLoader::setCurrentScreen(Screen* p_screen) {
  const auto& logger = HX3D_LOGGER(kWindow);

  if (!p_screen) {
    logger.critical("Trying to set an uninitialized screen");
  }

  else {
    disposeCurrentScreen();

    logger.info("Loading new screen: %p", p_screen);
    m_currentScreen = p_screen;
    m_currentScreen->create();
  }
}

Screen* ScreenLoader::getCurrentScreen() {
  if (!m_currentScreen) {
    const auto& logger = HX3D_LOGGER(kWindow);
    logger.critical("Trying to fetch an uninitialized screen");
  }

  return m_currentScreen;
}

void ScreenLoader::disposeCurrentScreen() {
  if (m_currentScreen) {
    const auto& logger = HX3D_LOGGER(kWindow);

    logger.info("Disposing screen: %p", m_currentScreen);
    m_currentScreen->dispose();
    m_currentScreen = nullptr;
  }
}

}
}
