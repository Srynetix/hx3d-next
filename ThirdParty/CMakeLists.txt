add_subdirectory(SDL2-2.0.4)

if(WIN32)
add_subdirectory(StackWalker)
endif()

add_subdirectory(libepoxy-master)
add_subdirectory(stb)
add_subdirectory(freetype-2.7)
add_subdirectory(miniz-114)
add_subdirectory(Box2D/Box2D)
