#include <Engine/Game/SceneLoader.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Game/Scene.hpp>

namespace hx3d {
namespace Game {

SceneLoader::SceneLoader():
  m_currentScene(nullptr) {}

SceneLoader::~SceneLoader() {
  disposeCurrentScene();
}

void SceneLoader::setCurrentScene(Scene* p_scene) {
  const auto& logger = HX3D_LOGGER(kWindow);

  if (!p_scene) {
    logger.critical("Trying to set an uninitialized scene");
  }

  else {
    disposeCurrentScene();

    logger.info("Loading new scene: %p", p_scene);
    m_currentScene = p_scene;
    m_currentScene->create();
  }
}

Scene* SceneLoader::getCurrentScene() {
  if (!m_currentScene) {
    const auto& logger = HX3D_LOGGER(kWindow);
    logger.critical("Trying to fetch an uninitialized scene");
  }

  return m_currentScene;
}

void SceneLoader::disposeCurrentScene() {
  if (m_currentScene) {
    const auto& logger = HX3D_LOGGER(kWindow);

    logger.info("Disposing scene: %p", m_currentScene);
    m_currentScene->dispose();
    m_currentScene = nullptr;
  }
}

}
}
