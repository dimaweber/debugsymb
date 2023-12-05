cmake_minimum_required(VERSION 3.27)

set (TARGET global)
set (SOURCES global_lib.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(${TARGET} STATIC ${SOURCES})

#set (TARGET_DS ${CMAKE_BINARY_DIR}/${TARGET}.${DEBUG_SYMBOL_SUFFIX})

#add_custom_command(TARGET ${TARGET} POST_BUILD
#        COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${TARGET}> ${TARGET_DS}
#        COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=${TARGET_DS} $<TARGET_FILE:${TARGET}>
#)

install (TARGETS ${TARGET} ARCHIVE)
#install (FILES ${TARGET_DS} TYPE INFO)
