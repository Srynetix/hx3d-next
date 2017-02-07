cmake_minimum_required(VERSION 3.0)

project(hx3d)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

option(BUILD_GAME     "Build the game"   ON)
option(BUILD_TESTS    "Build the tests"  ON)
option(BUILD_RELEASE  "Build release"    OFF)

if(BUILD_RELEASE)
  set(CMAKE_BUILD_TYPE Release)
else()
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(ThirdParty)
include(ThirdParty/ThirdPartyConfig.cmake)

set(HX3D_MAJOR_VERSION 1)
set(HX3D_MINOR_VERSION 0)
set(HX3D_BUILD_VERSION 0)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}/Configured
)

add_subdirectory(Engine)

if(BUILD_TESTS)
  add_subdirectory(Tests)
endif()

if (BUILD_GAME)
  add_subdirectory(SmashGame)
endif()
