#pragma once

#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>

#include <Engine/Core/Types.hpp>
#include <Engine/Utils/Uncopyable.hpp>

namespace hx3d {
namespace Graphics {

class Camera: private Utils::Uncopyable {
public:
  Camera();

  void setViewportSize(const F32 p_width, const F32 p_height);
  void setCameraDepth(const F32 p_near, const F32 p_far);

  void lookAt(const glm::vec3& p_target);
  void translate(const glm::vec3& p_displ);

  void rotate(const F32 p_angle, const glm::vec3& p_axis);
  void rotateAroundTarget(const glm::vec3& p_target, const F32 p_angle, const glm::vec3& p_axis);

  const glm::mat4& getProjectionMatrix() const;
  const glm::mat4& getViewMatrix() const;

  virtual void update() = 0;

protected:
  /// @brief Camera position
  glm::vec3 m_position;
  /// @brief Camera direction
  glm::vec3 m_direction;
  /// @brief Camera up vector
  glm::vec3 m_up;

  /// @brief Projection matrix
  glm::mat4 m_projection;
  /// @brief View matrix
  glm::mat4 m_view;

  /// @brief Near pane
  F32 m_near;
  /// @brief Far pane
  F32 m_far;

  /// @brief Viewport width
  F32 m_viewportWidth;
  /// @brief Viewport height
  F32 m_viewportHeight;
};

}
}
