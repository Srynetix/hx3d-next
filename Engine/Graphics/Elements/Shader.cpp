#include <Engine/Graphics/Elements/Shader.hpp>
#include <Engine/Debug/Logging.hpp>
#include <Engine/Utils/IO/File.hpp>

namespace hx3d {
namespace Graphics {

Shader::Shader():
  m_vertexShaderCode(""),
  m_fragmentShaderCode(""),
  m_vertexID(0),
  m_fragmentID(0),
  m_programID(0)
  {}

void Shader::loadShader(const std::string& p_vertexShaderCode, const std::string& p_fragmentShaderCode) {
  const auto& logger = HX3D_LOGGER(kGraphics);
  m_vertexShaderCode = p_vertexShaderCode;
  m_fragmentShaderCode = p_fragmentShaderCode;

  compileSubShader(m_vertexID, GL_VERTEX_SHADER, m_vertexShaderCode);
  compileSubShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentShaderCode);
  compileProgram();
}

void Shader::loadShader(const std::string& p_pathToShaders) {
  const auto& logger = HX3D_LOGGER(kGraphics);

  std::string vertex_path = p_pathToShaders + ".vert.glsl";
  std::string fragment_path = p_pathToShaders + ".frag.glsl";

  logger.info("Loading shader `%s`...", p_pathToShaders);

  Utils::File vertex_file = Utils::File::loadTextFile(vertex_path);
  Utils::File fragment_file = Utils::File::loadTextFile(fragment_path);

  loadShader(vertex_file.getContent(), fragment_file.getContent());
}

void Shader::compileSubShader(U32& p_shaderId, GLenum p_type, const std::string& p_content) {
  const auto& logger = HX3D_LOGGER(kGraphics);

  p_shaderId = glCreateShader(p_type);
  const GLchar* code = p_content.c_str();

  glShaderSource(p_shaderId, 1, &code, 0);
  glCompileShader(p_shaderId);

  GLint error(0);
  glGetShaderiv(p_shaderId, GL_COMPILE_STATUS, &error);

  if (error != GL_TRUE) {
    GLint error_size(0);
    glGetShaderiv(p_shaderId, GL_INFO_LOG_LENGTH, &error_size);

    char* error_msg = new char[error_size + 1];
    glGetShaderInfoLog(p_shaderId, error_size, &error_size, error_msg);
    error_msg[error_size] = '\0';

    logger.error("Shader failed to load: %s", error_msg);

    delete[] error_msg;
    glDeleteShader(p_shaderId);
  }
}

void Shader::compileProgram() {
  const auto& logger = HX3D_LOGGER(kGraphics);

  m_programID = glCreateProgram();

  glAttachShader(m_programID, m_vertexID);
  glAttachShader(m_programID, m_fragmentID);
  glLinkProgram(m_programID);

  GLint error(0);
  glGetProgramiv(m_programID, GL_LINK_STATUS, &error);

  if (error != GL_TRUE) {
    GLint error_size(0);
    glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &error_size);

    char* error_msg = new char[error_size + 1];
    glGetShaderInfoLog(m_programID, error_size, &error_size, error_msg);
    error_msg[error_size] = '\0';

    logger.error("Shader program failed to load: %s", error_msg);

    delete[] error_msg;
    glDeleteProgram(m_programID);
  }
}

}
}
