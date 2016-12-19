#include <Engine/Fonts/FontsModule.hpp>
#include <Engine/Debug/Logging.hpp>

namespace hx3d {
namespace Fonts {

void FontsModule::setUp() {
  if (FT_Init_FreeType(&m_library)) {
    HX3D_LOGGER(kFont).critical("FreeType init error.");
  }

  HX3D_LOGGER(kFont).info("FontModule initialized.");
}

const FT_Library& FontsModule::getLibrary() const {
  return m_library;
}

void FontsModule::tearDown() {
  HX3D_LOGGER(kFont).info("FontModule stopped.");
}

}
}
