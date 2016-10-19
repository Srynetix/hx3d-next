set(ASSETS_PATH "Assets")

configure_file(
  EngineConfig.hpp.in
  ${PROJECT_BINARY_DIR}/Configured/EngineConfig.hpp
)

add_subdirectory(Debug)
add_subdirectory(Core)
add_subdirectory(Utils)
add_subdirectory(Graphics)
add_subdirectory(Window)

file(COPY ${ASSETS_PATH} DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
