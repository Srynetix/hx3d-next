############
# PATHS

set(DEP_PATH_SDL2   "ThirdParty/SDL2-2.0.4")
set(DEP_PATH_SW     "ThirdParty/StackWalker")
set(DEP_PATH_EPOXY  "ThirdParty/libepoxy-master")

# SDL2
include_directories(${PROJECT_SOURCE_DIR}/${DEP_PATH_SDL2}/include)
link_directories(${PROJECT_BINARY_DIR}/${DEP_PATH_SDL2}/${CMAKE_BUILD_TYPE})

# StackWalker
include_directories(${PROJECT_SOURCE_DIR}/${DEP_PATH_SW})
link_directories(${PROJECT_BINARY_DIR}/${DEP_PATH_SW}/${CMAKE_BUILD_TYPE})

# epoxy
include_directories(${PROJECT_SOURCE_DIR}/${DEP_PATH_EPOXY}/include)
include_directories(${PROJECT_BINARY_DIR}/${DEP_PATH_EPOXY}/include)
link_directories(${PROJECT_BINARY_DIR}/${DEP_PATH_EPOXY}/src/${CMAKE_BUILD_TYPE})
