#pragma once

#include <Engine/Utils/Uncopyable.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Core/Types.hpp>

#include <Engine/Fonts/FontData.hpp>

namespace hx3d {

namespace Utils {
  class File;
}

namespace Fonts {

class Font: public Utils::Uncopyable {
public:
  Font();
  ~Font();

  void loadFromFile(Utils::File&& p_file);
  void loadFromFile(const std::string& p_path);

  void updateSize(const U16 p_height, const U16 p_deviceWidth, const U16 p_deviceHeight);

  bool isCharacterAvailable(const U32 p_code);
  FontData getCharacterData(const U32 p_code) const;

private:
  HX3D_PIMPL
};

}
}
