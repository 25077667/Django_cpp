set(HEADER_DIRS "${CMAKE_SOURCE_DIR}/include")

find_package(nlohmann_json 3.11.2 REQUIRED)

add_library(Django STATIC Django.cpp)
target_include_directories(Django PUBLIC ${HEADER_DIRS})

add_library(Module STATIC module.cpp)
target_include_directories(Module PUBLIC ${HEADER_DIRS})

add_subdirectory(parser)
add_subdirectory(render)

target_link_libraries(Django PUBLIC Module nlohmann_json::nlohmann_json parser render)
