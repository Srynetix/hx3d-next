#pragma once

namespace hx3d {
namespace Game {

class Scene;
class SceneLoader {
public:
  SceneLoader();
  ~SceneLoader();

  void setCurrentScene(Scene* p_scene);
  Scene* getCurrentScene();

private:
  Scene* m_currentScene;

  void disposeCurrentScene();
};

}
}
