#include <Engine/Graphics/Elements/Geometries/Base/PCTIndexGeometry.hpp>

namespace hx3d {
namespace Graphics {

void PCTIndexGeometry::initialize() {
  m_vertexArray.generateID();
  m_indexBuffer.generateID();

  createAttributeBuffer<Position>("a_position");
  createAttributeBuffer<Color>("a_color");
  createAttributeBuffer<Texture>("a_texture");

  initializeBuffers();
}

void PCTIndexGeometry::uploadBuffersToGPU() {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");
  auto& textureStorage = getAttributeStorage<Texture>("a_texture");
  auto& indexBuffer = m_indexBuffer;

  positionStorage.uploadToGPU(Buffer::kStatic);
  colorStorage.uploadToGPU(Buffer::kStatic);
  textureStorage.uploadToGPU(Buffer::kStatic);
  indexBuffer.uploadToGPU(Buffer::kStatic);
}

void PCTIndexGeometry::linkBuffersToShader(const Shader& p_shader) {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");
  auto& textureStorage = getAttributeStorage<Texture>("a_texture");
  auto& indexBuffer = m_indexBuffer;

  positionStorage.bindBufferWithForce();
  positionStorage.linkToShader(p_shader);
  positionStorage.bindAttribPointer();

  colorStorage.bindBufferWithForce();
  colorStorage.linkToShader(p_shader);
  colorStorage.bindAttribPointer();

  textureStorage.bindBufferWithForce();
  textureStorage.linkToShader(p_shader);
  textureStorage.bindAttribPointer();

  indexBuffer.bindBufferWithForce();
}

GLenum PCTIndexGeometry::getPrimitiveName() {
  return GL_TRIANGLES;
}

U32 PCTIndexGeometry::getVertexCount() {
  return m_indexBuffer.getSize();
}

}
}
