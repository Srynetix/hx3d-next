#include <Engine/Game/Game.hpp>
#include <Engine/Game/Scene.hpp>

namespace hx3d {
namespace Game {

void Game::create() {
  onCreate();
}

void Game::show() {
  onShow();
  m_sceneLoader.getCurrentScene()->show();
}

void Game::hide() {
  onHide();
  m_sceneLoader.getCurrentScene()->hide();
}

void Game::pause() {
  onPause();
  m_sceneLoader.getCurrentScene()->pause();
}

void Game::resume() {
  onResume();
  m_sceneLoader.getCurrentScene()->resume();
}

void Game::resize(const U16 p_width, const U16 p_height) {
  onResize(p_width, p_height);
  m_sceneLoader.getCurrentScene()->resize(p_width, p_height);
}

void Game::update(const F32 p_delta) {
  onUpdate(p_delta);
  m_sceneLoader.getCurrentScene()->update(p_delta);
}

void Game::render() {
  onRender();
  m_sceneLoader.getCurrentScene()->render();
}

void Game::dispose() {
  onDispose();
}

bool Game::isRunning() const {
  return m_running;
}

const SceneLoader& Game::getSceneLoader() const {
  return m_sceneLoader;
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
