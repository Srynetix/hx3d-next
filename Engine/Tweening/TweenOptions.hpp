#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Tweening/Interpolation.hpp>

namespace hx3d {
namespace Tweening {

enum LoopMode {
  kOneShot = 0,
  kLoop = 1
};

enum PlayMode {
  kForward = 0,
  kReverse = 1
};

struct TweenOptions {
  F32 duration;
  InterpolationType interpolation;
  LoopMode loopMode;
  PlayMode playMode;

  TweenOptions(const F32 p_duration = 10.f, const InterpolationType p_interpolation = kLinear, const LoopMode p_loopMode = kOneShot, const PlayMode p_playMode = kForward);

  inline PlayMode getInvertedPlayMode();
};

static TweenOptions DefaultOptions;

}
}
