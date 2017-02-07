#include <Engine/Graphics/Elements/Shapes/Circle.hpp>

#include <Engine/Graphics/Elements/Texture.hpp>
#include <Engine/Debug/Logging.hpp>

namespace hx3d {
namespace Graphics {

Circle::Circle(F32 p_precision): Shape() {
  m_geometry.setPrecision(p_precision);
  m_geometry.initialize();
  m_geometry.uploadToGPU();
}

void Circle::draw(Shader& p_shader) {
  if (m_colorDirty) {
    applyColor();
    m_colorDirty = false;
  }

  Texture::Blank().bindToContext();

  m_geometry.linkToShader(p_shader);
  m_geometry.render();
}

CircleGeometry& Circle::getGeometry() {
  return m_geometry;
}

void Circle::applyColor() {
  const glm::vec4& color = this->getColor().getFloatValues();

  if (m_geometry.containsBuffer("a_color")) {
    auto& buffer = m_geometry.getAttributeStorage<AttributeBuffer4F>("a_color");
    auto size = buffer.getSize();

    buffer.clear();
    for (auto i = 0U; i < size / 4; ++i) {
      buffer.add(color.x, color.y, color.z, color.w);
    }

    buffer.uploadToGPU(Buffer::kStatic);
  }
}

}
}
