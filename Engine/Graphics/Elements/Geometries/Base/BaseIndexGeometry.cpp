#include <Engine/Graphics/Elements/Geometries/Base/BaseIndexGeometry.hpp>

namespace hx3d {
namespace Graphics {

void BaseIndexGeometry::renderBuffers() {
  glDrawElements(getPrimitiveName(), getVertexCount(), GetOpenGLType<IndexBuffer16::ValueType>(), 0);
 }

}
}
