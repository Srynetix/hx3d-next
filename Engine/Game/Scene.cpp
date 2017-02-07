#include <Engine/Game/Scene.hpp>

namespace hx3d {
namespace Game {

void Scene::create() {
  onCreate();
}

void Scene::show() {
  onShow();
}

void Scene::hide() {
  onHide();
}

void Scene::pause() {
  onPause();
}

void Scene::resume() {
  onResume();
}

void Scene::resize(const U16 p_width, const U16 p_height) {
  onResize(p_width, p_height);
}

void Scene::update(const F32 p_delta) {
  onUpdate(p_delta);
}

void Scene::render() {
  onRender();
}

void Scene::dispose() {
  onDispose();
}

////////////////////////

void Scene::onCreate() {}

void Scene::onShow() {}
void Scene::onHide() {}
void Scene::onPause() {}
void Scene::onResume() {}

void Scene::onResize(const U16 p_width, const U16 p_height) {}
void Scene::onUpdate(const F32 p_delta) {}
void Scene::onRender() {}

void Scene::onDispose() {}

}
}
