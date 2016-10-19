#pragma once

#include <Engine/Core/Types.hpp>

#include <SDL.h>

namespace hx3d {
namespace Graphics {

class OpenGLContext {
public:
  OpenGLContext();

  void setDoubleBuffer(const bool p_value);
  void setMultisampleBuffers(const U8 p_value);
  void setMultisampleSamples(const U8 p_value);

  void setViewport(const U16 p_width, const U16 p_height);
  void createContext(SDL_Window* p_window);
  void swapWindow(SDL_Window* p_window);

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
