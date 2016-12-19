#include <Engine/Graphics/Elements/Cameras/Camera.hpp>
#include <Engine/Math/VectorUtils.hpp>
#include <Engine/Math/Constants.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace hx3d {
namespace Graphics {

Camera::Camera():
  m_position(0.f),
  m_direction(0.f, 0.f, -1.f),
  m_up(0.f, 1.f, 0.f),
  m_near(0.1f),
  m_far(1000.f),
  m_viewportWidth(1.f),
  m_viewportHeight(1.f)
{}

void Camera::setViewportSize(const F32 p_width, const F32 p_height) {
  m_viewportWidth = p_width;
  m_viewportHeight = p_height;
}

void Camera::setCameraDepth(const F32 p_near, const F32 p_far) {
  m_near = p_near;
  m_far = p_far;
}

void Camera::lookAt(const glm::vec3& p_target) {
  auto new_target = p_target - m_position;
  new_target = glm::normalize(new_target);

  if (new_target != glm::vec3(0)) {
    F32 dot = glm::dot(new_target, m_up);
    if (std::abs(dot - 1) < Math::kEpsilon) {
      m_up = m_direction;
      m_up *= -1;
    } else if (std::abs(dot + 1) < Math::kEpsilon) {
      m_up = m_direction;
    }

    m_direction = new_target;

    // normalize up
    glm::vec3 tmp(m_direction);
    tmp = glm::cross(tmp, m_up);
    tmp = glm::normalize(tmp);

    m_up = tmp;
    m_up = glm::cross(m_up, m_direction);
    m_up = glm::normalize(m_up);
  }
}

void Camera::translate(const glm::vec3& p_displ) {
  m_position += p_displ;
}

void Camera::rotate(const F32 p_angle, const glm::vec3& p_axis) {
  m_direction = Math::VectorUtils::rotate(m_direction, glm::radians(p_angle), p_axis);
  m_up = Math::VectorUtils::rotate(m_up, p_angle, p_axis);
}

const glm::mat4& Camera::getProjectionMatrix() const {
  return m_projection;
}

const glm::mat4& Camera::getViewMatrix() const {
  return m_view;
}

void Camera::rotateAroundTarget(const glm::vec3& p_target, const F32 p_angle, const glm::vec3& p_axis) {
  glm::vec3 tmp(p_target);
  tmp -= m_position;

  translate(tmp);
  rotate(p_angle, p_axis);

  tmp = Math::VectorUtils::rotate(tmp, glm::radians(p_angle), p_axis);
  translate(-tmp);
}

}
}
