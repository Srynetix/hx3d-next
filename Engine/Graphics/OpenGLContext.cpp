#include <Engine/Graphics/OpenGLContext.hpp>
#include <Engine/Graphics/GLHeaders.hpp>

#include <Engine/Debug/Logging.hpp>

namespace hx3d {
namespace Graphics {

OpenGLContext::OpenGLContext():
  m_attrDoubleBuffer(true),
  m_attrMultisampleSamples(0),
  m_attrMultisampleBuffers(0)
{}

void OpenGLContext::setDoubleBuffer(const bool p_value) {
  m_attrDoubleBuffer = p_value;
}

void OpenGLContext::setMultisampleSamples(const U8 p_value) {
  m_attrMultisampleSamples = p_value;
}

void OpenGLContext::setMultisampleBuffers(const U8 p_value) {
  m_attrMultisampleBuffers = p_value;
}

void OpenGLContext::createContext(SDL_Window* p_window) {
  SDL_GL_CreateContext(p_window);

  const auto& logger = HX3D_LOGGER(kGraphics);
  logger.info("Initializing OpenGL version %s", showGLVersion());
}

void OpenGLContext::setViewport(const U16 p_width, const U16 p_height) {
  glViewport(0, 0, p_width, p_height);
}

void OpenGLContext::swapWindow(SDL_Window* p_window) {
  SDL_GL_SwapWindow(p_window);
}

void OpenGLContext::setUp() {
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, m_attrDoubleBuffer);

  if (m_attrMultisampleBuffers) {
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, m_attrMultisampleBuffers);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, m_attrMultisampleSamples);
  }

  // Platform-specific
#ifdef __ANDROID__

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

#else

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

#endif
}

void OpenGLContext::tearDown() {
  SDL_GL_DeleteContext(m_context);
}

///////////////////////

const char* OpenGLContext::showGLVersion() {
  switch (epoxy_gl_version()) {
    case 33:
      return "3.3";
    default:
      return "Not yet implemented";
  }
}

}
}
