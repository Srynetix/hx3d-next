configure_file(
  EngineConfig.hpp.in
  ${PROJECT_BINARY_DIR}/Configured/EngineConfig.hpp
)

add_subdirectory(Debug)
add_subdirectory(Core)
add_subdirectory(Graphics)
add_subdirectory(Window)
