#pragma once

#include <Engine/Graphics/GLHeaders.hpp>

namespace hx3d {
namespace Graphics {

class VertexArray {
public:
  VertexArray();
  ~VertexArray();

  void generateID();
  void bindToContext();

  GLuint getID() const;

  static void disableVertexArrays();

private:
  GLuint m_id;

  static GLuint m_currentVAID;
};

}
}
