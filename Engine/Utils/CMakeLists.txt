project(hx3d-utils)

set(SOURCES

  IO/Path.cpp
  IO/File.cpp
  IO/FileLoader.cpp
  IO/FileHandler.cpp

  Parsers/INIParser.cpp
  Parsers/INIHandler.cpp

  Time/Chronometer.cpp

  Compression/ZipFile.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} miniz)
