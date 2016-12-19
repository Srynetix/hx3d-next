#include <Engine/Graphics/Elements/Geometries/TriangleGeometry.hpp>

namespace hx3d {
namespace Graphics {

void TriangleGeometry::initializeBuffers() {
  createAttributeBuffer<Position>("a_position");
  createAttributeBuffer<Color>("a_color");

  auto& positionStorage = getAttributeStorage<Position>("a_position");
  positionStorage.add(
    -0.5f, -0.5f, 0.f,
    0.f, 0.5f, 0.f,
    0.5f, -0.5f, 0.f
  );

  auto& colorStorage = getAttributeStorage<Color>("a_color");
  colorStorage.add(
    1.f, 0.f, 0.f, 1.f,
    0.f, 0.f, 1.f, 1.f,
    0.f, 1.f, 0.f, 1.f
  );
}

void TriangleGeometry::uploadBuffersToGPU() {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");

  positionStorage.uploadToGPU(Buffer::kStatic);
  colorStorage.uploadToGPU(Buffer::kStatic);
}

void TriangleGeometry::linkBuffersToShader(const Shader& p_shader) {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");

  positionStorage.bindBuffer();
  positionStorage.linkToShader(p_shader);
  positionStorage.bindAttribPointer();

  colorStorage.bindBuffer();
  colorStorage.linkToShader(p_shader);
  colorStorage.bindAttribPointer();
}

GLenum TriangleGeometry::getPrimitiveName() {
  return GL_TRIANGLES;
}

U32 TriangleGeometry::getVertexCount() {
  auto& positionStorage = getAttributeStorage<Position>("a_position");

  return positionStorage.getSize() / 3;
}

}
}
