#include <Engine/Fonts/FontRenderer.hpp>
#include <Engine/Fonts/FontAtlas.hpp>
#include <Engine/Fonts/Font.hpp>

#include <Engine/Core/Root.hpp>

#include <Engine/Graphics/ShaderCache.hpp>
#include <Engine/Graphics/Elements/Shader.hpp>

namespace hx3d {
namespace Fonts {

struct FontRenderer::Impl {
  FontAtlas m_atlas;
  Graphics::Shader& m_shader;

  Impl():
    m_shader(Root::Instance().getShaderCache().get("font")) {
      m_shader.useProgram();

      m_atlas.setTextureSize(512, 128);
      m_atlas.generate(m_shader);
    }
};

FontRenderer::FontRenderer():
  HX3D_PIMPL_INIT() {}

FontRenderer::~FontRenderer() {}

void FontRenderer::renderText(const Font& p_font, const std::string& p_string,
                              const F32 p_x, const F32 p_y,
                              const F32 p_sx, const F32 p_sy, const Graphics::Color p_color) {

  m_impl->m_shader.useProgram();
  m_impl->m_shader.sendUniform("u_color", p_color);

  m_impl->m_atlas.renderText(p_font, p_string, p_x, p_y, p_sx, p_sy);
}

void FontRenderer::renderText(const FontPack& p_fontPack, const std::string& p_string,
                              const F32 p_x, const F32 p_y,
                              const F32 p_sx, const F32 p_sy, const Graphics::Color p_color) {

  m_impl->m_shader.useProgram();
  m_impl->m_shader.sendUniform("u_color", p_color);



  m_impl->m_atlas.renderText(p_fontPack, p_string, p_x, p_y, p_sx, p_sy);
}

}
}
