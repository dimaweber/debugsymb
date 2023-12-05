cmake_minimum_required(VERSION 3.16)
project(debugsymb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set (DEBUG_SYMBOL_SUFFIX ds)

include(GNUInstallDirs)
set(CMAKE_INSTALL_BINDIR out/bin)
set(CMAKE_INSTALL_LIBDIR out/lib)
set(CMAKE_INSTALL_INFODIR out)

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(src/inc)

set(SYMBOLS_BINARY_PATH ${CMAKE_BINARY_DIR}/symbols)
file(MAKE_DIRECTORY ${SYMBOLS_BINARY_PATH})
function (create_ds target)
    set (TARGET_DS ${SYMBOLS_BINARY_PATH}/${target}.${DEBUG_SYMBOL_SUFFIX})

    add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${target}> ${TARGET_DS}
            COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${target}>
            COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=${TARGET_DS} $<TARGET_FILE:${target}>
    )
endfunction()
install(DIRECTORY ${SYMBOLS_BINARY_PATH} TYPE INFO)

add_subdirectory(src/app)
add_subdirectory(src/lib)
