#include <Engine/Fonts/Font.hpp>

#include <Engine/Core/Root.hpp>

#include <Engine/Fonts/FontAtlas.hpp>
#include <Engine/Fonts/FontsModule.hpp>

#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <Engine/Graphics/Elements/Buffers/Buffer.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace hx3d {
namespace Fonts {

struct Font::Impl {
  Utils::File m_file;
  FT_Face m_face;
};

Font::Font():
  HX3D_PIMPL_INIT() {}

Font::~Font() = default;

void Font::loadFromFile(Utils::File&& p_file) {
  auto& impl = *m_impl;
  auto& fontModule = Root::Instance().getModule<Fonts::FontsModule>();
  impl.m_file = std::move(p_file);

  auto error = FT_New_Memory_Face(
    fontModule.getLibrary(),
    impl.m_file.getUContent(),
    (FT_Long)impl.m_file.getSize(),
    0,
    &impl.m_face
  );

  if (error) {
    HX3D_LOGGER(kFont).critical("Font load error: {}", error);
  }
}

void Font::loadFromFile(const std::string& p_path) {
  auto& impl = *m_impl;
  auto& fontModule = Root::Instance().getModule<Fonts::FontsModule>();
  auto& loader = Root::Instance().getFileLoader();

  impl.m_file = loader.syncLoad(p_path, Utils::File::kBinary);
  auto error = FT_New_Memory_Face(
    fontModule.getLibrary(),
    impl.m_file.getUContent(),
    (FT_Long)impl.m_file.getSize(),
    0,
    &impl.m_face
  );

  if (error) {
    HX3D_LOGGER(kFont).critical("Font load error: {}", error);
  }
}

void Font::updateSize(const U16 p_height, const U16 p_deviceWidth, const U16 p_deviceHeight) {
  auto& impl = *m_impl;
  auto error = FT_Set_Char_Size(
    impl.m_face,             /* handle to face object           */
    0,                  /* char_width in 1/64th of points  */
    p_height*64,        /* char_height in 1/64th of points */
    p_deviceWidth,      /* horizontal device resolution    */
    p_deviceHeight      /* vertical device resolution      */
  );

  if (error) {
    HX3D_LOGGER(kFont).critical("Font resize error: {}", error);
  }
}

FontData Font::getCharacterData(const U32 p_code) const {
  auto index = FT_Get_Char_Index(m_impl->m_face, p_code);
  if (FT_Load_Glyph(m_impl->m_face, index, FT_LOAD_DEFAULT)) {
    HX3D_LOGGER(kFont).error("ERROR LOAD GLYPH");
  }

  if (FT_Render_Glyph(m_impl->m_face->glyph, FT_RENDER_MODE_NORMAL)) {
    HX3D_LOGGER(kFont).error("ERROR RENDER GLYPH");
  }

  auto& g = m_impl->m_face->glyph;

  auto data = FontData();
  data.m_width = g->bitmap.width;
  data.m_rows = g->bitmap.rows;
  data.m_left = g->bitmap_left;
  data.m_top = g->bitmap_top;

  data.m_advanceX = g->advance.x >> 6;
  data.m_advanceY = g->advance.y >> 6;
  data.m_buffer = g->bitmap.buffer;
  return data;
}

bool Font::isCharacterAvailable(const U32 p_code) {
  return FT_Get_Char_Index(m_impl->m_face, p_code) != 0;
}

}
}
