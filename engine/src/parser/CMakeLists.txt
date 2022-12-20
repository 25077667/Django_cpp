set(HEADER_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../../include")

find_package(Boost 1.80.0 REQUIRED COMPONENTS regex)

add_library(parser STATIC parser.cpp ${HEADER_DIRS})
target_include_directories(parser PUBLIC ${HEADER_DIRS})

add_library(parser_variable STATIC variable.cpp)
target_include_directories(parser_variable PUBLIC ${HEADER_DIRS})

add_library(extends STATIC extends.cpp)
target_include_directories(extends PUBLIC ${HEADER_DIRS})

target_link_libraries(parser PUBLIC parser_variable extends Boost::regex)