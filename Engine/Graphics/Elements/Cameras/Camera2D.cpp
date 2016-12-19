#include <Engine/Graphics/Elements/Cameras/Camera2D.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace hx3d {
namespace Graphics {

Camera2D::Camera2D(): Camera(), m_zoom(1.f) {
  setOrthographicSize(1, 1);
}

void Camera2D::setOrthographicSize(const F32 p_width, const F32 p_height) {
  m_viewportWidth = p_width;
  m_viewportHeight = p_height;

  update();
}

void Camera2D::update() {
  m_position = glm::vec3(m_zoom * m_viewportWidth / 2.f, m_zoom * m_viewportHeight / 2.f, 0);
  m_projection = glm::ortho(m_zoom * (-m_viewportWidth / 2.f), m_zoom * (m_viewportWidth / 2.f), m_zoom * (-m_viewportHeight / 2.f), m_zoom * (m_viewportHeight / 2.f), m_near, m_far);
  m_view = glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera2D::setZoom(const F32 p_zoom) {
  m_zoom = p_zoom;

  update();
}

}
}
