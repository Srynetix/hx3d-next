#include <Engine/Tweening/MultiTween.hpp>

namespace hx3d {
namespace Tweening {

MultiTween::MultiTween(const TweenOptions p_options):
  AbstractTween(p_options) {}

void MultiTween::addTween(const Utils::SharedPtr<AbstractTween>& p_tween) {
  m_tweens.push_back(p_tween);
}

void MultiTween::reset() {
  m_ended = false;
  for (auto& tw: m_tweens) {
    tw->reset();
  }
}

void MultiTween::stop() {

}

void MultiTween::update(const F32 p_delta) {
  if (m_ended)
    return;

  bool end = true;
  for (auto& tw: m_tweens) {
    tw->update(p_delta);
    if (!tw->isTimeout()) {
      end = false;
    }
  }

  if (end) {
    m_ended = true;
  }
}

}
}
