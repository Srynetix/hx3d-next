#include <Tests/Common/Scenes/GUIScene.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Core/Globals.hpp>

#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Utils/Compression/ZipFile.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <Engine/Graphics/Elements/Texture.hpp>

#include <Engine/Graphics/TextureCache.hpp>
#include <Engine/Graphics/OpenGLContext.hpp>

#include <Engine/Window/Window.hpp>
#include <Engine/Window/WindowModule.hpp>

#include <Engine/Fonts/FontPack.hpp>

#include <Engine/UI/Layouts/BoxLayout.hpp>
#include <Engine/UI/Button.hpp>

GUIScene::GUIScene() {}

void GUIScene::onCreate() {
  const auto& logger = HX3D_LOGGER(kTests);

  // Caches
  auto& textureCache = Root::Instance().getTextureCache();
  auto& fontCache = Root::Instance().getFontCache();
  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& shaderCache = Root::Instance().getShaderCache();

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
  shader.useProgram();
  shader.sendUniform("u_projection", m_camera.getProjectionMatrix());
  shader.sendUniform("u_view", m_camera.getViewMatrix());

  //////////////

  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().setClearColor(Graphics::Color::Gray);

  m_panel = UI::Panel::Create();
  m_panel->setBackgroundColor(Graphics::Color::Pink);
  m_panel->setScale(600.f, 600.f);
  m_panel->setPosition(400.f, 300.f);

  m_panel->makeLayout<UI::Layouts::BoxLayout>(UI::Layouts::BoxLayout::kVertical);
  auto pnl = m_panel->makeWidget<UI::Panel>(Graphics::Color::Red);
  auto btn = m_panel->makeWidget<UI::Button>();

  pnl->setScalePolicy(UI::UITransform::kExpand);

  btn->setScalePolicy(UI::UITransform::kExpandWidth);
  btn->setScale(400, 50);

  m_panel->applyLayout();
}

void GUIScene::onUpdate(const F32 p_delta) {}

void GUIScene::onRender() {
  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().clearWindow();

  auto& shaderCache = Root::Instance().getShaderCache();
  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& pack = fontPackCache.get("noto");

  U32 width = Root::Instance().getGlobals().get<U16>("win.width");
  U32 height = Root::Instance().getGlobals().get<U16>("win.height");
  F32 sx = 2.f / width;
  F32 sy = 2.f / height;
  F32 x = -1 + 8 * sx;
  F32 y = 1 - 100 * sy;

  // m_fontRenderer.renderText(pack, "Message: 💪🎅", x, y, sx, sy, Graphics::Color::Pink);

  auto& baseShader = shaderCache.get("base");
  baseShader.useProgram();
  m_panel->draw(baseShader);
}
