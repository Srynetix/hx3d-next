#pragma once

namespace hx3d {
namespace Window {

class Screen;
class ScreenLoader {
public:
  ScreenLoader();
  ~ScreenLoader();

  void setCurrentScreen(Screen* p_screen);
  Screen* getCurrentScreen();

private:
  Screen* m_currentScreen;

  void disposeCurrentScreen();
};

}
}
