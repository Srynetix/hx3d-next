project(hx3d-text)

set(SOURCES
  Unicode.cpp
  String.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME})
