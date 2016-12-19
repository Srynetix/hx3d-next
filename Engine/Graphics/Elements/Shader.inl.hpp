#include <Engine/Graphics/Elements/Color.hpp>

namespace hx3d {
namespace Graphics {

template <>
inline void Shader::sendUniform(const std::string& p_uniform, const F32&& p_value) {
  glUniform1f(glGetUniformLocation(m_programID, p_uniform.c_str()), p_value);
}

template <>
inline void Shader::sendUniform(const std::string& p_uniform, const glm::mat4& p_value) {
  glUniformMatrix4fv(glGetUniformLocation(m_programID, p_uniform.c_str()), 1, GL_FALSE, glm::value_ptr(p_value));
}

template <>
inline void Shader::sendUniform(const std::string& p_uniform, const glm::mat4&& p_value) {
  glUniformMatrix4fv(glGetUniformLocation(m_programID, p_uniform.c_str()), 1, GL_FALSE, glm::value_ptr(p_value));
}

template <>
inline void Shader::sendUniform(const std::string& p_uniform, const glm::vec4& p_value) {
  glUniform4f(glGetUniformLocation(m_programID, p_uniform.c_str()), p_value.x, p_value.y, p_value.z, p_value.w);
}

template <>
inline void Shader::sendUniform(const std::string& p_uniform, const glm::vec4&& p_value) {
  glUniform4f(glGetUniformLocation(m_programID, p_uniform.c_str()), p_value.x, p_value.y, p_value.z, p_value.w);
}

template <>
inline void Shader::sendUniform(const std::string& p_uniform, const Color& p_value) {
  const auto& val = p_value.getFloatValues();
  glUniform4f(glGetUniformLocation(m_programID, p_uniform.c_str()), val.x, val.y, val.z, val.w);
}

template <>
inline void Shader::sendUniform(const std::string& p_uniform, const Color&& p_value) {
  const auto& val = p_value.getFloatValues();
  glUniform4f(glGetUniformLocation(m_programID, p_uniform.c_str()), val.x, val.y, val.z, val.w);
}

}
}
