cmake_minimum_required(VERSION 3.0.0)
project(c4 VERSION 0.1.0)

add_library(libc4 INTERFACE)
target_include_directories(libc4 INTERFACE inc)
target_compile_features(libc4 INTERFACE cxx_std_20)

add_executable(c4 main.cpp)
target_compile_features(c4 PRIVATE cxx_std_20)
target_link_libraries(c4 PRIVATE libc4)
