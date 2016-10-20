project(hx3d-utils)

set(SOURCES

  IO/Path.cpp
  IO/File.cpp
  IO/FileLoader.cpp
  Parsers/INIParser.cpp
  Parsers/INIHandler.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME})
