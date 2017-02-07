#include <Engine/Tweening/AbstractTween.hpp>

namespace hx3d {
namespace Tweening {

AbstractTween::AbstractTween(const TweenOptions p_options):
  m_ended(false), m_currentTime(0.f), m_options(p_options), m_initialized(false)
{}

AbstractTween::AbstractTween(AbstractTween&& p_tween):
  m_options(p_tween.m_options),
  m_initialized(p_tween.m_initialized),
  m_ended(p_tween.m_ended),
  m_currentTime(p_tween.m_currentTime)
{}

bool AbstractTween::isTimeout() const {
  return m_ended;
}

bool AbstractTween::isInitialized() const {
  return m_initialized;
}

}
}
