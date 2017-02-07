#pragma once

namespace hx3d {
namespace Graphics {

class Shader;
class Drawable {
public:
  Drawable();
  virtual ~Drawable() = 0;

  virtual void draw(Shader& p_shader) = 0;
};

}
}
