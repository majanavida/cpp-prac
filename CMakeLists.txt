cmake_minimum_required(VERSION 3.16)

project(prac1_dynamic_array LANGUAGES CXX)

add_executable(dynamic_array_demo
    src/main.cpp
    src/DynamicArray.cpp
)

target_include_directories(dynamic_array_demo PRIVATE include)
target_compile_features(dynamic_array_demo PRIVATE cxx_std_17)
