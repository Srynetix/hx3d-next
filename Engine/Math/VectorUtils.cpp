#include <Engine/Math/VectorUtils.hpp>
#include <Engine/Math/Constants.hpp>

#include <glm/gtx/rotate_vector.hpp>

namespace hx3d {
namespace Math {
namespace VectorUtils {

glm::vec2 multiply(const glm::vec2& p_vector, const F32 p_scalar) {
  return glm::vec2(p_vector.x * p_scalar, p_vector.y * p_scalar);
}

glm::vec3 multiply(const glm::vec3& p_vector, const F32 p_scalar) {
  return glm::vec3(p_vector.x * p_scalar, p_vector.y * p_scalar, p_vector.z * p_scalar);
}

glm::vec3 rotate(const glm::vec3& p_vector, const F32 p_angle, const glm::vec3& p_axis) {
  glm::vec3 ret(p_vector);

  if (p_axis.x != 0)
    ret = glm::rotateX(ret, p_angle);
  if (p_axis.y != 0)
    ret = glm::rotateY(ret, p_angle);
  if (p_axis.z != 0)
    ret = glm::rotateZ(ret, p_angle);

  return ret;
}

glm::vec2 cross(const F32 p_scalar, const glm::vec2& p_vector) {
  return glm::vec2(-p_scalar * p_vector.y, p_scalar * p_vector.x);
}

glm::vec2 cross(const glm::vec2& p_vector, const F32 p_scalar) {
  return glm::vec2(p_scalar * p_vector.y, -p_scalar * p_vector.x);
}

F32 cross(const glm::vec2& p_lhs, const glm::vec2& p_rhs) {
  return p_lhs.x * p_rhs.y - p_lhs.y * p_rhs.x;
}

glm::vec2 normalize(const glm::vec2& p_vector) {
  F32 length = glm::length(p_vector);
  if (length > kEpsilon) {
    F32 inv = 1.f / length;
    return {p_vector.x * inv, p_vector.y * inv};
  }

  return p_vector;
}

F32 squareLength(const glm::vec2& p_vector) {
  return p_vector.x * p_vector.x + p_vector.y * p_vector.y;
}

F32 angleBetweenVecs(const glm::vec2& p_lhs, const glm::vec2& p_rhs) {
  F32 angle = 0.f;
  F32 a = glm::dot(p_lhs, p_rhs);

  if (p_rhs.x < 0) {
    angle = -std::acos(a);
  } else {
    angle = std::acos(a);
  }

  return angle;
}

}
}
}
