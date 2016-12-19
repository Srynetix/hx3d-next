#include <Engine/Graphics/Elements/Buffers/VertexArray.hpp>
#include <Engine/Debug/Logging.hpp>

namespace hx3d {
namespace Graphics {

GLuint VertexArray::m_currentVAID = 0;

VertexArray::VertexArray():
  m_id(0)
{}

VertexArray::~VertexArray() {
  if (glIsVertexArray(m_id)) {
    glDeleteVertexArrays(1, &m_id);
  }
}

void VertexArray::generateID() {
  if (!glIsVertexArray(m_id)) {
    glGenVertexArrays(1, &m_id);
  }
}

void VertexArray::bindToContext() {
  if (m_currentVAID != m_id) {
    glBindVertexArray(m_id);
    HX3D_LOGGER(kGraphicsLowLevel).debug("Vertex array %u active.", m_id);
    m_currentVAID = m_id;
  }
}

GLuint VertexArray::getID() const {
  return m_id;
}

void VertexArray::disableVertexArrays() {
  if (m_currentVAID != 0) {
    glBindVertexArray(0);
    HX3D_LOGGER(kGraphicsLowLevel).debug("Vertex arrays disabled.");
    m_currentVAID = 0;
  }
}

}
}
