#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <Engine/Core/Types.hpp>

namespace hx3d {
namespace Math {
namespace VectorUtils {

glm::vec2 multiply(const glm::vec2& p_vector, const F32 p_scalar);
glm::vec3 multiply(const glm::vec3& p_vector, const F32 p_scalar);

glm::vec3 rotate(const glm::vec3& p_vector, const F32 p_angle, const glm::vec3& p_axis);
glm::vec2 cross(const glm::vec2& p_vector, const F32 p_scalar);
glm::vec2 cross(const F32 p_scalar, const glm::vec2& p_vector);

float cross(glm::vec2 p_lhs, glm::vec2 p_rhs);
glm::vec2 normalize(const glm::vec2& p_vector);

float squareLength(const glm::vec2& p_vector);
float angleBetweenVecs(const glm::vec2& p_lhs, const glm::vec2& p_rhs);

} /* VectorUtils */
} /* Math */
} /* hx3d */
