#pragma once

#include <Engine/Tweening/MultiTween.hpp>

#include <queue>

namespace hx3d {
namespace Tweening {

class Sequence: public AbstractTween {
public:
  Sequence(const TweenOptions p_options = DefaultOptions);

  template <U32 I, class S, class V>
  void createTween(S* p_subject, const V& p_destValue, const TweenOptions p_options = DefaultOptions) {
    m_tweens.push_back(Utils::MakeSharedPtr<Tween<S, V, I>>(p_subject, p_destValue, p_options));
  }

  Utils::SharedPtr<MultiTween> createMulti(const TweenOptions p_options = DefaultOptions);
  void addTween(const Utils::SharedPtr<AbstractTween>& p_tween);

  virtual void stop() override;
  virtual void reset() override;
  virtual void update(const F32 p_delta) override;

private:
  std::deque<Utils::SharedPtr<AbstractTween>> m_tweens;
  std::deque<Utils::SharedPtr<AbstractTween>> m_doneTweens;
};

}
}
