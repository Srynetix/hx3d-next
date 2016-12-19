#include <Engine/Core/Root.hpp>

#include <Engine/Debug/Logging.hpp>
#include <Engine/Debug/StackTraceHandler.hpp>

#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Utils/Parsers/INIHandler.hpp>
#include <Engine/Core/Globals.hpp>

#include <Engine/Fonts/FontsModule.hpp>
#include <Engine/Window/WindowModule.hpp>

#include <chrono>

namespace hx3d {

struct EngineRoot::Impl {
  Utils::INIHandler m_engineConfigHandler;
  std::chrono::time_point<std::chrono::system_clock> m_startingTimePoint;
};

EngineRoot::EngineRoot():
  HX3D_PIMPL_INIT() {}

EngineRoot::~EngineRoot() {
  SFileLoader::Release();
}

void EngineRoot::Start() {
  const auto& core_logger = HX3D_LOGGER(kCore);

  SFileLoader::Initialize();
  STextureCache::Initialize();
  SShaderCache::Initialize();
  SFontCache::Initialize();
  SFontPackCache::Initialize();
  SGlobals::Initialize();

  // Loading config
  core_logger.info("Loading engine configuration...");
  m_impl->m_engineConfigHandler.parseFromFile("EngineConfig.ini");

  // Initializing random seed
  srand((U32)time(0));

  // Starting modules
  m_loader.loadModule<Window::WindowModule>();
  m_loader.loadModule<Fonts::FontsModule>();

  // Loading default assets
  auto& cache = this->getShaderCache();
  cache.loadFromFile("base", "Shaders/Base");
  cache.loadFromFile("font", "Shaders/Font");

  core_logger.info("Engine Root ready !");
}

void EngineRoot::AbortOnException(const std::exception& p_exc) {
  const auto& core_logger = HX3D_LOGGER(kCore);
  Debug::StackTraceHandler handler;

  core_logger.error(p_exc.what());
  handler.report();

  throw p_exc;
}

Utils::FileLoader& EngineRoot::getFileLoader() {
  return SFileLoader::Instance();
}

Graphics::TextureCache& EngineRoot::getTextureCache() {
  return STextureCache::Instance();
}

Graphics::ShaderCache& EngineRoot::getShaderCache() {
  return SShaderCache::Instance();
}

Fonts::FontCache& EngineRoot::getFontCache() {
  return SFontCache::Instance();
}

Fonts::FontPackCache& EngineRoot::getFontPackCache() {
  return SFontPackCache::Instance();
}

Core::Globals& EngineRoot::getGlobals() {
  return SGlobals::Instance();
}

Utils::INIHandler& EngineRoot::getEngineConfiguration() {
  return m_impl->m_engineConfigHandler;
}

}
