#pragma once

#include <Engine/Core/Types.hpp>

namespace hx3d {
namespace Game {

class Scene {
public:
  void create();

  void show();
  void hide();
  void pause();
  void resume();

  void resize(const U16 p_width, const U16 p_height);
  void update(const F32 p_delta);
  void render();

  void dispose();

protected:
  virtual void onCreate();

  virtual void onShow();
  virtual void onHide();
  virtual void onPause();
  virtual void onResume();

  virtual void onResize(const U16 p_width, const U16 p_height);
  virtual void onUpdate(const F32 p_delta);
  virtual void onRender();

  virtual void onDispose();
};

}
}
