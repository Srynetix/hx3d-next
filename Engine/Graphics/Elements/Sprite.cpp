#include <Engine/Graphics/Elements/Sprite.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Core/Globals.hpp>

#include <Engine/Graphics/Elements/Geometries/PCTQuadGeometry.hpp>
#include <Engine/Graphics/Elements/Texture.hpp>

#include <Engine/Math/Random.hpp>
#include <Engine/Math/Constants.hpp>

namespace hx3d {
namespace Graphics {

struct Sprite::Impl {
  PCTQuadGeometry m_geometry;
  Utils::SharedPtr<Texture> m_texture;

  Impl():
    m_texture(Texture::BlankShared()) {
      m_geometry.initialize();
      m_geometry.uploadToGPU();
    }
};

Sprite::Sprite():
  HX3D_PIMPL_INIT()
{
  const U16 w = Root::Instance().getGlobals().get<U16>("win.width");
  const U16 h = Root::Instance().getGlobals().get<U16>("win.height");

  this->setPosition((F32)w/2.f, (F32)h/2.f);
  this->setScale(300.f, 300.f);
}

Sprite::~Sprite() {}

void Sprite::prepareForFramebuffer(const bool p_value) {
  if (p_value) {
    m_impl->m_geometry.setFramebufferTextureCoordinates();
    this->setZRotation(Math::kPi);
  } else {
    m_impl->m_geometry.setDefaultTextureCoordinates();
  }
}

void Sprite::setTexture(const Utils::SharedPtr<Texture>& p_texture) {
  m_impl->m_texture = p_texture;
}

Graphics::BaseGeometry& Sprite::getGeometry() {
  return m_impl->m_geometry;
}

void Sprite::draw(Shader& p_shader) {
  if (m_colorDirty) {
    applyColor();
    m_colorDirty = false;
  }

  m_impl->m_texture->bindToContext();

  m_impl->m_geometry.linkToShader(p_shader);
  p_shader.sendUniform("u_model", this->getModelMatrix());
  m_impl->m_geometry.render();
}

void Sprite::applyColor() {
  const glm::vec4& color = this->getColor().getFloatValues();

  if (m_impl->m_geometry.containsBuffer("a_color")) {
    auto& buffer = m_impl->m_geometry.getAttributeStorage<AttributeBuffer4F>("a_color");
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
