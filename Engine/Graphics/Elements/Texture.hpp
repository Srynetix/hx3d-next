#pragma once

#include <Engine/Graphics/GLHeaders.hpp>
#include <Engine/Utils/IO/File.hpp>
#include <Engine/Utils/Uncopyable.hpp>
#include <Engine/Core/Types.hpp>

#include <string>

namespace hx3d {
namespace Graphics {

class Texture: public Utils::Uncopyable {
public:
  enum FilterParameter {
    kMinFilter  = GL_TEXTURE_MIN_FILTER,
    kMagFilter  = GL_TEXTURE_MAG_FILTER,
    kWrapS      = GL_TEXTURE_WRAP_S,
    kWrapT      = GL_TEXTURE_WRAP_T
  };

  enum FilterValue {
    kLinear               = GL_LINEAR,
    kNearest              = GL_NEAREST,
    kLinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR,
    kNearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
    kLinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
    kNearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,

    kClampToEdge          = GL_CLAMP_TO_EDGE,
    kMirroredRepeat       = GL_MIRRORED_REPEAT,
    kRepeat               = GL_REPEAT
  };

  Texture();
  ~Texture();

  void generateID();
  void bindToContext(const bool p_force = false);

  void generateFontTexture(const U32 p_width, const U32 p_height);
  void loadFromFile(const std::string& p_pathToFile);

  void setFilter(const FilterParameter p_param, const FilterValue p_value);

  static Texture& Blank();

  static U32 getLastBound();
  static void disableTextures();

private:
  U32 m_id;
  U32 m_width;
  U32 m_height;
  bool m_loaded;

  static U32 m_currentTextureID;
  static Texture m_blankTexture;

  static void generateBlankTexture();
};

}
}
