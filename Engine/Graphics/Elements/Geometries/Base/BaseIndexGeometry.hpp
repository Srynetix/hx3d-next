#pragma once

#include <Engine/Graphics/Elements/Geometries/Base/BaseGeometry.hpp>
#include <Engine/Graphics/Elements/Buffers/IndexBuffer.hpp>

namespace hx3d {
namespace Graphics {

class BaseIndexGeometry: public BaseGeometry {
protected:
  virtual void renderBuffers() override;

  virtual GLenum getPrimitiveName() = 0;
  virtual U32 getVertexCount() = 0;

  IndexBuffer16 m_indexBuffer;
};

}
}
