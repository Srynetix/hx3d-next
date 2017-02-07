#pragma once

#include <Engine/Core/Types.hpp>
#include <Engine/Graphics/GLHeaders.hpp>
#include <Engine/Graphics/Elements/Texture.hpp>
#include <Engine/Utils/Memory/SmartPtrs.hpp>

#include <stack>

namespace hx3d {
namespace Graphics {

class Renderbuffer {
public:
  Renderbuffer();
  Renderbuffer(const U16 p_width, const U16 p_height);
  ~Renderbuffer();

  void resize(const U16 p_width, const U16 p_height);
  void bindToContext();

  const Utils::SharedPtr<Texture>& toTexture() const;

  static void storeDefaultRenderbuffer();

  static void pushBuffer(const Utils::SharedPtr<Renderbuffer>& p_buffer);
  static void popBuffer();
  static void useDefaultBuffer();

private:
  U16 m_width;
  U16 m_height;
  U32 m_renderbufferId;
  U32 m_depthbufferId;
  Utils::SharedPtr<Texture> m_colorbuffer;

  static S32 m_defaultRenderbufferId;
  static std::stack<Utils::SharedPtr<Renderbuffer>> m_bufferStack;

  void create();
  void createBuffer(U32& p_id, GLenum p_format);
};

}
}
