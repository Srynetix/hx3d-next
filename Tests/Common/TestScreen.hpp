#pragma once

#include <Engine/Window/Screen.hpp>
#include <Engine/Graphics/Elements/Shader.hpp>
#include <Engine/Graphics/Elements/Texture.hpp>
#include <Engine/Graphics/Elements/Cameras/Camera2D.hpp>
#include <Engine/Graphics/Elements/Geometries/PCTQuadGeometry.hpp>
#include <Engine/Graphics/Elements/Shapes/Rectangle.hpp>

#include <Engine/Fonts/FontRenderer.hpp>

#include <Engine/Game/Transform.hpp>

#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/IO/FileHandler.hpp>
#include <Engine/Utils/Time/Chronometer.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Core/Globals.hpp>

#include <Engine/Math/Random.hpp>
#include <Engine/Math/VectorUtils.hpp>

using namespace hx3d;

struct ColorRectangle {
  Graphics::Rectangle m_rectangle;
  Game::Transform m_transform;
  glm::vec2 m_dir;

  ColorRectangle() {
    using Math::Random::randrange;

    const U16 w = Root::Instance().getGlobals().get<U16>("win.width");
    const U16 h = Root::Instance().getGlobals().get<U16>("win.height");
    const F32 size = randrange(10.f, 100.f);

    m_rectangle.setColor(Graphics::Color::GenerateRandomColor());
    m_transform.setPosition(randrange(0.f, (F32)w), randrange(0.f, (F32)h));
    m_transform.setScale(size, size);
    m_dir = glm::vec2(1.f, 1.f);
  }

  void update(const F32 p_depSpeed, const F32 p_rotSpeed, const F32 p_delta) {
    if (isHittingLRBounds()) {
      // changeColor();
      m_dir.x *= -1;
    }

    if (isHittingUDBounds()) {
      // changeColor();
      m_dir.y *= -1;
    }

    m_transform.rotateZ((p_delta / 3.f) * p_rotSpeed);
    m_transform.move(Math::VectorUtils::multiply(m_dir, p_delta * p_depSpeed));
  }

  void draw(Graphics::Shader& p_shader) {
    Graphics::Texture::Blank().bindToContext(true);
    p_shader.sendUniform("u_model", m_transform.getModelMatrix());
    m_rectangle.draw(p_shader);
  }

  bool isHittingUDBounds() const {
    const U16 h = Root::Instance().getGlobals().get<U16>("win.height");
    auto& pos = m_transform.getPosition();
    return (pos.y <= 0 || pos.y >= h);
  }

  bool isHittingLRBounds() const {
    const U16 w = Root::Instance().getGlobals().get<U16>("win.width");
    auto& pos = m_transform.getPosition();
    return (pos.x <= 0 || pos.x >= w);
  }

  void changeColor() {
    m_rectangle.setColor(Graphics::Color::GenerateRandomColor());
  }
};

class TestScreen: public Window::Screen {
public:
  TestScreen();

protected:
  virtual void onCreate() override;
  virtual void onUpdate(const F32 p_delta) override;
  virtual void onRender() override;

private:
  Graphics::Camera2D m_camera;
  Utils::Chronometer m_chrono;
  Fonts::FontRenderer m_fontRenderer;

  std::vector<std::shared_ptr<ColorRectangle>> m_rectangles;
  glm::vec2 m_dir;
};
