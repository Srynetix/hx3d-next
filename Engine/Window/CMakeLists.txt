project(hx3d-window)

set(SOURCES
  WindowModule.cpp
  Window.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} SDL2)
