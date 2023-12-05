cmake_minimum_required(VERSION 3.27)

set (TARGET global)
set (SOURCES global_lib.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(${TARGET} STATIC ${SOURCES})
