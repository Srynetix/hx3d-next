#include <Engine/Graphics/Elements/Renderbuffer.hpp>

#include <Engine/Core/Root.hpp>
#include <Engine/Core/Globals.hpp>

namespace hx3d {
namespace Graphics {

S32 Renderbuffer::m_defaultRenderbufferId = 0;
std::stack<Utils::SharedPtr<Renderbuffer>> Renderbuffer::m_bufferStack;

Renderbuffer::Renderbuffer():
  Renderbuffer(
    HX3D_GLOB_GET("win.width", U16),
    HX3D_GLOB_GET("win.height", U16)
  )
{}

Renderbuffer::Renderbuffer(const U16 p_width, const U16 p_height):
  m_width(p_width), m_height(p_height), m_renderbufferId(0), m_depthbufferId(0)
{
  create();
}

Renderbuffer::~Renderbuffer() {
  if (glIsFramebuffer(m_renderbufferId) == GL_TRUE)
    glDeleteFramebuffers(1, &m_renderbufferId);
  if (glIsRenderbuffer(m_depthbufferId) == GL_TRUE)
    glDeleteRenderbuffers(1, &m_depthbufferId);

  HX3D_LOGGER(kGraphicsLowLevel).debug("Renderbuffer deleted: {}", this);
}

void Renderbuffer::resize(const U16 p_width, const U16 p_height) {
  m_width = p_width;
  m_height = p_height;

  create();
}

void Renderbuffer::storeDefaultRenderbuffer() {
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_defaultRenderbufferId);
}

void Renderbuffer::create() {
  if (glIsFramebuffer(m_renderbufferId) == GL_TRUE)
    glDeleteFramebuffers(1, &m_renderbufferId);

  // Génération d'un id
  glGenFramebuffers(1, &m_renderbufferId);
  glBindFramebuffer(GL_FRAMEBUFFER, m_renderbufferId);

  m_colorbuffer = Utils::MakeSharedPtr<Texture>();
  m_colorbuffer->generateColorBuffer(m_width, m_height);
  m_colorbuffer->bindToContext();

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorbuffer->getID(), 0);

  this->createBuffer(m_depthbufferId, GL_DEPTH_COMPONENT16);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthbufferId);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    glDeleteFramebuffers(1, &m_renderbufferId);
    glDeleteRenderbuffers(1, &m_depthbufferId);

    HX3D_LOGGER(kGraphicsLowLevel).debug("Renderbuffer creation error.");
  }

  else {
    HX3D_LOGGER(kGraphicsLowLevel).debug("Renderbuffer {} created (size: {}x{}).", this, m_width, m_height);
  }

  glBindFramebuffer(GL_FRAMEBUFFER, m_defaultRenderbufferId);
}

void Renderbuffer::pushBuffer(const Utils::SharedPtr<Renderbuffer>& p_buffer) {
  p_buffer->bindToContext();
  m_bufferStack.push(p_buffer);
}

void Renderbuffer::popBuffer() {
  m_bufferStack.pop();
  if (m_bufferStack.size() == 0) {
    Renderbuffer::useDefaultBuffer();
  } else {
    auto& buf = m_bufferStack.top();
    buf->bindToContext();
  }
}

const Utils::SharedPtr<Texture>& Renderbuffer::toTexture() const {
  return m_colorbuffer;
}

void Renderbuffer::bindToContext() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_renderbufferId);
  glViewport(0, 0, m_width, m_height);
}

void Renderbuffer::useDefaultBuffer() {
  auto w = HX3D_GLOB_GET("win.width", U16);
  auto h = HX3D_GLOB_GET("win.height", U16);
  glBindFramebuffer(GL_FRAMEBUFFER, m_defaultRenderbufferId);
  glViewport(0, 0, w, h);
}

void Renderbuffer::createBuffer(U32& p_id, GLenum p_format) {
  if (glIsRenderbuffer(p_id) == GL_TRUE)
    glDeleteRenderbuffers(1, &p_id);

  glGenRenderbuffers(1, &p_id);
  glBindRenderbuffer(GL_RENDERBUFFER, p_id);
  glRenderbufferStorage(GL_RENDERBUFFER, p_format, m_width, m_height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

}
}
