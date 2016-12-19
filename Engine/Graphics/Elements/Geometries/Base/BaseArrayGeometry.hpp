#pragma once

#include <Engine/Graphics/Elements/Geometries/Base/BaseGeometry.hpp>

namespace hx3d {
namespace Graphics {

class BaseArrayGeometry: public BaseGeometry {
protected:
  virtual void renderBuffers() override;

  virtual GLenum getPrimitiveName() = 0;
  virtual U32 getVertexCount() = 0;
};

}
}
