#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Graphics/GLHeaders.hpp>

#include <SDL.h>

#define HX3D_GL_ERROR(msg) \
  { \
    auto _gl_err = glGetError(); \
    if (_gl_err != GL_NO_ERROR) { \
      HX3D_LOGGER(kGraphics).error("[GL ERR] %s: %lu (%s [%d])", msg, _gl_err, __FILE__, __LINE__); \
    } else { \
      HX3D_LOGGER(kGraphics).debug("[GL ERR] %s: OK (%s [%d])", msg, __FILE__, __LINE__); \
    } \
  }

namespace hx3d {
namespace Graphics {

class OpenGLContext {
public:
  OpenGLContext();

  void setDoubleBuffer(const bool p_value);
  void setMultisampleBuffers(const U8 p_value);
  void setMultisampleSamples(const U8 p_value);

  static void enableFlag(const GLenum p_flag);
  static void disableFlag(const GLenum p_flag);

  void setViewport(const U16 p_width, const U16 p_height);
  void createContext(SDL_Window* p_window);
  void swapWindow(SDL_Window* p_window);

  static void checkForErrors();

  void setUp();
  void tearDown();

private:
  const char* showGLVersion();

  bool m_attrDoubleBuffer;
  U8 m_attrMultisampleBuffers;
  U8 m_attrMultisampleSamples;

  SDL_GLContext m_context;
};

}
}
