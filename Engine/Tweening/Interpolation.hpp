#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Math/Constants.hpp>

namespace hx3d {
namespace Tweening {

enum InterpolationType {
  kLinear = 0,

  kInQuad,
  kOutQuad,
  kInOutQuad,

  kInCubic,
  kOutCubic,
  kInOutCubic,

  kInQuart,
  kOutQuart,
  kInOutQuart,

  kInQuint,
  kOutQuint,
  kInOutQuint,

  kInSine,
  kOutSine,
  kInOutSine,

  kInExpo,
  kOutExpo,
  kInOutExpo,

  kInCirc,
  kOutCirc,
  kInOutCirc,

  kInBack,
  kOutBack,
  kInOutBack,

  kInBounce,
  kOutBounce,
  kInOutBounce,

  kInElastic,
  kOutElastic,
  kInOutElastic
};


/**
@brief Interpolate between two values.

@param p_a    Starting value
@param p_b    End value
@param p_t    Current time (between 0 and 1)
@param p_type Interpolation function

@return Computed value
*/
template <class T>
T Interpolate(const T p_a, const T p_b, const F32 p_t, const InterpolationType p_type);

}
}

#include <Engine/Tweening/Interpolation.inl.hpp>
