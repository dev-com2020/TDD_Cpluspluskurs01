cmake_minimum_required(VERSION 3.26)
project(01)

set(CMAKE_CXX_STANDARD 17)

add_executable(01 tests/main.cpp
        Test.h
        tests/Creation.cpp
        tests/Confirm.cpp)
