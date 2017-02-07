#pragma once

#include <Engine/Game/Scene.hpp>
#include <Engine/Graphics/Elements/Cameras/Camera2D.hpp>
#include <Engine/Graphics/Elements/Sprite.hpp>

#include <Engine/Fonts/FontRenderer.hpp>
#include <Engine/Tweening/TweenSystem.hpp>

#include <Engine/Debug/Logging.hpp>

using namespace hx3d;

constexpr U32 SPRITE_TWEEN_X = 1;
constexpr U32 SPRITE_TWEEN_Y = 2;
constexpr U32 SPRITE_TWEEN_ROT_Z = 3;

namespace hx3d {
namespace Tweening {

template <>
inline void TweenExecution<Graphics::Sprite, F32, SPRITE_TWEEN_X>(Graphics::Sprite* p_subject, const F32& p_interpValue, const F32 p_t) {
  p_subject->setPosition(p_interpValue, p_subject->getPosition().y);
}

template <>
inline void TweenExecution<Graphics::Sprite, F32, SPRITE_TWEEN_Y>(Graphics::Sprite* p_subject, const F32& p_interpValue, const F32 p_t) {
  p_subject->setPosition(p_subject->getPosition().x, p_interpValue);
}

template <>
inline void TweenExecution<Graphics::Sprite, F32, SPRITE_TWEEN_ROT_Z>(Graphics::Sprite* p_subject, const F32& p_interpValue, const F32 p_t) {
  p_subject->setZRotation(p_interpValue);
}

template <>
inline F32 TweenStart<Graphics::Sprite, F32, SPRITE_TWEEN_X>(Graphics::Sprite* p_subject) {
  return p_subject->getPosition().x;
}

template <>
inline F32 TweenStart<Graphics::Sprite, F32, SPRITE_TWEEN_Y>(Graphics::Sprite* p_subject) {
  return p_subject->getPosition().y;
}

template <>
inline F32 TweenStart<Graphics::Sprite, F32, SPRITE_TWEEN_ROT_Z>(Graphics::Sprite* p_subject) {
  return p_subject->getZRotation();
}

}
}

class TweenScene: public Game::Scene {
public:
  TweenScene();

protected:
  virtual void onCreate() override;
  virtual void onUpdate(const F32 p_delta) override;
  virtual void onRender() override;

private:
  Graphics::Camera2D m_camera;
  Fonts::FontRenderer m_fontRenderer;
  Tweening::TweenSystem m_tweenSystem;
  Graphics::Sprite m_sprite;
};
