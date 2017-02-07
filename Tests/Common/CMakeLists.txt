project(hx3d-tests-common)

set(SOURCES

  TestGame.cpp
  Scenes/TestScene.cpp
  Scenes/GUIScene.cpp
  Scenes/TweenScene.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
