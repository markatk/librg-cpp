set(SOURCES librg-cpp.cpp context.cpp)

configure_file(${CMAKE_SOURCE_DIR}/include/librg-cpp/version.h.in version.h)

add_library(librg_cpp STATIC ${SOURCES})

target_include_directories(librg_cpp PRIVATE ${CMAKE_SOURCE_DIR}/include/librg-cpp)
target_include_directories(librg_cpp PRIVATE ${CMAKE_BINARY_DIR})

target_include_directories(librg_cpp INTERFACE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(librg_cpp PUBLIC librg_static)
