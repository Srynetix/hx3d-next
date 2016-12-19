#pragma once

#include <Engine/Core/Module.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace hx3d {
namespace Fonts {

class FontsModule: public Core::Module {
public:
  virtual void setUp() override;
  virtual void tearDown() override;

  const FT_Library& getLibrary() const;

private:
  FT_Library m_library;
};

}
}
