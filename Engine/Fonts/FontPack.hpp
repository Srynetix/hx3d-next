#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>
#include <Engine/Fonts/FontData.hpp>

namespace hx3d {
namespace Fonts {

class FontPack {
public:
  FontPack();
  ~FontPack();

  void loadFromFile(const std::string& p_pathToFile);

  FontData getCharacterData(const U32 p_code) const;

private:
  HX3D_PIMPL
};

}
}
