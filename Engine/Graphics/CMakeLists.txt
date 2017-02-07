project(hx3d-graphics)

set(SOURCES
  Elements/Shader.cpp
  Elements/Texture.cpp
  Elements/Sprite.cpp
  Elements/Color.cpp
  Elements/Renderbuffer.cpp
  Elements/Drawable.cpp

  Elements/Cameras/Camera.cpp
  Elements/Cameras/Camera2D.cpp

  Elements/Buffers/Buffer.cpp
  Elements/Buffers/VertexArray.cpp

  Elements/Shapes/Shape.cpp
  Elements/Shapes/Circle.cpp
  Elements/Shapes/Rectangle.cpp

  Elements/Geometries/Base/BaseGeometry.cpp
  Elements/Geometries/Base/BaseArrayGeometry.cpp
  Elements/Geometries/Base/BaseIndexGeometry.cpp
  Elements/Geometries/Base/PCTIndexGeometry.cpp
  Elements/Geometries/TriangleGeometry.cpp
  Elements/Geometries/CircleGeometry.cpp
  Elements/Geometries/QuadGeometry.cpp
  Elements/Geometries/PCTQuadGeometry.cpp

  OpenGLContext.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} epoxy_0)
