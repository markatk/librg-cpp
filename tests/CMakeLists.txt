# Data tests
add_executable(librg_cpp_datatest data.cpp)
target_link_libraries(librg_cpp_datatest PRIVATE librg_cpp)
add_test(NAME data COMMAND librg_cpp_datatest)

# Context tests
add_executable(librg_cpp_contexttest context.cpp)
target_link_libraries(librg_cpp_contexttest PRIVATE librg_cpp)
add_test(NAME context COMMAND librg_cpp_contexttest)

# Entity tests
add_executable(librg_cpp_entitytest entity.cpp)
target_link_libraries(librg_cpp_entitytest PRIVATE librg_cpp)
add_test(NAME entity COMMAND librg_cpp_entitytest)
