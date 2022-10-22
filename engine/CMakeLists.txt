cmake_minimum_required(VERSION 3.12)

project(Django CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set (COMMON_WARNNING_FLAG "-Wall -Wextra")
set (MY_CXX_FLAGS "")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_CXX_FLAGS} ${COMMON_WARNNING_FLAG}")

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0 -ggdb -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Ofast -s -flto")

add_executable(engine main.cpp)
add_subdirectory(src)
target_link_libraries(engine PUBLIC Django)