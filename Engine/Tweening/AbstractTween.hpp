#pragma once

#include <Engine/Tweening/TweenOptions.hpp>

#include <Engine/Utils/Uncopyable.hpp>

namespace hx3d {
namespace Tweening {

class AbstractTween: public Utils::Uncopyable {
public:
  AbstractTween(const TweenOptions p_options = DefaultOptions);
  AbstractTween(AbstractTween&& p_tween);

  bool isTimeout() const;
  bool isInitialized() const;

  virtual void reset() = 0;
  virtual void stop() = 0;
  virtual void update(const F32 p_delta) = 0;

protected:
  TweenOptions m_options;
  bool m_ended;
  bool m_initialized;
  F32 m_currentTime;
};

}
}
