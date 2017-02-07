#pragma once

#include <Engine/Game/Scene.hpp>
#include <Engine/Fonts/FontRenderer.hpp>
#include <Engine/Math/Transform.hpp>
#include <Engine/Graphics/Elements/Cameras/Camera2D.hpp>
#include <Engine/Graphics/Elements/Shapes/Rectangle.hpp>
#include <Engine/Graphics/Elements/Shapes/Circle.hpp>

#include <Engine/Graphics/Elements/Drawable.hpp>
#include <Engine/Graphics/Elements/Sprite.hpp>
#include <Engine/Graphics/Elements/Renderbuffer.hpp>

using namespace hx3d;

class Spinner: public Graphics::Drawable, public Math::Transform {
public:
  struct Options {
    U16 count = 16;
    F32 precision = Math::kPi / 12;
    F32 radius = 500.f;
    F32 elementSize = 40.f;
    F32 speed = 1.f;
  };

  static Options DefaultOptions;

  Spinner(const Options options = DefaultOptions);
  ~Spinner();

  void update(const F32 p_delta);
  virtual void draw(Graphics::Shader& p_shader) override;

private:
  Options m_options;
  F32 m_time;
  F32 m_total;
  F32 m_offset;
  std::vector<Utils::SharedPtr<Graphics::Circle>> m_circles;
};

class SplashScene: public Game::Scene {
public:
  SplashScene();

protected:
  virtual void onCreate() override;
  virtual void onUpdate(const F32 p_delta) override;
  virtual void onRender() override;

private:
  void drawSpinner();
  void drawBoxes();

  Graphics::Camera2D m_camera;
  Fonts::FontRenderer m_fontRenderer;

  Graphics::Rectangle m_rectangle;
  Math::Transform m_rectangleTransform;

  Utils::SharedPtr<Graphics::Renderbuffer> m_renderbuffer;
  Utils::SharedPtr<Graphics::Renderbuffer> m_renderbufferBoxes;
  Graphics::Sprite m_rbSprite;
  Graphics::Sprite m_rbBoxesSprite;
  Graphics::Sprite m_boxSprite;

  Spinner m_spinner;

  F32 m_time;
};
