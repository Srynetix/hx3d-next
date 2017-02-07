#include <Engine/Tweening/TweenOptions.hpp>

namespace hx3d {
namespace Tweening {

TweenOptions::TweenOptions(const F32 p_duration, const InterpolationType p_interpolation, const LoopMode p_loopMode, const PlayMode p_playMode):
  duration(p_duration),
  interpolation(p_interpolation),
  loopMode(p_loopMode),
  playMode(p_playMode)
{}

PlayMode TweenOptions::getInvertedPlayMode() {
  return (playMode == kForward) ? kReverse : kForward;
}

}
}
