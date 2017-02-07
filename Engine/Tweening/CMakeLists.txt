project(hx3d-tweening)

set(SOURCES
  AbstractTween.cpp
  TweenOptions.cpp
  MultiTween.cpp
  TweenSystem.cpp
  Sequence.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
