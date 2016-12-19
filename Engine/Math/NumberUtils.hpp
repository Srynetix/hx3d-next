#pragma once

#include <Engine/Math/Constants.hpp>

namespace hx3d {
namespace Math {
namespace NumberUtils {

template <class T>
inline bool epsEqual(const T p_lhs, const T p_rhs) {
  return std::abs(v1 - v2) <= kEpsilon;
}

}
}
}
