project(hx3d-graphics)

set(SOURCES
  Elements/Shader.cpp

  OpenGLContext.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} hx3d-debug epoxy_0 SDL2)
