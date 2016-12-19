#include <Engine/Fonts/FontPack.hpp>
#include <Engine/Fonts/FontCache.hpp>

#include <Engine/Core/Root.hpp>

#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Utils/Compression/ZipFile.hpp>

#include <Engine/Text/String.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace hx3d {
namespace Fonts {

struct FontPack::Impl {
  std::vector<Font*> m_fonts;
  Utils::Compression::ZipFile m_zipFile;
};

FontPack::FontPack():
  HX3D_PIMPL_INIT() {}

FontPack::~FontPack() = default;

void FontPack::loadFromFile(const std::string& p_pathToFile) {
  auto& fontCache = Root::Instance().getFontCache();
  auto& impl = *m_impl;

  impl.m_zipFile.loadFromFile(p_pathToFile);

  auto count = impl.m_zipFile.getFileCount();
  for (auto i = 0U; i < count; ++i) {
    auto stat = impl.m_zipFile.getFileStat(i);
    auto file = impl.m_zipFile.extractFileByName(stat.getFilename());
    auto slugname = Text::SlugFilename(stat.getFilename());

    fontCache.loadFromFile(slugname, std::move(file));
    impl.m_fonts.push_back(&fontCache.get(slugname));
  }
}

FontData FontPack::getCharacterData(const U32 p_code) const {
  assert(m_impl->m_fonts.size() > 0);

  for (auto font: m_impl->m_fonts) {
    if (font->isCharacterAvailable(p_code)) {
      return font->getCharacterData(p_code);
    }
  }

  return m_impl->m_fonts[0]->getCharacterData(p_code);
}

}
}
