#pragma once

#include <Engine/Graphics/Elements/Geometries/Base/BaseArrayGeometry.hpp>

namespace hx3d {
namespace Graphics {

class CircleGeometry: public BaseArrayGeometry {
public:
  CircleGeometry();
  virtual void initializeBuffers() override;
  virtual void uploadBuffersToGPU() override;
  virtual void linkBuffersToShader(const Shader& p_shader) override;

  virtual GLenum getPrimitiveName() override;
  virtual U32 getVertexCount() override;

  void setPrecision(const F32 p_step);

private:
  typedef AttributeBuffer3F Position;
  typedef AttributeBuffer4F Color;

  F32 m_precision;
};

}
}
