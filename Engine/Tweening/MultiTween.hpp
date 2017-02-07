#pragma once

#include <Engine/Tweening/Tween.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <vector>

namespace hx3d {
namespace Tweening {

class MultiTween: public AbstractTween {
public:
  MultiTween(const TweenOptions p_options = DefaultOptions);

  template <U32 I, class S, class V>
  void createTween(S* p_subject, const V& p_destValue, const TweenOptions p_options = DefaultOptions) {
    auto options = p_options;
    options.loopMode = m_options.loopMode;
    options.playMode = m_options.playMode;

    m_tweens.push_back(Utils::MakeSharedPtr<Tween<S, V, I>>(p_subject, p_destValue, options));
  }

  void addTween(const Utils::SharedPtr<AbstractTween>& p_tween);

  virtual void reset() override;
  virtual void stop() override;
  virtual void update(const F32 p_delta) override;

private:
  std::vector<Utils::SharedPtr<AbstractTween>> m_tweens;
};

}
}
