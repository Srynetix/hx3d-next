#pragma once

#include <Engine/Graphics/Elements/Shader.hpp>
#include <Engine/Graphics/GLHeaders.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Core/Types.hpp>

#include <cassert>
#include <vector>

#define HX3D_BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace hx3d {
namespace Graphics {

template <class Type>
GLenum GetOpenGLType();

class Shader;
class Buffer {
public:
  enum GPUStorage {
    kStatic = GL_STATIC_DRAW,
    kDynamic = GL_DYNAMIC_DRAW,
    kStream = GL_STREAM_DRAW
  };

  enum BufferType {
    kArray = GL_ARRAY_BUFFER,
    kElement = GL_ELEMENT_ARRAY_BUFFER
  };

  Buffer();
  Buffer(const BufferType p_type);
  virtual ~Buffer();

  void generateID();
  void setBufferType(const BufferType p_type);
  void bindBuffer(bool force = false);
  void bindBufferWithForce();

  GLuint getID() const;

  virtual void uploadToGPU(const GPUStorage p_storage = kStatic) = 0;

  static void disableBuffers(const BufferType p_type);

protected:
  GLuint m_id;
  BufferType m_bufferType;

  static GLuint m_currentArrayBufferID;
  static GLuint m_currentElementBufferID;
};

template <class Type>
class VectorStorage {
public:
  typedef Type ValueType;
  typedef U32 IndexType;
  typedef std::vector<Type> StorageType;

  template <class... Args>
  void add(const Type p_value, Args&&... p_args) {
    add(p_value);
    add(p_args...);
  }

  void add(const Type p_value) {
    m_storage.push_back(p_value);
  }

  void addPacked(const StorageType& p_values) {
    for (auto& value: p_values) {
      m_storage.push_back(value);
    }
  }

  void set(const IndexType p_index, const Type p_value) {
    assert(p_index < m_storage.size());
    m_storage[p_index] = p_value;
  }

  void replace(const StorageType& p_values) {
    m_storage = p_values;
  }

  void clear() {
    m_storage.clear();
  }

  Type get(const IndexType p_index) const {
    assert(p_index < m_storage.size());
    return m_storage[p_index];
  }

  const Type* getStream() const {
    return m_storage.data();
  }

  IndexType getSize() const {
    return (IndexType)m_storage.size();
  }

protected:
  StorageType m_storage;
};

template <class BufferStorage>
class BufferImpl: public Buffer, public BufferStorage {
public:
  typedef typename BufferStorage::ValueType ValueType;
  typedef typename BufferStorage::IndexType IndexType;
  typedef typename BufferStorage::StorageType StorageType;

  BufferImpl(): BufferImpl(kArray) {}
  BufferImpl(const BufferType p_bufferType): Buffer(p_bufferType) {}

  virtual void uploadToGPU(const GPUStorage p_storage) override {
    bindBuffer();
    glBufferData(m_bufferType, sizeof(ValueType) * getSize(), getStream(), p_storage);

    HX3D_LOGGER(kGraphicsLowLevel).debug("Buffer %u uploaded. Size: %lu", m_id, sizeof(ValueType) * getSize());
  }
};

}
}

#include <Engine/Graphics/Elements/Buffers/Buffer.inl.hpp>
