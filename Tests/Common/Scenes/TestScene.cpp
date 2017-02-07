#include <Tests/Common/Scenes/TestScene.hpp>
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

#include <Engine/Fonts/FontPack.hpp>

TestScene::TestScene() {}

void TestScene::onCreate() {
  const auto& logger = HX3D_LOGGER(kTests);

  // Caches
  auto& textureCache = Root::Instance().getTextureCache();
  auto& fontCache = Root::Instance().getFontCache();
  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& shaderCache = Root::Instance().getShaderCache();

  // Init sprite
  auto& texture = textureCache.get("clouds");

  m_sprite.setTexture(textureCache.getShared("clouds"));

  // Load font
  auto& font = fontCache.get("notoemoji-regular");
  auto& fontSt = fontCache.get("notosans-regular");
  font.updateSize(24, 300, 300);
  fontSt.updateSize(24, 300, 300);

  U32 width = Root::Instance().getGlobals().get<U16>("win.width");
  U32 height = Root::Instance().getGlobals().get<U16>("win.height");
  m_camera.setCameraDepth(-10.f, 10.f);
  m_camera.setOrthographicSize((F32)width, (F32)height);

  auto& shader = shaderCache.get("base");
  shader.sendUniform("u_projection", m_camera.getProjectionMatrix());
  shader.sendUniform("u_view", m_camera.getViewMatrix());

  for (size_t i = 0; i < 100; ++i) {
    m_rectangles.emplace_back(Utils::MakeSharedPtr<ColorRectangle>());
  }

  m_chrono.setTimeout(10);

  //////////////

  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().setClearColor(Graphics::Color::Pink);

  m_sprite.setAnchor(Math::Transform::kSouth);
}

void TestScene::onUpdate(const F32 p_delta) {
  m_chrono.tick(p_delta);
  if (m_chrono.isTimeout()) {
    m_chrono.reset();
  }

  for (auto& rect: m_rectangles) {
    F32 mult = Math::Random::randrange(10.f, 150.f);

    F32 depSpeed = std::abs(std::sin(m_chrono.getElapsedTime())) * mult + 20.f;
    F32 rotSpeed = std::abs(std::sin(m_chrono.getElapsedTime())) * 10.f + 5.f;

    rect->update(depSpeed, rotSpeed, p_delta);
  }

  m_sprite.setZRotation(std::sin(m_chrono.getElapsedTime()));
}

void TestScene::onRender() {
  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().clearWindow();

  auto& shader = Root::Instance().getShaderCache().get("base");
  shader.useProgram();

  shader.sendUniform("u_projection", m_camera.getProjectionMatrix());
  shader.sendUniform("u_view", m_camera.getViewMatrix());

  for (auto& rect: m_rectangles) rect->draw(shader);

  m_sprite.draw(shader);

  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& pack = fontPackCache.get("noto");

  U32 width = Root::Instance().getGlobals().get<U16>("win.width");
  U32 height = Root::Instance().getGlobals().get<U16>("win.height");
  F32 sx = 2.f / width;
  F32 sy = 2.f / height;
  F32 x = -1 + 8 * sx;
  F32 y = 1 - 100 * sy;

  m_fontRenderer.renderText(pack, "Coucou!💪🎅", x, y, sx, sy, Graphics::Color::GenerateRandomColor());
}
