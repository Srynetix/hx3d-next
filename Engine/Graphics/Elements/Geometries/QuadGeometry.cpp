#include <Engine/Graphics/Elements/Geometries/QuadGeometry.hpp>

namespace hx3d {
namespace Graphics {

void QuadGeometry::initializeBuffers() {
  createAttributeBuffer<Position>("a_position");
  createAttributeBuffer<Color>("a_color");

  auto& positionStorage = getAttributeStorage<Position>("a_position");
  positionStorage.add(
    -0.5f, -0.5f, 0.f,
    0.5f, -0.5f, 0.f,
    0.5f, 0.5f, 0.f,
    -0.5f, 0.5f, 0.f
  );

  auto& colorStorage = getAttributeStorage<Color>("a_color");
  colorStorage.add(
    1.f, 0.f, 0.f, 1.f,
    0.f, 0.f, 1.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 1.f, 1.f, 1.f
  );

  auto& indexBuffer = m_indexBuffer;
  indexBuffer.generateID();
  indexBuffer.add(
    0, 1, 3,
    1, 2, 3
  );
}

void QuadGeometry::uploadBuffersToGPU() {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");
  auto& indexBuffer = m_indexBuffer;

  positionStorage.uploadToGPU(Buffer::kStatic);
  colorStorage.uploadToGPU(Buffer::kStatic);
  indexBuffer.uploadToGPU(Buffer::kStatic);
}

void QuadGeometry::linkBuffersToShader(const Shader& p_shader) {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");
  auto& indexBuffer = m_indexBuffer;

  positionStorage.bindBuffer();
  positionStorage.linkToShader(p_shader);
  positionStorage.bindAttribPointer();

  colorStorage.bindBuffer();
  colorStorage.linkToShader(p_shader);
  colorStorage.bindAttribPointer();

  indexBuffer.bindBuffer(true);
}

GLenum QuadGeometry::getPrimitiveName() {
  return GL_TRIANGLES;
}

U32 QuadGeometry::getVertexCount() {
  return m_indexBuffer.getSize();
}

}
}
