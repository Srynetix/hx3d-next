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

#include <Engine/Game/SceneGraph.hpp>

#include <Engine/Input/InputHandler.hpp>

#include <Box2D/Box2D.h>

#include <SmashGame/Common/Scenes/DebugDraw.hpp>

#define PHYS_COEF 100.f

using namespace hx3d;

// [0.1 -> 10]

class GameObject {
public:
  GameObject(): m_body(nullptr) {}

  virtual void createBody(b2World& p_world) {}
  virtual void draw(Graphics::Shader& p_shader) {}
  virtual void update(const F32 p_delta) {
    if (m_body) {
      m_transform.setPosition(m_body->GetPosition().x * PHYS_COEF, m_body->GetPosition().y * PHYS_COEF);
    }
  }

  Math::Transform& getTransform() { return m_transform; }

  b2Body* m_body;
  Math::Transform m_transform;
};

class Platform: public GameObject {
public:
  Platform() {
    m_shape.setColor(Graphics::Color::Red);
    m_transform.setPosition(50, 50);
    m_transform.setScale(300, 30);
  }

  virtual void createBody(b2World& p_world) override {
    // Physics
    b2BodyDef def;
    def.position.Set(m_transform.getPosition().x / PHYS_COEF, m_transform.getPosition().y / PHYS_COEF);

    b2PolygonShape shape;
    shape.SetAsBox((m_transform.getScale().x / 2) / PHYS_COEF, (m_transform.getScale().y / 2) / PHYS_COEF);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = 1.f;

    m_body = p_world.CreateBody(&def);
    m_body->CreateFixture(&fixture);
  }

  Graphics::Rectangle& getShape() {
    return m_shape;
  }

  virtual void draw(Graphics::Shader& p_shader) override {
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
    m_transform.setPosition(100, 100);
    m_transform.setScale(50, 75);
  }

  virtual void createBody(b2World& p_world) override {
    // Physics
    b2BodyDef def;
    def.fixedRotation = true;
    def.type = b2_dynamicBody;
    def.position.Set(m_transform.getPosition().x / PHYS_COEF, m_transform.getPosition().y / PHYS_COEF);

    b2PolygonShape shape;
    shape.SetAsBox((m_transform.getScale().x / 2) / PHYS_COEF, (m_transform.getScale().y / 2) / PHYS_COEF);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = 0.5f;

    m_body = p_world.CreateBody(&def);
    m_body->CreateFixture(&fixture);
  }

  virtual void update(const F32 p_delta) override {
    GameObject::update(p_delta);

    auto oldVel = m_body->GetLinearVelocity();
    auto step = 15.f;
    auto jump = 8;
    auto maxVelocity = glm::vec2(5.f, 5.f);

    if (this->isKeyPressed(Input::Event::kKeyArrowLeft)) {
      m_body->SetLinearVelocity(b2Vec2(oldVel.x - step * p_delta, oldVel.y));
    }

    if (this->isKeyPressed(Input::Event::kKeyArrowRight)) {
      m_body->SetLinearVelocity(b2Vec2(oldVel.x + step * p_delta, oldVel.y));
    }

    // clamp

    auto vel = m_body->GetLinearVelocity();
    if (glm::sign(vel.x) > 0)
      vel.x = min(vel.x, maxVelocity.x);
    else if (glm::sign(vel.x) < 0)
      vel.x = max(vel.x, -maxVelocity.x);

    if (glm::sign(vel.y) > 0)
      vel.y = min(vel.y, maxVelocity.y);
    else if (glm::sign(vel.y) < 0)
      vel.y = max(vel.y, -maxVelocity.y);

    m_body->SetLinearVelocity(vel);
  }

  virtual void onKeyPress(const Input::Event& p_event) override {
    auto oldVel = m_body->GetLinearVelocity();
    auto jump = 6;

    if (p_event.key == Input::Event::kKeyArrowUp) {
      m_body->SetLinearVelocity(b2Vec2(oldVel.x, oldVel.y + jump));
    }
  }

  virtual void draw(Graphics::Shader& p_shader) override {
    p_shader.sendUniform("u_model", m_transform.getModelMatrix());
    m_bodyShape.draw(p_shader);
  }

private:
  Graphics::Rectangle m_bodyShape;
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
  Game::SceneGraph m_sceneGraph;

  Character m_character;
  Platform m_platform;
  b2World m_world;
  DebugDraw m_debugDraw;
};
