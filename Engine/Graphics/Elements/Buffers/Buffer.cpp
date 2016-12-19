#include <Engine/Graphics/Elements/Buffers/Buffer.hpp>

namespace hx3d {
namespace Graphics {

GLuint Buffer::m_currentArrayBufferID = 0;
GLuint Buffer::m_currentElementBufferID = 0;

Buffer::Buffer():
  Buffer(kArray) {}

Buffer::Buffer(const BufferType p_bufferType):
  m_id(0),
  m_bufferType(p_bufferType)
  {}

Buffer::~Buffer() {
  if (glIsBuffer(m_id)) {
    glDeleteBuffers(1, &m_id);
  }
}

void Buffer::generateID() {
  if (!glIsBuffer(m_id)) {
    glGenBuffers(1, &m_id);
  }
}

void Buffer::setBufferType(const BufferType p_bufferType) {
  m_bufferType = p_bufferType;
}

GLuint Buffer::getID() const {
  return m_id;
}

void Buffer::bindBufferWithForce() {
  bindBuffer(true);
}

void Buffer::bindBuffer(bool force) {
  std::string forced = force ? " with force" : "";
  if (m_bufferType == kElement && (m_currentElementBufferID != m_id || force)) {
    glBindBuffer(kElement, m_id);
    HX3D_LOGGER(kGraphicsLowLevel).debug("Element buffer %u active%s.", m_id, forced);

    m_currentElementBufferID = m_id;
  }

  else if (m_bufferType == kArray && (m_currentArrayBufferID != m_id || force)) {
    glBindBuffer(kArray, m_id);
    HX3D_LOGGER(kGraphicsLowLevel).debug("Array buffer %u active%s.", m_id, forced);

    m_currentArrayBufferID = m_id;
  }
}

void Buffer::disableBuffers(const BufferType p_bufferType) {
  if (p_bufferType == kArray && m_currentArrayBufferID != 0) {
    glBindBuffer(kArray, 0);
    HX3D_LOGGER(kGraphicsLowLevel).debug("Array buffers disabled.");
    m_currentArrayBufferID = 0;
  }

  else if (p_bufferType == kElement && m_currentElementBufferID != 0) {
    glBindBuffer(kElement, 0);
    HX3D_LOGGER(kGraphicsLowLevel).debug("Element buffers disabled.");
    m_currentElementBufferID = 0;
  }
}

}
}
