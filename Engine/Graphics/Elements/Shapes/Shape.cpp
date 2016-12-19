#include <Engine/Graphics/Elements/Shapes/Shape.hpp>

namespace hx3d {
namespace Graphics {

Shape::Shape():
  m_color(Color::Black),
  m_colorDirty(true)
  {}

void Shape::setColor(const Color p_color) {
  if (p_color != m_color) {
    m_color = p_color;
    m_colorDirty = true;
  }
}

const Color Shape::getColor() const {
  return m_color;
}

}
}
