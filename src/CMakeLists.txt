
add_library(shashank_lib blank.cpp
    ../include/vector.hpp)

target_include_directories(shashank_lib PUBLIC ../include)

target_compile_features(shashank_lib PUBLIC cxx_std_11)
