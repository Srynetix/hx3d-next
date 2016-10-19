project(hx3d-core)

set(SOURCES

  Engine.cpp
  ModuleLoader.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} hx3d-window hx3d-debug)
