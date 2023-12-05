cmake_minimum_required(VERSION 3.27)

set (TARGET stepper)
set (SOURCES main.cpp)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} class)

set (TARGET_DS ${CMAKE_BINARY_DIR}/${TARGET}.${DEBUG_SYMBOL_SUFFIX})

add_custom_command(TARGET ${TARGET} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${TARGET}> ${TARGET_DS}
        COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${TARGET}>
        COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=${TARGET_DS} $<TARGET_FILE:${TARGET}>
)


install (TARGETS ${TARGET} RUNTIME)
install (FILES ${TARGET_DS} TYPE INFO)
