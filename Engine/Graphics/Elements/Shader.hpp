#pragma once

#include <Engine/Graphics/GLHeaders.hpp>
#include <Engine/Core/Types.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace hx3d {
namespace Graphics {

class Shader {
public:
  Shader();

  void loadShader(const std::string& p_vertexShaderCode, const std::string& p_fragmentShaderCode);
  void loadFromFile(const std::string& p_pathToShaders);

  GLint getAttributeLocation(const std::string p_attribute) const;

  template <class Type>
  void sendUniform(const std::string& p_uniform, const Type& p_value);
  template <class Type>
  void sendUniform(const std::string& p_uniform, const Type&& p_value);

  void useProgram();

private:
  std::string m_vertexShaderCode;
  std::string m_fragmentShaderCode;

  U32 m_vertexID;
  U32 m_fragmentID;
  U32 m_programID;

  void compileSubShader(U32& p_shaderId, const GLenum p_type, const std::string& content);
  void compileProgram();

  static void disablePrograms();

  static U32 m_currentProgramID;
};

}
}

#include <Engine/Graphics/Elements/Shader.inl.hpp>
