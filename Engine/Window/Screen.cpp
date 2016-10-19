#include <Engine/Window/Screen.hpp>

namespace hx3d {
namespace Window {

void Screen::create() {
  onCreate();
}

void Screen::show() {
  onShow();
}

void Screen::hide() {
  onHide();
}

void Screen::pause() {
  onPause();
}

void Screen::resume() {
  onResume();
}

void Screen::resize(const U16 p_width, const U16 p_height) {
  onResize(p_width, p_height);
}

void Screen::update(const F32 p_delta) {
  onUpdate(p_delta);
}

void Screen::render() {
  onRender();
}

void Screen::dispose() {
  onDispose();
}

////////////////////////

void Screen::onCreate() {}

void Screen::onShow() {}
void Screen::onHide() {}
void Screen::onPause() {}
void Screen::onResume() {}

void Screen::onResize(const U16 p_width, const U16 p_height) {}
void Screen::onUpdate(const F32 p_delta) {}
void Screen::onRender() {}

void Screen::onDispose() {}

}
}
