#include <Engine/Fonts/FontAtlas.hpp>
#include <Engine/Fonts/FontData.hpp>
#include <Engine/Fonts/FontPack.hpp>
#include <Engine/Fonts/Font.hpp>

#include <Engine/Text/Unicode.hpp>

#include <Engine/Graphics/Elements/Texture.hpp>
#include <Engine/Graphics/Elements/Buffers/AttributeBuffer.hpp>
#include <Engine/Graphics/Elements/Buffers/VertexArray.hpp>

#include <map>

namespace hx3d {
namespace Fonts {

struct FontAtlas::Impl {
  Graphics::VertexArray m_vertexArray;
  Graphics::AttributeBuffer4F m_buffer;
  Graphics::Texture m_texture;

  U32 m_textureWidth;
  U32 m_textureHeight;
  U32 m_lastX;

  std::map<U32, FontData> m_fontData;

  Impl(): m_textureWidth(512), m_textureHeight(512), m_lastX(0) {
    m_buffer.setShaderName("a_chardata");
  }
};

FontAtlas::FontAtlas():
  HX3D_PIMPL_INIT() {}

FontAtlas::~FontAtlas() {}

void FontAtlas::setTextureSize(const U32 p_width, const U32 p_height) {
  m_impl->m_textureWidth = p_width;
  m_impl->m_textureHeight = p_height;
}

void FontAtlas::generate(const Graphics::Shader& p_shader) {
  auto& impl = *m_impl;

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  impl.m_texture.generateFontTexture(m_impl->m_textureWidth, m_impl->m_textureHeight);

  impl.m_buffer.generateID();
  impl.m_vertexArray.generateID();

  impl.m_vertexArray.bindToContext();
  impl.m_buffer.bindBuffer();
  impl.m_buffer.linkToShader(p_shader);
  impl.m_buffer.bindAttribPointer();

  impl.m_texture.bindToContext();
}

void FontAtlas::bindToContext() {
  auto& impl = *m_impl;

  impl.m_vertexArray.bindToContext();
  impl.m_texture.bindToContext();
}

FontData& FontAtlas::storeAndFetchData(const FontPack& p_fontPack, const U32 p_code) {
  if (m_impl->m_fontData.find(p_code) == m_impl->m_fontData.end()) {
    auto data = p_fontPack.getCharacterData(p_code);

    // Adding in atlas
    m_impl->m_texture.bindToContext();
    data.m_tx = (F32)m_impl->m_lastX / m_impl->m_textureWidth;

    glTexSubImage2D(
      GL_TEXTURE_2D,
      0,
      m_impl->m_lastX,
      0,
      data.m_width,
      data.m_rows,
      GL_RED,
      GL_UNSIGNED_BYTE,
      data.m_buffer
    );

    m_impl->m_lastX += data.m_width;
    m_impl->m_fontData[p_code] = data;
  }

  return m_impl->m_fontData[p_code];
}

FontData& FontAtlas::storeAndFetchData(const Font& p_font, const U32 p_code) {
  if (m_impl->m_fontData.find(p_code) == m_impl->m_fontData.end()) {
    auto data = p_font.getCharacterData(p_code);

    // Adding in atlas
    m_impl->m_texture.bindToContext();
    data.m_tx = (F32)m_impl->m_lastX / m_impl->m_textureWidth;

    glTexSubImage2D(
      GL_TEXTURE_2D,
      0,
      m_impl->m_lastX,
      0,
      data.m_width,
      data.m_rows,
      GL_RED,
      GL_UNSIGNED_BYTE,
      data.m_buffer
    );

    m_impl->m_lastX += data.m_width;
    m_impl->m_fontData[p_code] = data;
  }

  return m_impl->m_fontData[p_code];
}

void FontAtlas::renderText(const Font& p_font, const std::string& p_string, const F32 p_x, const F32 p_y, const F32 p_w, const F32 p_h) {
  auto codes = Text::ToUTF32(p_string);
  this->renderText(p_font, codes, p_x, p_y, p_w, p_h);
}

void FontAtlas::renderText(const FontPack& p_fontPack, const std::string& p_string, const F32 p_x, const F32 p_y, const F32 p_w, const F32 p_h) {
  auto codes = Text::ToUTF32(p_string);
  this->renderText(p_fontPack, codes, p_x, p_y, p_w, p_h);
}

void FontAtlas::renderText(const FontPack& p_fontPack, const std::vector<U32>& p_codes, const F32 p_x, const F32 p_y, const F32 p_w, const F32 p_h) {
  auto& impl = *m_impl;

  S32 n = 0;
  F32 x = p_x;
  F32 y = p_y;

  bindToContext();
  impl.m_buffer.clear();

  for (auto code: p_codes) {
    auto& data = this->storeAndFetchData(p_fontPack, code);

    F32 x2 = x + data.m_left * p_w;
    F32 y2 = -y - data.m_top * p_h;
    F32 w = data.m_width * p_w;
    F32 h = data.m_rows * p_h;

    x += data.m_advanceX * p_w;
    y += data.m_advanceY * p_h;

    if (!w || !h)
      continue;

    impl.m_buffer.add(
      x2,         -y2,        data.m_tx,                                              0.f,
      x2 + w,     -y2,        data.m_tx + data.m_width / (F32)m_impl->m_textureWidth, 0.f,
      x2,         -y2 - h,    data.m_tx,                                              data.m_rows / (F32)m_impl->m_textureHeight,

      x2 + w,     -y2,        data.m_tx + data.m_width / (F32)m_impl->m_textureWidth, 0.f,
      x2,         -y2 - h,    data.m_tx,                                              data.m_rows / (F32)m_impl->m_textureHeight,
      x2 + w,     -y2 - h,    data.m_tx + data.m_width / (F32)m_impl->m_textureWidth, data.m_rows / (F32)m_impl->m_textureHeight
    );

    n += 6;
  }

  impl.m_buffer.uploadToGPU(Graphics::Buffer::kDynamic);

  glDrawArrays(GL_TRIANGLES, 0, n);
}

void FontAtlas::renderText(const Font& p_font, const std::vector<U32>& p_codes, const F32 p_x, const F32 p_y, const F32 p_w, const F32 p_h) {
  auto& impl = *m_impl;

  S32 n = 0;
  F32 x = p_x;
  F32 y = p_y;

  bindToContext();
  impl.m_buffer.clear();

  for (auto code: p_codes) {
    auto& data = this->storeAndFetchData(p_font, code);

    F32 x2 = x + data.m_left * p_w;
    F32 y2 = -y - data.m_top * p_h;
    F32 w = data.m_width * p_w;
    F32 h = data.m_rows * p_h;

    x += data.m_advanceX * p_w;
    y += data.m_advanceY * p_h;

    if (!w || !h)
      continue;

    impl.m_buffer.add(
      x2,         -y2,        data.m_tx,                                              0.f,
      x2 + w,     -y2,        data.m_tx + data.m_width / (F32)m_impl->m_textureWidth, 0.f,
      x2,         -y2 - h,    data.m_tx,                                              data.m_rows / (F32)m_impl->m_textureHeight,

      x2 + w,     -y2,        data.m_tx + data.m_width / (F32)m_impl->m_textureWidth, 0.f,
      x2,         -y2 - h,    data.m_tx,                                              data.m_rows / (F32)m_impl->m_textureHeight,
      x2 + w,     -y2 - h,    data.m_tx + data.m_width / (F32)m_impl->m_textureWidth, data.m_rows / (F32)m_impl->m_textureHeight
    );

    n += 6;
  }

  impl.m_buffer.uploadToGPU(Graphics::Buffer::kDynamic);

  glDrawArrays(GL_TRIANGLES, 0, n);
}

}
}
