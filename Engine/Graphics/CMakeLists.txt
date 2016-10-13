project(hx3d-graphics)

set(SOURCES
  OpenGLContext.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} epoxy_0 SDL2)
