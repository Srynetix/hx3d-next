#include <Engine/Graphics/Elements/Texture.hpp>
#include <Engine/Debug/Logging.hpp>

#include <Engine/Utils/IO/FileLoader.hpp>
#include <Engine/Graphics/OpenGLContext.hpp>
#include <Engine/Core/Root.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace hx3d {
namespace Graphics {

Texture Texture::m_blankTexture;
U32 Texture::m_currentTextureID = 0;

Texture::Texture():
  m_width(0),
  m_height(0),
  m_loaded(false)
  {}

Texture::~Texture() {
  if (glIsTexture(m_id)) {
    glDeleteTextures(1, &m_id);
  }
}

void Texture::generateID() {
  if (!glIsTexture(m_id)) {
    glGenTextures(1, &m_id);
  }
}

void Texture::bindToContext(const bool p_force) {
  if (p_force || m_currentTextureID != m_id) {
    glBindTexture(GL_TEXTURE_2D, m_id);
    HX3D_LOGGER(kGraphicsLowLevel).debug("Texture %u active.", m_id);
    m_currentTextureID = m_id;
  }
}

void Texture::generateFontTexture(const U32 p_width, const U32 p_height) {
  this->generateID();

  U32 lastBound = m_currentTextureID;
  glBindTexture(GL_TEXTURE_2D, m_id);

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RED,
    p_width,
    p_height,
    0,
    GL_RED,
    GL_UNSIGNED_BYTE,
    0
  );

  this->setFilter(kMinFilter, kLinear);
  this->setFilter(kMagFilter, kLinear);
  this->setFilter(kWrapS, kClampToEdge);
  this->setFilter(kWrapT, kClampToEdge);

  m_currentTextureID = lastBound;
  glBindTexture(GL_TEXTURE_2D, lastBound);
}

void Texture::loadFromFile(const std::string& p_pathToFile) {
  auto& loader = Root::Instance().getFileLoader();
  auto& file = loader.syncLoad(p_pathToFile, Utils::File::kBinary);

  this->generateID();

  int bpp = 0;
  auto fileSize = file.getSize();

  char* fileContent = file.getContent();
  unsigned char* uFileContent = reinterpret_cast<unsigned char*>(fileContent);
  unsigned char* stb_fileContent = stbi_load_from_memory(uFileContent, (U32)fileSize, (int*)&m_width, (int*)&m_height, &bpp, 0);
  HX3D_LOGGER(kGraphicsLowLevel).debug("Texture is %u x %u", m_width, m_height);

  U32 lastBound = m_currentTextureID;
  glBindTexture(GL_TEXTURE_2D, m_id);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, stb_fileContent);

  this->setFilter(kMinFilter, kNearest);
  this->setFilter(kMagFilter, kNearest);
  this->setFilter(kWrapS, kMirroredRepeat);
  this->setFilter(kWrapT, kMirroredRepeat);

  m_currentTextureID = lastBound;
  glBindTexture(GL_TEXTURE_2D, lastBound);

  m_loaded = true;
  stbi_image_free(stb_fileContent);
}

void Texture::setFilter(const FilterParameter p_param, const FilterValue p_value) {
  glTexParameteri(GL_TEXTURE_2D, p_param, p_value);
}

void Texture::disableTextures() {
  if (m_currentTextureID != 0) {
    HX3D_LOGGER(kGraphicsLowLevel).debug("Textures disabled.");
    glBindTexture(GL_TEXTURE_2D, 0);
    m_currentTextureID = 0;
  }
}

U32 Texture::getLastBound() {
  return m_currentTextureID;
}

///////////////

Texture& Texture::Blank() {
  Texture& texture = m_blankTexture;
  if (!texture.m_loaded) {
    generateBlankTexture();
  }

  return texture;
}

void Texture::generateBlankTexture() {
  Texture& texture = m_blankTexture;

  texture.m_width = 1;
  texture.m_height = 1;
  texture.m_loaded = true;

  U32 lastBound = m_currentTextureID;
  S16 pixels[] = { -1, -1, -1, 0 };

  texture.generateID();
  texture.bindToContext();

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  texture.setFilter(kMinFilter, kNearest);
  texture.setFilter(kMagFilter, kNearest);
  texture.setFilter(kWrapS, kClampToEdge);
  texture.setFilter(kWrapT, kClampToEdge);

  m_currentTextureID = lastBound;
  glBindTexture(GL_TEXTURE_2D, lastBound);
}

}
}
