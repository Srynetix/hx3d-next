#pragma once

#include <Engine/Graphics/Elements/Shapes/Shape.hpp>
#include <Engine/Graphics/Elements/Geometries/CircleGeometry.hpp>

#include <Engine/Math/Constants.hpp>

namespace hx3d {
namespace Graphics {

class Circle: public Shape {
public:
  Circle(F32 p_precision = Math::kPi / 6);

  virtual void draw(Shader& p_shader) override;
  virtual CircleGeometry& getGeometry();

protected:
  virtual void applyColor() override;
  CircleGeometry m_geometry;
};

}
}
