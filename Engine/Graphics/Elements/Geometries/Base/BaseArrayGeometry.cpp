#include <Engine/Graphics/Elements/Geometries/Base/BaseArrayGeometry.hpp>

namespace hx3d {
namespace Graphics {

void BaseArrayGeometry::renderBuffers() {
  glDrawArrays(getPrimitiveName(), 0, getVertexCount());
}

}
}
