file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scanner.hpp
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(BISON)
find_package(FLEX)
find_package(nlohmann_json 3.11.2 REQUIRED)

BISON_TARGET(MyParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(MyScanner lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser nlohmann_json::nlohmann_json)

add_library(block_parser
    ${BISON_MyParser_OUTPUTS}
    ${FLEX_MyScanner_OUTPUTS}
)

target_include_directories(block_parser PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
# Prevent unknowned issue about using legacy C++ in modern C++
target_compile_features(block_parser PUBLIC cxx_std_14)

target_link_libraries(block_parser ${FLEX_LIBRARIES} nlohmann_json::nlohmann_json)