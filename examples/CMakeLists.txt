# Server
set(SERVER_SOURCES server.cpp)

add_executable(example_server ${SERVER_SOURCES})

target_link_libraries(example_server PRIVATE librg_cpp)

# Client
set(CLIENT_SOURCES client.cpp)

add_executable(example_client ${CLIENT_SOURCES})

target_link_libraries(example_client PRIVATE librg_cpp)
