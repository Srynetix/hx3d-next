project(hx3d-window)

set(SOURCES
  WindowModule.cpp
  Window.cpp

  ScreenLoader.cpp
  Screen.cpp
  Game.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} hx3d-debug hx3d-graphics)
