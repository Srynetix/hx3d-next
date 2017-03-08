#include <SmashGame/Common/Scenes/StageScene.hpp>

#include <Engine/Debug/Logging.hpp>

#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Utils/Compression/ZipFile.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <Engine/Graphics/Elements/Buffers/AttributeBuffer.hpp>
#include <Engine/Graphics/Elements/Buffers/VertexArray.hpp>
#include <Engine/Graphics/Elements/Texture.hpp>

#include <Engine/Graphics/TextureCache.hpp>
#include <Engine/Graphics/OpenGLContext.hpp>

#include <Engine/Window/Window.hpp>
#include <Engine/Window/WindowModule.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Core/Globals.hpp>

#include <Engine/Math/Random.hpp>
#include <Engine/Fonts/FontPack.hpp>

StageScene::StageScene():
  m_world(b2Vec2(0.f, -9.f))
{
  m_world.SetDebugDraw(&m_debugDraw);
}

void StageScene::onCreate() {
  const auto& logger = HX3D_LOGGER(kTests);

  // Caches
  auto& textureCache = Root::Instance().getTextureCache();
  auto& fontCache = Root::Instance().getFontCache();
  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& shaderCache = Root::Instance().getShaderCache();

  auto width = Root::Instance().getGlobals().get<U16>("win.width");
  auto height = Root::Instance().getGlobals().get<U16>("win.height");
  m_camera.setCameraDepth(-10.f, 10.f);
  m_camera.setOrthographicSize((F32)width, (F32)height);

  m_fontRenderer.setProjectionMatrix(m_camera.getProjectionMatrix());
  m_fontRenderer.setViewMatrix(m_camera.getViewMatrix());

  auto& shader = shaderCache.get("base");
  shader.useProgram();
  shader.sendUniform("u_projection", m_camera.getProjectionMatrix());
  shader.sendUniform("u_view", m_camera.getViewMatrix());

  //////////////

  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().setClearColor(Graphics::Color::Black);
  window.getInput().registerHandler(&m_character);

  m_character.getTransform().setPosition(220.f, 100.f);
  m_platform.getTransform().setScale(width / 1.5f, 10);
  m_platform.getTransform().setPosition(width / 2.f, 10);

  m_platform.createBody(m_world);
  m_character.createBody(m_world);

  //////////////

  m_sceneGraph.getRoot().createChild<Game::TestSceneNode>();
}

void StageScene::onUpdate(const F32 p_delta) {
  m_platform.update(1.f/60.f);
  m_character.update(1.f/60.f);

  m_world.Step(1.f/60.f, 8, 3);
}

void StageScene::onRender() {
  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().clearWindow();

  auto& shaderCache = Root::Instance().getShaderCache();
  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& fontCache = Root::Instance().getFontCache();
  auto& pack = fontPackCache.get("noto");
  auto& font = fontCache.get("notosans-regular");

  auto& shader = shaderCache.get("base");
  shader.useProgram();

  U32 width = Root::Instance().getGlobals().get<U16>("win.width");
  U32 height = Root::Instance().getGlobals().get<U16>("win.height");
  F32 sx = 2.f / width;
  F32 sy = 2.f / height;

  // render
  ///////////

  m_character.draw(shader);
  m_platform.draw(shader);

  auto fps = window.getCurrentFPS();

  m_fontRenderer.renderText(pack,
    Text::Format("Hello.\nYou are on StageScene. Current FPS are {}.\nThis is a multiline sample text.💪🎅\n  Hello I am indented !\nCharacter velocity: X: {} Y: {}",
    fps, m_character.m_body->GetLinearVelocity().x, m_character.m_body->GetLinearVelocity().y),
    10, height - 30.f, 1, 1, Graphics::Color::Pink);
}
