set(HEADER_DIRS "${CMAKE_SOURCE_DIR}/include")

find_package(Boost 1.80.0 REQUIRED COMPONENTS regex)

add_library(render STATIC render.cpp ${HEADER_DIRS})
target_include_directories(render PUBLIC ${HEADER_DIRS})

add_library(render_variable STATIC variable.cpp ${HEADER_DIRS})
target_include_directories(render_variable PUBLIC ${HEADER_DIRS})

add_library(render_filter STATIC filter.cpp ${HEADER_DIRS})
target_include_directories(render_filter PUBLIC ${HEADER_DIRS})

add_library(render_custom_filter STATIC custom_filter.cpp ${HEADER_DIRS})
target_include_directories(render_custom_filter PUBLIC ${HEADER_DIRS})

add_library(render_tags STATIC tags.cpp ${HEADER_DIRS})
target_include_directories(render_tags PUBLIC ${HEADER_DIRS})

target_link_libraries(render PUBLIC Boost::regex render_variable render_filter render_custom_filter render_tags)
