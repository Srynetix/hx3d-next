#pragma once

#include <Engine/Graphics/Elements/Geometries/Base/PCTIndexGeometry.hpp>

namespace hx3d {
namespace Graphics {

class PCTQuadGeometry: public PCTIndexGeometry {
public:
  virtual void initializeBuffers() override;

  void setFramebufferTextureCoordinates();
  void setDefaultTextureCoordinates();
};

}
}
