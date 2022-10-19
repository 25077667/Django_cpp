set(HEADER_DIRS "${CMAKE_SOURCE_DIR}/include")


add_library(parser STATIC parser.cpp ${HEADER_DIRS})
target_include_directories(parser PUBLIC ${HEADER_DIRS})

add_library(variable STATIC variable.cpp)
target_include_directories(variable PUBLIC ${HEADER_DIRS})

target_link_libraries(parser PUBLIC variable)