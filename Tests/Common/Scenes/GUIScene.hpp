#pragma once

#include <Engine/Game/Scene.hpp>
#include <Engine/Graphics/Elements/Cameras/Camera2D.hpp>
#include <Engine/Fonts/FontRenderer.hpp>

#include <Engine/UI/Panel.hpp>

using namespace hx3d;

class GUIScene: public Game::Scene {
public:
  GUIScene();

protected:
  virtual void onCreate() override;
  virtual void onUpdate(const F32 p_delta) override;
  virtual void onRender() override;

private:
  Graphics::Camera2D m_camera;
  Fonts::FontRenderer m_fontRenderer;

  UI::Panel::UPtr m_panel;
};
