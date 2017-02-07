#include <Engine/Graphics/Elements/Geometries/CircleGeometry.hpp>

#include <Engine/Math/Constants.hpp>

namespace hx3d {
namespace Graphics {

CircleGeometry::CircleGeometry():
  m_precision(Math::kPi / 6) {}

void CircleGeometry::initializeBuffers() {
  createAttributeBuffer<Position>("a_position");
  createAttributeBuffer<Color>("a_color");
  U32 steps = static_cast<U32>((2 * Math::kPi) / m_precision) + 1;

  auto& positionStorage = getAttributeStorage<Position>("a_position");
  for (auto i = 0U; i < steps; ++i) {
    F32 v = i * m_precision;
    positionStorage.add(std::cos(v), std::sin(v), 0.f);
  }

  auto& colorStorage = getAttributeStorage<Color>("a_color");
  for (auto i = 0U; i < steps; ++i) {
    colorStorage.add(1.f, 1.f, 1.f, 1.f);
  }
}

void CircleGeometry::setPrecision(const F32 p_step) {
  m_precision = p_step;

  // Reupload ?
}

void CircleGeometry::uploadBuffersToGPU() {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");

  positionStorage.uploadToGPU(Buffer::kStatic);
  colorStorage.uploadToGPU(Buffer::kStatic);
}

void CircleGeometry::linkBuffersToShader(const Shader& p_shader) {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");

  positionStorage.bindBuffer();
  positionStorage.linkToShader(p_shader);
  positionStorage.bindAttribPointer();

  colorStorage.bindBuffer();
  colorStorage.linkToShader(p_shader);
  colorStorage.bindAttribPointer();
}

GLenum CircleGeometry::getPrimitiveName() {
  return GL_TRIANGLE_FAN;
}

U32 CircleGeometry::getVertexCount() {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  return positionStorage.getSize();
}

}
}
