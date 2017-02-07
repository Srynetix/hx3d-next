project(hx3d-debug)

set(SOURCES
  Logger.cpp
  Logging.cpp
  CrashHandler.cpp
  StackTraceHandler.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} StackWalker)
