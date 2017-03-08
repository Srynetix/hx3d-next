project(hx3d-game)

set(SOURCES
  Game.cpp

  Scene.cpp
  SceneLoader.cpp

  SceneGraph.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Box2D)
