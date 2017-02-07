project(hx3d-fonts)

set(SOURCES
  Font.cpp
  FontAtlas.cpp
  FontRenderer.cpp
  FontPack.cpp

  FontsModule.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} freetype)
