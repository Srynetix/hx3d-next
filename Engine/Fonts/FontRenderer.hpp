#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Graphics/Elements/Color.hpp>

namespace hx3d {
namespace Fonts {

class Font;
class FontPack;
class FontRenderer {
public:
  FontRenderer();
  ~FontRenderer();

  void renderText(const FontPack& p_fontPack, const std::string& p_string,
                  const F32 p_x, const F32 p_y,
                  const F32 p_sx, const F32 p_sy, const Graphics::Color p_color);

  void renderText(const Font& p_font, const std::string& p_string,
                  const F32 p_x, const F32 p_y,
                  const F32 p_sx, const F32 p_sy, const Graphics::Color p_color);

private:
  HX3D_PIMPL
};

}
}
