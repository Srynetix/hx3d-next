set(ASSETS_PATH "Assets")

configure_file(
  EngineConfig.hpp.in
  ${PROJECT_BINARY_DIR}/Configured/EngineConfig.hpp
)

add_subdirectory(Debug)
add_subdirectory(Core)
add_subdirectory(Fonts)
add_subdirectory(Utils)
add_subdirectory(Graphics)
add_subdirectory(Input)
add_subdirectory(Game)
add_subdirectory(Math)
add_subdirectory(Text)
add_subdirectory(Tweening)
add_subdirectory(Window)
add_subdirectory(UI)

file(COPY ${ASSETS_PATH} DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
