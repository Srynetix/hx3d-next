#include <Engine/Tweening/TweenSystem.hpp>

namespace hx3d {
namespace Tweening {

TweenSystem::TweenSystem() {}

Utils::SharedPtr<Sequence> TweenSystem::createSequence(const TweenOptions p_options) {
  auto tween = Utils::MakeSharedPtr<Sequence>(p_options);
  m_tweenList.push_back(tween);
  return tween;
}

void TweenSystem::update(const F32 p_delta) {
  for (auto& tw: m_tweenList) {
    tw->update(p_delta);
  }
}

}
}
