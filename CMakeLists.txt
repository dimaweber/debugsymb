cmake_minimum_required(VERSION 3.16)
project(debugsymb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)
set(CMAKE_INSTALL_BINDIR out/bin)
set(CMAKE_INSTALL_LIBDIR out/lib)
set(CMAKE_INSTALL_INFODIR out)

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(src/inc)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(DebugSymbols)

add_subdirectory(src/app)
add_subdirectory(src/lib)
