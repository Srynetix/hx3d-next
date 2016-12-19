############
# PATHS

set(DEP_PATH_SDL2     "ThirdParty/SDL2-2.0.4")
set(DEP_PATH_SW       "ThirdParty/StackWalker")
set(DEP_PATH_EPOXY    "ThirdParty/libepoxy-master")
set(DEP_PATH_GLM      "ThirdParty/glm-0.9.8.1")
set(DEP_PATH_STB      "ThirdParty/stb")
set(DEP_PATH_FT       "ThirdParty/freetype-2.7")
set(DEP_PATH_UTFCPP   "ThirdParty/utfcpp-master")
set(DEP_PATH_ARCHIVE  "ThirdParty/miniz-114")

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

# glm
include_directories(${PROJECT_SOURCE_DIR}/${DEP_PATH_GLM})

# stb
include_directories(${PROJECT_SOURCE_DIR}/${DEP_PATH_STB})

# freetype
include_directories(${PROJECT_SOURCE_DIR}/${DEP_PATH_FT}/include)
link_directories(${PROJECT_BINARY_DIR}/${DEP_PATH_FT}/${CMAKE_BUILD_TYPE})

# utfcpp
include_directories(${PROJECT_SOURCE_DIR}/${DEP_PATH_UTFCPP}/source)

# miniz
include_directories(${PROJECT_SOURCE_DIR}/${DEP_PATH_ARCHIVE})
link_directories(${PROJECT_BINARY_DIR}/${DEP_PATH_ARCHIVE}/${CMAKE_BUILD_TYPE})
