project(hx3d-math)

set(SOURCES
  NumberUtils.cpp
  VectorUtils.cpp
  Transform.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
