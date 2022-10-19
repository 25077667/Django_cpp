cmake_minimum_required(VERSION 3.12)

project(Django CXX)
set(CMAKE_CXX_STANDARD 20)

set (MY_CXX_FLAGS "-pthread")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_CXX_FLAGS}")

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

add_executable(engine main.cpp)
add_subdirectory(src)
target_link_libraries(engine PUBLIC Django)