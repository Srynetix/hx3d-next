#pragma once

#include <Engine/Graphics/Elements/Cameras/Camera.hpp>

namespace hx3d {
namespace Graphics {

class Camera2D: public Camera {
public:
  Camera2D();

  void setOrthographicSize(const F32 p_width, const F32 p_height);
  void setZoom(const F32 p_zoom);

  virtual void update() override;

private:
  F32 m_zoom;
};

}
}
