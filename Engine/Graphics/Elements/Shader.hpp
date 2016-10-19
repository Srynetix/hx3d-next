#pragma once

#include <Engine/Graphics/GLHeaders.hpp>
#include <Engine/Core/Types.hpp>
#include <string>

namespace hx3d {
namespace Graphics {

class Shader {
public:
  Shader();

  void loadShader(const std::string& p_vertexShaderCode, const std::string& p_fragmentShaderCode);
  void loadShader(const std::string& p_pathToShaders);

private:
  std::string m_vertexShaderCode;
  std::string m_fragmentShaderCode;

  U32 m_vertexID;
  U32 m_fragmentID;
  U32 m_programID;

  void compileSubShader(U32& p_shaderId, GLenum p_type, const std::string& content);
  void compileProgram();
};

}
}
