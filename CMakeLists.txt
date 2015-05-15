cmake_minimum_required( VERSION 2.8 )
project( CORE )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/module;${CMAKE_MODULE_PATH}")
set(CMAKE_BINAARY_DIR ${CMAKE_SOURE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories( include )
add_subdirectory( src )
