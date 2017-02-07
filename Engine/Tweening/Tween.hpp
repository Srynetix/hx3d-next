#pragma once

#include <Engine/Tweening/AbstractTween.hpp>
#include <Engine/Tweening/Interpolation.hpp>

namespace hx3d {
namespace Tweening {

template <class SubjectT, class ValueT, U32 ActionID>
void TweenExecution(SubjectT* p_subject, const ValueT& p_interpValue, const F32 p_t);

template <class SubjectT, class ValueT, U32 ActionID>
ValueT TweenInterpolate(const ValueT& p_baseValue, const ValueT& p_destValue, const F32& p_delta, const InterpolationType p_interpolation);

template <class SubjectT, class ValueT, U32 ActionID>
ValueT TweenStart(SubjectT* p_subject);

template <class SubjectT, class ValueT, U32 ActionID>
class Tween: public AbstractTween {
public:
  using SubjectType = SubjectT;
  using ValueType = ValueT;

  Tween(Tween&& p_tween):
    AbstractTween(p_tween),
    m_subject(p_tween.m_subject),
    m_baseValue(p_tween.m_baseValue),
    m_destValue(p_tween.m_destValue)
  {}

  Tween(SubjectT* p_subject, const ValueT& p_value, const TweenOptions p_options = DefaultOptions):
    AbstractTween(p_options),
    m_subject(p_subject), m_destValue(p_value),
    m_baseValue(ValueT())
  {}

  void initialize() {
    m_baseValue = TweenStart<SubjectT, ValueT, ActionID>(m_subject);
    m_initialized = true;
  }

  virtual void stop() override {
  }

  virtual void reset() override {
    m_currentTime = 0.f;
    m_ended = false;

    TweenExecution<SubjectT, ValueT, ActionID>(m_subject, TweenInterpolate<SubjectT, ValueT, ActionID>(m_baseValue, m_destValue, 0, m_options.interpolation), 0);
  }

  virtual void update(const F32 p_delta) override {
    if (!m_initialized) this->initialize();

    if (m_currentTime < m_options.duration) {
      m_currentTime += p_delta;

      // Apply
      auto t = m_currentTime / m_options.duration;
      TweenExecution<SubjectT, ValueT, ActionID>(m_subject, TweenInterpolate<SubjectT, ValueT, ActionID>(m_baseValue, m_destValue, t, m_options.interpolation), t);

    } else {
      m_ended = true;
    }
  }

private:
  SubjectT* m_subject;
  ValueT m_baseValue;
  ValueT m_destValue;
};

template <class SubjectT, class ValueT, U32 ActionID>
ValueT TweenInterpolate(const ValueT& p_baseValue, const ValueT& p_destValue, const F32& p_delta, const InterpolationType p_interpolation) {
  return Interpolate(p_baseValue, p_destValue, p_delta, p_interpolation);
}

}
}
