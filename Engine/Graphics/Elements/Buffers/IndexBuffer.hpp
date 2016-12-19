#pragma once

#include <Engine/Graphics/Elements/Buffers/Buffer.hpp>
#include <Engine/Core/Types.hpp>

namespace hx3d {
namespace Graphics {

template <class BufferStorage>
class IndexBuffer: public BufferImpl<BufferStorage> {
public:
  typedef typename BufferStorage::ValueType ValueType;

  IndexBuffer(): BufferImpl(kElement),
    m_type(GetOpenGLType<BufferStorage::ValueType>())
    {}

protected:
  GLenum m_type;
};

typedef IndexBuffer<VectorStorage<U16>> IndexBuffer16;
typedef IndexBuffer<VectorStorage<U32>> IndexBuffer32;

}
}
