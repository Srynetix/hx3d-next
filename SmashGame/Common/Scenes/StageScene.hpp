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

#include <Engine/Input/InputHandler.hpp>

#include <Box2D/Box2D.h>

using namespace hx3d;

class GameObject {
public:
  GameObject() {}

  virtual void draw(Graphics::Shader& p_shader) {}
  virtual void update(const F32 p_delta) {}

  Math::Transform& getTransform() { return m_transform; }

protected:
  Math::Transform m_transform;
};

class Platform: public GameObject {
public:
  Platform() {
    m_shape.setColor(Graphics::Color::Red);
    m_transform.setPosition(50, 50);
    m_transform.setScale(300, 30);
  }

  Graphics::Rectangle& getShape() {
    return m_shape;
  }

  virtual void draw(Graphics::Shader& p_shader) {
    p_shader.sendUniform("u_model", m_transform.getModelMatrix());
    m_shape.draw(p_shader);
  }

private:
  Graphics::Rectangle m_shape;
};

class Character: public GameObject, public Input::InputHandler {
public:
  Character() {
    m_bodyShape.setColor(Graphics::Color::LightGray);
    m_headShape.setColor(Graphics::Color::Red);
    m_transform.setPosition(100, 100);
    m_transform.setScale(10, 50);

    m_headShapeTransform.setPosition(100, 125);
    m_headShapeTransform.setScale(10, 10);
  }

  virtual void draw(Graphics::Shader& p_shader) override {
    p_shader.sendUniform("u_model", m_transform.getModelMatrix());
    m_bodyShape.draw(p_shader);

    p_shader.sendUniform("u_model", m_headShapeTransform.getModelMatrix());
    m_headShape.draw(p_shader);
  }

  virtual void update(const F32 p_delta) override {
  }

  virtual void onKeyPress(const Input::Event& p_event) override {
    if (p_event.key == Input::Event::kKeyArrowLeft) {
      // m_velocity.x -= 10 * 5;
    } else if (p_event.key == Input::Event::kKeyArrowRight) {
      // m_velocity.x += 10 * 5;
    } else if (p_event.key == Input::Event::kKeyArrowUp) {
      // m_velocity.y += 20 * 5;
    } else if (p_event.key == Input::Event::kKeyArrowDown) {
      // m_velocity.y -= 20 * 5;
    }
  }

private:
  Graphics::Rectangle m_bodyShape;
  Graphics::Circle m_headShape;
  Math::Transform m_headShapeTransform;
};

class StageScene: public Game::Scene {
public:
  StageScene();

protected:
  virtual void onCreate() override;
  virtual void onUpdate(const F32 p_delta) override;
  virtual void onRender() override;

private:
  Graphics::Camera2D m_camera;
  Fonts::FontRenderer m_fontRenderer;

  Character m_character;
  Platform m_platform;
  b2World m_world;
};
