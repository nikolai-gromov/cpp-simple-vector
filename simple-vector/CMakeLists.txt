cmake_minimum_required(VERSION 3.16)
project(simple_vector)


set(CMAKE_CXX_STANDARD 17)


include_directories(.)


add_executable(simple_vector
        array_ptr.h
        main.cpp
        simple_vector.h
        tests.h)