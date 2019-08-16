# Data tests
add_executable(librg_datatest data.cpp)
target_link_libraries(librg_datatest PRIVATE librg_cpp)
add_test(NAME data COMMAND librg_datatest)
