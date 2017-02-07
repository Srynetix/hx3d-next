#include <Engine/Graphics/Elements/Geometries/PCTQuadGeometry.hpp>

namespace hx3d {
namespace Graphics {

void PCTQuadGeometry::initializeBuffers() {
  auto& positionStorage = getAttributeStorage<Position>("a_position");
  auto& colorStorage = getAttributeStorage<Color>("a_color");
  auto& textureStorage = getAttributeStorage<Texture>("a_texture");
  auto& indexBuffer = m_indexBuffer;

  positionStorage.add(
    -0.5f, -0.5f, 0.f,
    0.5f, -0.5f, 0.f,
    0.5f, 0.5f, 0.f,
    -0.5f, 0.5f, 0.f
  );

  // colorStorage.add(
  //   1.f, 0.f, 0.f, 1.f,
  //   0.f, 0.f, 1.f, 1.f,
  //   0.f, 1.f, 0.f, 1.f,
  //   0.f, 1.f, 1.f, 1.f
  // );

  colorStorage.add(
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f,
    1.f, 1.f, 1.f, 1.f
  );

  textureStorage.add(
    0.f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
    0.f, 0.f
  );

  indexBuffer.add(
    0, 1, 3,
    1, 2, 3
  );
}

void PCTQuadGeometry::setFramebufferTextureCoordinates() {
  auto& textureStorage = getAttributeStorage<Texture>("a_texture");
  textureStorage.clear();
  textureStorage.add(
    1.f, 1.f,
    0.f, 1.f,
    0.f, 0.f,
    1.f, 0.f
  );

  textureStorage.uploadToGPU(Buffer::kStatic);
}

void PCTQuadGeometry::setDefaultTextureCoordinates() {
  auto& textureStorage = getAttributeStorage<Texture>("a_texture");
  textureStorage.clear();
  textureStorage.add(
    0.f, 1.f,
    1.f, 1.f,
    1.f, 0.f,
    0.f, 0.f
  );

  textureStorage.uploadToGPU(Buffer::kStatic);
}

}
}
