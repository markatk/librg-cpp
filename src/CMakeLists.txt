set(SOURCES librg-cpp.cpp context.cpp server.cpp client.cpp host.cpp data.cpp event.cpp entity.cpp message.cpp peer.cpp utility.cpp)

configure_file(${CMAKE_SOURCE_DIR}/include/librg-cpp/version.h.in version.h)

add_library(librg_cpp STATIC ${SOURCES})

if(USE_LINALG)
    target_include_directories(librg_cpp PUBLIC ${CMAKE_SOURCE_DIR}/thirdparty/linalg)
endif()

target_include_directories(librg_cpp PRIVATE ${CMAKE_SOURCE_DIR}/include/librg-cpp)
target_include_directories(librg_cpp PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(librg_cpp INTERFACE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(librg_cpp PUBLIC librg_static)
