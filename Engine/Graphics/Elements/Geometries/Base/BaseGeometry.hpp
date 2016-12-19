#pragma once

#include <Engine/Graphics/Elements/Buffers/AttributeBuffer.hpp>
#include <Engine/Graphics/Elements/Buffers/VertexArray.hpp>

#include <Engine/Utils/Uncopyable.hpp>

#include <memory>

namespace hx3d {
namespace Graphics {

class BaseGeometry: public Utils::Uncopyable {
public:
  enum CullingType {
    kFront = GL_FRONT,
    kBack = GL_BACK,
    kDisabled = 0
  };

  virtual ~BaseGeometry();

  virtual void initialize();
  virtual void uploadToGPU();
  virtual void linkToShader(const Shader& p_shader);
  virtual void render();

  bool containsBuffer(const std::string& m_name);
  Buffer& getBuffer(const std::string& p_shaderName);

  template <class AttributeType>
  AttributeType& getAttributeStorage(const std::string& p_shaderName) {
    return *static_cast<AttributeType*>(m_buffers[p_shaderName].get());
  }

protected:
  template <class AttributeType>
  void createAttributeBuffer(const std::string& p_shaderName) {
    auto type = new AttributeType();
    type->setShaderName(p_shaderName);
    type->generateID();

    m_buffers[p_shaderName].reset(type);
  }

  virtual void initializeBuffers() = 0;
  virtual void uploadBuffersToGPU() = 0;
  virtual void linkBuffersToShader(const Shader& p_shader) = 0;
  virtual void renderBuffers() = 0;

  void setFaceCulling(const CullingType p_culling);

protected:
  VertexArray m_vertexArray;
  std::map<std::string, std::shared_ptr<Buffer>> m_buffers;
  CullingType m_cullingType;
};

}
}
