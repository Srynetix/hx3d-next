#pragma once

#include <Engine/Utils/SingletonHolder.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <Engine/Graphics/ShaderCache.hpp>
#include <Engine/Graphics/TextureCache.hpp>
#include <Engine/Fonts/FontCache.hpp>
#include <Engine/Fonts/FontPackCache.hpp>

#include <Engine/Core/ModuleLoader.hpp>

namespace hx3d {

namespace Utils {
  class FileLoader;
  class INIHandler;
}

namespace Core {
  class Engine;
  class Globals;
}

class EngineRoot {
public:
  EngineRoot();
  ~EngineRoot();

  void Start();
  void AbortOnException(const std::exception& p_exc);

  Utils::FileLoader& getFileLoader();
  Utils::INIHandler& getEngineConfiguration();
  Graphics::TextureCache& getTextureCache();
  Graphics::ShaderCache& getShaderCache();
  Fonts::FontCache& getFontCache();
  Fonts::FontPackCache& getFontPackCache();
  Core::Globals& getGlobals();

  template <class ModuleType>
  ModuleType& getModule() {
    return m_loader.getModule<ModuleType>();
  }

private:
  HX3D_PIMPL

  Core::ModuleLoader m_loader;

  using SFileLoader = Utils::SingletonHolder<Utils::FileLoader>;
  using STextureCache = Utils::SingletonHolder<Graphics::TextureCache>;
  using SShaderCache = Utils::SingletonHolder<Graphics::ShaderCache>;
  using SFontCache = Utils::SingletonHolder<Fonts::FontCache>;
  using SFontPackCache = Utils::SingletonHolder<Fonts::FontPackCache>;
  using SGlobals = Utils::SingletonHolder<Core::Globals>;
};

using Root = Utils::SingletonHolder<EngineRoot>;

}
