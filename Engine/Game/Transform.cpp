#include <Engine/Game/Transform.hpp>

#include <glm/gtx/transform.hpp>

namespace hx3d {
namespace Game {

Transform::Transform():
  m_position(0.f),
  m_scale(1.f),
  m_anchor(0.5f),
  m_matrix(1.f),
  m_dirty(true)
  {}

void Transform::setAnchor(const F32 p_x, const F32 p_y, const F32 p_z) {
  m_anchor.x = p_x;
  m_anchor.y = p_y;
  m_anchor.z = p_z;

  m_dirty = true;
}

void Transform::setAnchor(const Anchor p_anchor) {
  switch (p_anchor) {
    case kSouth:
      setAnchor(0.5f, 0.f);
      break;
    case kEast:
      setAnchor(1.f, 0.5f);
      break;
    case kNorth:
      setAnchor(0.5f, 1.f);
      break;
    case kWest:
      setAnchor(0.f, 0.5f);
      break;
    case kSE:
      setAnchor(1.f, 0.f);
      break;
    case kSW:
      setAnchor(0.f, 0.f);
      break;
    case kNE:
      setAnchor(1.f, 1.f);
      break;
    case kNW:
      setAnchor(0.f, 1.f);
      break;
    case kCenter:
      setAnchor(0.5f, 0.5f);
      break;
  }
}

void Transform::setPosition(const F32 p_x, const F32 p_y, const F32 p_z) {
  m_position.x = p_x;
  m_position.y = p_y;
  m_position.z = p_z;

  m_dirty = true;
}

void Transform::setZRotation(const F32 p_val) {
  m_rotation.z = p_val;

  m_dirty = true;
}

void Transform::setScale(const F32 p_w, const F32 p_h, const F32 p_d) {
  m_scale.x = p_w;
  m_scale.y = p_h;
  m_scale.z = p_d;

  m_dirty = true;
}

const glm::vec3& Transform::getPosition() const {
  return m_position;
}

const F32 Transform::getZRotation() const {
  return m_rotation.z;
}

void Transform::rotateZ(const F32 p_val) {
  m_rotation.z += p_val;

  m_dirty = true;
}

void Transform::move(const F32 p_x, const F32 p_y, const F32 p_z) {
  m_position.x += p_x;
  m_position.y += p_x;
  m_position.z += p_x;

  m_dirty = true;
}

void Transform::move(const glm::vec2& p_vec) {
  m_position.x += p_vec.x;
  m_position.y += p_vec.y;

  m_dirty = true;
}

void Transform::scale(const F32 p_w, const F32 p_h, const F32 p_d) {
  m_scale.x += p_w;
  m_scale.y += p_h;
  m_scale.z += p_d;

  m_dirty = true;
}

const glm::mat4& Transform::getModelMatrix() {
  if (m_dirty) {
    computeModelMatrix();
    m_dirty = false;
  }

  return m_matrix;
}

void Transform::computeModelMatrix() {

  // Anchor offset
  glm::vec3 normAnchor = m_anchor - glm::vec3(0.5);
  glm::vec3 disp = normAnchor * m_scale;

  m_matrix = glm::scale(
    glm::translate(
      glm::rotate(
        glm::translate(
          glm::mat4(1.f), m_position + disp
        ),
        m_rotation.z,
        glm::vec3(0, 0, 1)
      ),
      disp
    ),
    m_scale
  );
}

}
}
