project(hx3d-desktop-test)

set(SOURCES
  Main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} hx3d-core hx3d-graphics)
