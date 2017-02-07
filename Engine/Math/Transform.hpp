#pragma once

#include <Engine/Core/Types.hpp>

#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>

namespace hx3d {
namespace Math {

struct Bounds2D {
  glm::vec2 topLeft;
  glm::vec2 bottomRight;
};

class Transform {
public:
  Transform();

  enum Anchor {
    kSouth,
    kEast,
    kNorth,
    kWest,
    kSE,
    kNE,
    kSW,
    kNW,
    kCenter
  };

  Bounds2D getBounds2D() {
    return Bounds2D {
      glm::vec2(
        m_position.x - m_scale.x / 2,
        m_position.y + m_scale.y / 2
      ),

      glm::vec2(
        m_position.x + m_scale.x / 2,
        m_position.y - m_scale.y / 2
      )
    };
  }

  void setAnchor(const Anchor p_anchor);
  void setAnchor(const F32 p_x, const F32 p_y, const F32 p_z = 0.f);

  void setPosition(const F32 p_x, const F32 p_y, const F32 p_z = 0.f);
  void setScale(const F32 p_w, const F32 p_h, const F32 p_d = 1.f);

  void setZRotation(const F32 p_val);

  const F32 getZRotation() const;
  const glm::vec3& getPosition() const;
  const glm::vec3& getScale() const;

  void move(const F32 p_x, const F32 p_y = 0, const F32 p_z = 0);
  void move(const glm::vec2& p_vec);

  void scale(const F32 p_w, const F32 p_h = 0, const F32 p_d = 0);

  void rotateZ(const F32 p_val);

  const glm::mat4& getModelMatrix();

private:
  glm::vec3 m_anchor;
  glm::vec3 m_position;
  glm::vec3 m_rotation;
  glm::vec3 m_scale;
  glm::mat4 m_matrix;

  bool m_dirty;

  void computeModelMatrix();
};

}
}
