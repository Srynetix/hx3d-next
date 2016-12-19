#include <Engine/Graphics/Elements/Shapes/Rectangle.hpp>

#include <Engine/Graphics/Elements/Texture.hpp>
#include <Engine/Debug/Logging.hpp>

namespace hx3d {
namespace Graphics {

Rectangle::Rectangle(): Shape() {
  m_geometry.initialize();
  m_geometry.uploadToGPU();
}

void Rectangle::draw(const Shader& p_shader) {
  if (m_colorDirty) {
    applyColor();
    m_colorDirty = false;
  }

  Texture::Blank().bindToContext();

  m_geometry.linkToShader(p_shader);
  m_geometry.render();
}

void Rectangle::applyColor() {
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
