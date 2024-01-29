cmake_minimum_required(VERSION 3.26)
project(Solution)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Solution
        collide.cpp
        game_object.h
        geo2d.cpp
        geo2d.h
        test_runner.h)
