#include <SmashGame/Common/Scenes/SplashScene.hpp>

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

Spinner::Options Spinner::DefaultOptions = Spinner::Options();

Spinner::Spinner(const Spinner::Options options): m_options(options), m_time(0.f), m_total(0.f), m_offset(1.f) {
  auto width = Root::Instance().getGlobals().get<U16>("win.width");
  auto height = Root::Instance().getGlobals().get<U16>("win.height");

  this->setScale(m_options.elementSize, m_options.elementSize);
  this->setPosition(width/2.f, height/2.f);

  for (U16 i = 0; i < options.count; ++i) {
    m_circles.emplace_back(Utils::MakeSharedPtr<Graphics::Circle>(options.precision));
  }
}

Spinner::~Spinner() {
}

void Spinner::update(const F32 p_delta) {
  m_total += p_delta;

  m_offset += p_delta * m_options.speed;
  if (m_offset > 2 * Math::kPi) {
    m_offset = m_offset - 2 * Math::kPi;
  }

  m_time += p_delta;
}

void Spinner::draw(Graphics::Shader& p_shader) {
  auto center = this->getPosition();
  auto radius = m_options.radius;
  auto count = m_options.count;
  auto step = (Math::kPi * 2.f) / count;

  for (U16 i = 0; i < count; ++i) {
    auto& circle = m_circles.at(i);

    // auto ang = i * step + m_time;
    auto ang = i * step + m_offset + std::sin(m_time / 5.f);
    auto x = center.x + (radius / 2) * cos(ang);
    auto y = center.y + (radius / 2) * sin(ang);
    this->setPosition(x, y);

    circle->setColor(Graphics::Color::RandomIncrement(circle->getColor()));

    p_shader.sendUniform("u_model", this->getModelMatrix());
    circle->draw(p_shader);
  }

  this->setPosition(center.x, center.y);
}

/////////////////
/////////////////
/////////////////

SplashScene::SplashScene(): m_spinner(Spinner::DefaultOptions) {}

void SplashScene::onCreate() {
  const auto& logger = HX3D_LOGGER(kTests);

  m_time = 0.f;

  // Caches
  auto& textureCache = Root::Instance().getTextureCache();
  auto& fontCache = Root::Instance().getFontCache();
  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& shaderCache = Root::Instance().getShaderCache();

  auto width = Root::Instance().getGlobals().get<U16>("win.width");
  auto height = Root::Instance().getGlobals().get<U16>("win.height");
  m_camera.setCameraDepth(-10.f, 10.f);
  m_camera.setOrthographicSize((F32)width, (F32)height);

  m_renderbuffer = Utils::MakeSharedPtr<Graphics::Renderbuffer>(width, height);
  m_renderbufferBoxes = Utils::MakeSharedPtr<Graphics::Renderbuffer>(width, height);

  auto& shader = shaderCache.get("base");
  shader.useProgram();
  shader.sendUniform("u_projection", m_camera.getProjectionMatrix());
  shader.sendUniform("u_view", m_camera.getViewMatrix());

  //////////////

  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().setClearColor(Graphics::Color::Black);

  //////////////

  m_rectangle.setColor(Graphics::Color::GenerateRandomColor());
  m_rectangleTransform.setPosition(0.f, 0.f);
  m_rectangleTransform.setScale(100, 100);

  m_rbSprite.setScale(width, height);
  m_rbSprite.setPosition(width / 2.f, height / 2.f);
  m_rbSprite.prepareForFramebuffer(true);

  m_rbBoxesSprite.setScale(width, height);
  m_rbBoxesSprite.setPosition(width / 2.f, height / 2.f);
  m_rbBoxesSprite.prepareForFramebuffer(true);

  m_boxSprite.setTexture(textureCache.getShared("clouds"));
  m_boxSprite.setScale(100, 100);
  m_boxSprite.setPosition(width / 2.f, height / 2.f);
}

void SplashScene::onUpdate(const F32 p_delta) {
  m_spinner.update(p_delta);
  m_time += p_delta;
}

void SplashScene::drawSpinner() {
  auto& shaderCache = Root::Instance().getShaderCache();
  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  auto& shader = shaderCache.get("base");

  // Bind FB
  m_renderbuffer->bindToContext();
  // Clear FB
  window.getContext().clearWindow();

  m_spinner.draw(shader);

  // Unbind FB
  Graphics::Renderbuffer::useDefaultBuffer();

  m_rbSprite.setTexture(m_renderbuffer->toTexture());
  if (m_time < 255) {
    U8 alpha = 255 - (U8)std::floor(m_time);
    m_rbSprite.setColor(Graphics::Color(255, 255, 255, alpha));
  }
  m_rbSprite.draw(shader);
}

void SplashScene::drawBoxes() {
  auto& shaderCache = Root::Instance().getShaderCache();
  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  auto& shader = shaderCache.get("base");

  // Bind FB
  m_renderbufferBoxes->bindToContext();
  // Clear FB
  window.getContext().clearWindow();

  m_boxSprite.draw(shader);

  // Unbind FB
  Graphics::Renderbuffer::useDefaultBuffer();

  m_rbBoxesSprite.setTexture(m_renderbufferBoxes->toTexture());
  m_rbBoxesSprite.draw(shader);
}

void SplashScene::onRender() {
  auto& window = Root::Instance().getModule<Window::WindowModule>().getWindow();
  window.getContext().clearWindow();

  auto& shaderCache = Root::Instance().getShaderCache();
  auto& fontPackCache = Root::Instance().getFontPackCache();
  auto& pack = fontPackCache.get("noto");

  auto& shader = shaderCache.get("base");
  shader.useProgram();

  drawBoxes();
  drawSpinner();

  U32 width = Root::Instance().getGlobals().get<U16>("win.width");
  U32 height = Root::Instance().getGlobals().get<U16>("win.height");
  F32 sx = 2.f / width;
  F32 sy = 2.f / height;
  F32 x = -1 + (100) * sx;
  F32 y = 1 - (100) * sy;

  // render
  ///////////

  // m_fontRenderer.renderText(pack, Text::Format("Time: {}", m_time), x, y, sx, sy, Graphics::Color::Pink);
}
