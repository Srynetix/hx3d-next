#pragma once

#include <Engine/Graphics/Elements/Buffers/Buffer.hpp>
#include <Engine/Graphics/Elements/Shader.hpp>
#include <Engine/Core/Types.hpp>

namespace hx3d {
namespace Graphics {

template <class BufferStorage, U8 Size>
class AttributeBuffer: public BufferImpl<BufferStorage> {
public:
  AttributeBuffer():
    m_type(GetOpenGLType<BufferStorage::ValueType>()),
    m_size(Size),
    m_shaderID(-1),
    m_shaderName("") {
      setBufferType(kArray);
    }

  void setShaderName(const std::string& p_name) {
    m_shaderName = p_name;
  }

  void linkToShader(const Shader& p_shader) {
    assert(m_shaderName != "");
    m_shaderID = p_shader.getAttributeLocation(m_shaderName);

    HX3D_LOGGER(kGraphicsLowLevel).debug("AttributeBuffer %u linked on attribute %s (%d)", m_id, m_shaderName, m_shaderID);
  }

  void bindAttribPointer() {
    assert(m_shaderID > -1);

    glEnableVertexAttribArray(m_shaderID);
    glVertexAttribPointer(m_shaderID, (GLint)m_size, m_type, GL_FALSE, 0, 0);
    HX3D_LOGGER(kGraphicsLowLevel).debug("AttributeBuffer %u enabled on %d and set.", m_id, m_shaderID);
  }

  void unbindAttribPointer() {
    assert(m_shaderID > -1);

    glDisableVertexAttribArray(m_shaderID);
    HX3D_LOGGER(kGraphicsLowLevel).debug("AttributeBuffer %u disabled on %d.", m_id, m_shaderID);
  }

private:
  GLenum m_type;
  size_t m_size;
  std::string m_shaderName;
  S32 m_shaderID;
};

typedef AttributeBuffer<VectorStorage<F32>, 1> AttributeBuffer1F;
typedef AttributeBuffer<VectorStorage<F32>, 2> AttributeBuffer2F;
typedef AttributeBuffer<VectorStorage<F32>, 3> AttributeBuffer3F;
typedef AttributeBuffer<VectorStorage<F32>, 4> AttributeBuffer4F;

}
}
