project(smashgame-common)

set(SOURCES
  SmashGame.cpp

  Scenes/SplashScene.cpp
  Scenes/StageScene.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
