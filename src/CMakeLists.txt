set(SOURCES library.cpp)

add_library(librg_cpp STATIC ${SOURCES})

target_link_libraries(librg_cpp PRIVATE librg_static)
