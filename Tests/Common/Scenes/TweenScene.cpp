#include <Tests/Common/Scenes/TweenScene.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Core/Globals.hpp>

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

TweenScene::TweenScene() {}

void TweenScene::onCreate() {
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

  //////////////

  m_sprite.setPosition(width / 2.f, height / 2.f);
  m_sprite.setScale(200, 200);
  m_sprite.setColor(Graphics::Color::White);

  auto options = Tweening::TweenOptions(1.f, Tweening::kInOutSine);
  auto seqOpt = Tweening::TweenOptions();
  seqOpt.playMode = Tweening::kReverse;
  seqOpt.loopMode = Tweening::kLoop;

  auto sequence = m_tweenSystem.createSequence(seqOpt);
  auto multiOne = sequence->createMulti();
  multiOne->createTween<SPRITE_TWEEN_X, Graphics::Sprite>(&m_sprite, width / 4.f, options);
  multiOne->createTween<SPRITE_TWEEN_Y, Graphics::Sprite>(&m_sprite, height / 4.f, options);
  multiOne->createTween<SPRITE_TWEEN_ROT_Z, Graphics::Sprite>(&m_sprite, Math::kPi, options);

  auto multiTwo = sequence->createMulti();
  multiTwo->createTween<SPRITE_TWEEN_X, Graphics::Sprite>(&m_sprite, width / 2.f + width / 4.f, options);
  multiTwo->createTween<SPRITE_TWEEN_Y, Graphics::Sprite>(&m_sprite, height / 4.f, options);
  multiTwo->createTween<SPRITE_TWEEN_ROT_Z, Graphics::Sprite>(&m_sprite, Math::kPi * 2.f, options);

  auto multiThree = sequence->createMulti();
  multiThree->createTween<SPRITE_TWEEN_X, Graphics::Sprite>(&m_sprite, width / 2.f + width / 4.f, options);
  multiThree->createTween<SPRITE_TWEEN_Y, Graphics::Sprite>(&m_sprite, height / 2.f + height / 4.f, options);
  multiThree->createTween<SPRITE_TWEEN_ROT_Z, Graphics::Sprite>(&m_sprite, Math::kPi * 3.f, options);

  auto multiFour = sequence->createMulti();
  multiFour->createTween<SPRITE_TWEEN_X, Graphics::Sprite>(&m_sprite, width / 4.f, options);
  multiFour->createTween<SPRITE_TWEEN_Y, Graphics::Sprite>(&m_sprite, height / 2.f + height / 4.f, options);
}

void TweenScene::onUpdate(const F32 p_delta) {
  m_tweenSystem.update(p_delta);
}

void TweenScene::onRender() {
  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().clearWindow();

  auto& shader = Root::Instance().getShaderCache().get("base");
  shader.useProgram();

  m_sprite.draw(shader);

  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& pack = fontPackCache.get("noto");

  // U32 width = Root::Instance().getGlobals().get<U16>("win.width");
  // U32 height = Root::Instance().getGlobals().get<U16>("win.height");
  // F32 sx = 2.f / width;
  // F32 sy = 2.f / height;
  // F32 x = -1 + 8 * sx;
  // F32 y = 1 - 100 * sy;

  // m_fontRenderer.renderText(pack, "Coucou!💪🎅", x, y, sx, sy, Graphics::Color::Green);
}
