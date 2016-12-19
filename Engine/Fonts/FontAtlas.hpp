#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Utils/Uncopyable.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <vector>

namespace hx3d {

namespace Graphics {
  class Shader;
}

namespace Fonts {

class Font;
class FontPack;
struct FontData;

class FontAtlas: public Utils::Uncopyable {
public:
  FontAtlas();
  ~FontAtlas();

  void generate(const Graphics::Shader& p_shader);
  void setTextureSize(const U32 p_width, const U32 p_height);
  void bindToContext();

  FontData& storeAndFetchData(const Font& p_font, const U32 p_code);
  FontData& storeAndFetchData(const FontPack& p_fontPack, const U32 p_code);

  void renderText(const Font& p_font, const std::string& p_string, const F32 p_x, const F32 p_y, const F32 p_w, const F32 p_h);
  void renderText(const Font& p_font, const std::vector<U32>& p_codes, const F32 p_x, const F32 p_y, const F32 p_w, const F32 p_h);

  void renderText(const FontPack& p_fontPack, const std::string& p_string, const F32 p_x, const F32 p_y, const F32 p_w, const F32 p_h);
  void renderText(const FontPack& p_fontPack, const std::vector<U32>& p_codes, const F32 p_x, const F32 p_y, const F32 p_w, const F32 p_h);

private:
  HX3D_PIMPL
};

}
}
