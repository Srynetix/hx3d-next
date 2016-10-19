#include <Engine/Window/Game.hpp>
#include <Engine/Window/Screen.hpp>

namespace hx3d {
namespace Window {

void Game::create() {
  onCreate();
}

void Game::show() {
  onShow();
  m_screenLoader.getCurrentScreen()->show();
}

void Game::hide() {
  onHide();
  m_screenLoader.getCurrentScreen()->hide();
}

void Game::pause() {
  onPause();
  m_screenLoader.getCurrentScreen()->pause();
}

void Game::resume() {
  onResume();
  m_screenLoader.getCurrentScreen()->resume();
}

void Game::resize(const U16 p_width, const U16 p_height) {
  onResize(p_width, p_height);
  m_screenLoader.getCurrentScreen()->resize(p_width, p_height);
}

void Game::update(const F32 p_delta) {
  onUpdate(p_delta);
  m_screenLoader.getCurrentScreen()->update(p_delta);
}

void Game::render() {
  onRender();
  m_screenLoader.getCurrentScreen()->render();
}

void Game::dispose() {
  onDispose();
}

bool Game::isRunning() const {
  return m_running;
}

const ScreenLoader& Game::getScreenLoader() const {
  return m_screenLoader;
}

/////////////////////

void Game::onShow() {}
void Game::onHide() {}
void Game::onPause() {}
void Game::onResume() {}
void Game::onResize(const U16 p_width, const U16 p_height) {}
void Game::onUpdate(const F32 p_delta) {}
void Game::onRender() {}
void Game::onDispose() {}

}
}
