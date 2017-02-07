project(hx3d-core)

set(SOURCES

  Engine.cpp
  ModuleLoader.cpp
  Root.cpp
  Globals.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
  hx3d-debug
  hx3d-fonts
  hx3d-game
  hx3d-graphics
  hx3d-input
  hx3d-math
  hx3d-text
  hx3d-tweening
  hx3d-ui
  hx3d-utils
  hx3d-window
)
