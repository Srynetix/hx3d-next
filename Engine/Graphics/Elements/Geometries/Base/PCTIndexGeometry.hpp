#pragma once

#include <Engine/Graphics/Elements/Geometries/Base/BaseIndexGeometry.hpp>

namespace hx3d {
namespace Graphics {

class PCTIndexGeometry: public BaseIndexGeometry {
public:
  virtual void initialize() override;
  virtual void uploadBuffersToGPU() override;
  virtual void linkBuffersToShader(const Shader& p_shader) override;

  virtual GLenum getPrimitiveName() override;
  virtual U32 getVertexCount() override;

protected:
  typedef AttributeBuffer3F Position;
  typedef AttributeBuffer4F Color;
  typedef AttributeBuffer2F Texture;
};

}
}
