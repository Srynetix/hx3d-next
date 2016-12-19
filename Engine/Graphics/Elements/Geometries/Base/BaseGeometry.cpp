#include <Engine/Graphics/Elements/Geometries/Base/BaseGeometry.hpp>
#include <Engine/Graphics/Elements/Buffers/Buffer.hpp>

namespace hx3d {
namespace Graphics {

BaseGeometry::~BaseGeometry() {}

void BaseGeometry::initialize() {
  m_vertexArray.generateID();
  initializeBuffers();
}

void BaseGeometry::uploadToGPU() {
  uploadBuffersToGPU();
}

void BaseGeometry::linkToShader(const Shader& p_shader) {
  m_vertexArray.bindToContext();
  linkBuffersToShader(p_shader);
  VertexArray::disableVertexArrays();
}

void BaseGeometry::render() {
  m_vertexArray.bindToContext();
  renderBuffers();
}

void BaseGeometry::setFaceCulling(const CullingType p_culling) {
  m_cullingType = p_culling;
}

bool BaseGeometry::containsBuffer(const std::string& p_name) {
  return m_buffers.find(p_name) != m_buffers.end();
}

Buffer& BaseGeometry::getBuffer(const std::string& p_shaderName) {
  return *m_buffers[p_shaderName];
}

}
}
