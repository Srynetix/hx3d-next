set(GAME_ASSETS_PATH "Assets")

add_subdirectory(Common)
add_subdirectory(Desktop)

file(COPY ${GAME_ASSETS_PATH} DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
