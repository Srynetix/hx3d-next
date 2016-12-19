#pragma once

#include <Engine/Graphics/Elements/Color.hpp>
#include <Engine/Graphics/Elements/Shader.hpp>

namespace hx3d {
namespace Graphics {

class Shape {
public:
  Shape();
  void setColor(const Color color);
  const Color getColor() const;

  virtual void draw(const Shader& p_shader) = 0;

private:
  virtual void applyColor() = 0;
  Color m_color;

protected:
  bool m_colorDirty;
};

}
}
