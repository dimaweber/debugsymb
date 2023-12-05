cmake_minimum_required(VERSION 3.27)

set (TARGET stepper)
set (SOURCES main.cpp)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} class)

create_ds(${TARGET})

install (TARGETS ${TARGET} RUNTIME)
