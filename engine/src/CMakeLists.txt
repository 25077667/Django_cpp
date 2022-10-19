set(HEADER_DIRS "${CMAKE_SOURCE_DIR}/include")

add_library(Django STATIC Django.cpp)
target_include_directories(Django PUBLIC ${HEADER_DIRS})

add_library(Module STATIC module.cpp)
target_include_directories(Module PUBLIC ${HEADER_DIRS})

target_link_libraries(Django PUBLIC Module)
