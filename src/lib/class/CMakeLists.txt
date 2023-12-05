cmake_minimum_required(VERSION 3.27)

set (TARGET class)
set (SOURCES class_lib.cpp)

add_library(${TARGET} SHARED ${SOURCES})
target_link_libraries(${TARGET} global)

create_ds(${TARGET})

install (TARGETS ${TARGET} LIBRARY)
