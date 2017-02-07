#include <Engine/Tweening/Sequence.hpp>

namespace hx3d {
namespace Tweening {

Sequence::Sequence(const TweenOptions p_options):
  AbstractTween(p_options) {}

Utils::SharedPtr<MultiTween> Sequence::createMulti(const TweenOptions p_options) {
  auto tween = Utils::MakeSharedPtr<MultiTween>(p_options);
  m_tweens.push_back(tween);
  return tween;
}

void Sequence::addTween(const Utils::SharedPtr<AbstractTween>& p_tween) {
  m_tweens.push_back(p_tween);
}

void Sequence::stop() {
}

void Sequence::reset() {
  m_ended = false;

  while (!m_tweens.empty()) {
    auto& top = m_tweens.front();
    m_doneTweens.push_back(top);
    m_tweens.pop_front();
  }

  while (!m_doneTweens.empty()) {
    auto& tw = (m_options.playMode == kForward ? m_doneTweens.front() : m_doneTweens.back());
    tw->reset();

    m_tweens.push_back(tw);

    if (m_options.playMode == kReverse)
      m_doneTweens.pop_back();
    else
      m_doneTweens.pop_front();
  }
}

void Sequence::update(const F32 p_delta) {
  if (m_ended) return;

  if (!m_tweens.empty()) {
    auto& tw = (m_options.playMode == kForward ? m_tweens.front() : m_tweens.back());
    tw->update(p_delta);

    if (tw->isTimeout()) {
      m_doneTweens.push_back(tw);

      if (m_options.playMode == kForward)
        m_tweens.pop_front();
      else
        m_tweens.pop_back();

    }
  } else {
    m_ended = true;
    if (m_options.loopMode == kLoop)
      this->reset();
  }
}

}
}
