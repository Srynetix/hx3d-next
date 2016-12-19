#include <Engine/Graphics/Elements/Shapes/Shape.hpp>
#include <Engine/Graphics/Elements/Geometries/QuadGeometry.hpp>

namespace hx3d {
namespace Graphics {

class Rectangle: public Shape {
public:
  Rectangle();

  virtual void draw(const Shader& p_shader) override;

private:
  virtual void applyColor() override;

  QuadGeometry m_geometry;
};

}
}
