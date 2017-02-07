namespace hx3d {
namespace Tweening {

static F32 outBounce(F32 t) {
  return
    (t < 0.3636f) ? 7.5625f * t * t:
    (t < 0.7272f) ? 7.5625f * (t - 0.5454f) * (t - 0.5454f) + 0.75f:
    (t < 0.9090f) ? 7.5625f * (t - 0.8181f) * (t - 0.8181f) + 0.9375f:
    7.5625f * (t - 0.9545f) * (t - 0.9545f) + 0.984375f;
}

static F32 inExpo(F32 t) {
  return (F32)std::pow(2, 10 * (t-1));
}

static F32 inCirc(F32 t) {
  return -(std::sqrt(1 - t*t) - 1);
}

static F32 inBack(F32 t) {
  return t*t * (3*t - 2);
}

static F32 inElastic(F32 t) {
  return (t == 0 || t == 1) ? t :
    (F32)(-std::pow(2, 8 * (t-1))) * (F32)std::sin(((t-1) * 80 - 7.5) * Math::kPi / 15);
}

template <class T>
T Interpolate(const T p_a, const T p_b, const F32 p_t, const InterpolationType p_type) {
  auto t = p_t;

  switch (p_type) {
    case kInQuad:
      t = t * t;
      break;
    case kOutQuad:
      t = t * (2-t);
      break;
    case kInOutQuad:
      t = (t < 0.5f) ? 2 * t * t : -1 + (4-2*t)*t;
      break;

    case kInCubic:
      t = t * t * t;
      break;
    case kOutCubic:
      t = (t-1) * (t-1) * (t-1) + 1;
      break;
    case kInOutCubic:
      t = (t < 0.5f) ? 4*t*t*t : (t-1)*(2*t-2)*(2*t-2)+1;
      break;

    case kInQuart:
      t = t * t * t * t;
      break;
    case kOutQuart:
      t = 1 - (t-1) * (t-1) * (t-1) * (t-1);
      break;
    case kInOutQuart:
      t = (t < 0.5f) ? 8*t*t*t*t : 1 - 8*(t-1)*(t-1)*(t-1)*(t-1);
      break;

    case kInQuint:
      t = t*t*t*t*t*t;
      break;
    case kOutQuint:
      t = 1 + (t-1) * (t-1) * (t-1) * (t-1) * (t-1);
      break;
    case kInOutQuint:
      t = (t < 0.5f) ? 16*t*t*t*t*t : 1 + 16*(t-1)*(t-1)*(t-1)*(t-1)*(t-1);
      break;

    case kInSine:
      t = -1 * std::cos(t * (Math::kPi / 2)) + 1;
      break;
    case kOutSine:
      t = std::sin(t * (Math::kPi / 2));
      break;
    case kInOutSine:
      t = (std::cos(t * Math::kPi) - 1) / -2;
      break;

    case kInExpo:
      t = inExpo(t);
      break;
    case kOutExpo:
      t = 1 - inExpo(1 - t);
      break;
    case kInOutExpo:
      t = (t < 0.5f) ?
        inExpo(t * 2) / 2 :
        1 - inExpo(t * -2 + 2) / 2;
      break;

    case kInCirc:
      t = inCirc(t);
      break;
    case kOutCirc:
      t = 1 - inCirc(1 - t);
      break;
    case kInOutCirc:
      t = (t < 0.5f) ?
        inCirc(t * 2) / 2 :
        1 - inCirc(t * -2 + 2) / 2;
      break;

    case kInBack:
      t = inBack(t);
      break;
    case kOutBack:
      t = 1 - inBack(1 - t);
      break;
    case kInOutBack:
      t = (t < 0.5f) ?
        inBack(t * 2) / 2 :
        1 - inBack(t * -2 + 2) / 2;
      break;

    case kInBounce:
      t = 1 - outBounce(1 - t);
      break;
    case kOutBounce:
      t = outBounce(t);
      break;
    case kInOutBounce:
      t =
        (t < 0.5f) ?
        (1 - outBounce(1 - t*2)) * 0.5f:
        outBounce(t * 2 - 1) * 0.5f + 1 * 0.5f;
      break;

    case kInElastic:
      t = inElastic(t);
      break;
    case kOutElastic:
      t = 1 - inElastic(1 - t);
      break;
    case kInOutElastic:
      t = (t < 0.5f) ?
        inElastic(t * 2) / 2 :
        1 - inElastic(t * -2 + 2) / 2;
      break;

    case kLinear:
    default:
      break;
  }

  return (T)(p_a + t*(p_b - p_a));
}

}
}
