#pragma once

#include <Engine/Tweening/Sequence.hpp>

namespace hx3d {
namespace Tweening {

class TweenSystem {
public:
  TweenSystem();

  template <U32 I, class S, class V>
  Utils::SharedPtr<Tween<S, V, I>> createTween(S* p_subject, const V& p_destValue, const TweenOptions p_options = DefaultOptions) {
    auto tween = Utils::MakeSharedPtr<Tween<S, V, I>>(p_subject, p_destValue, p_options);
    m_tweenList.push_back(tween);
    return tween;
  }

  Utils::SharedPtr<Sequence> createSequence(const TweenOptions p_options = DefaultOptions);

  void update(const F32 p_delta);

private:
  std::vector<Utils::SharedPtr<AbstractTween>> m_tweenList;
};

}
}
