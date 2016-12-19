PROJECT(miniz)
cmake_minimum_required(VERSION 2.8)

set(SOURCES
  miniz.c
)

add_library(${PROJECT_NAME} ${SOURCES})
