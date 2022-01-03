
add_executable(testvector vector_tests.cpp)

target_link_libraries(testvector PRIVATE shashank_lib)

add_test(NAME testvector
         COMMAND testvector)