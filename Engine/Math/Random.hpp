#pragma once

#include <Engine/Core/Types.hpp>
#include <cstdlib>

namespace hx3d {
namespace Math {
namespace Random {

template <class T>
T randrange(const T p_min, const T p_max) {
  return rand() % (p_max - p_min + 1) + p_min;
}

template <>
inline F32 randrange(const F32 p_min, const F32 p_max) {
  F32 random = ((F32) rand()) / (F32) RAND_MAX;
  F32 diff = p_max - p_min;
  F32 r = random * diff;
  return p_min + r;
}

}
}
}
