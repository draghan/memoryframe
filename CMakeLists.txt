cmake_minimum_required(VERSION 3.14)
project(MemoryFrame)

set(CMAKE_CXX_STANDARD 17)

add_executable(MemoryFrame Frame.cpp Frame.hpp frame_tests.cpp tests_main.cpp FrameEntity.hpp FrameEntity.cpp)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wduplicated-cond -Wformat=2 -Weffc++ -Wdouble-promotion -Wuseless-cast -Wnull-dereference -Wlogical-op -Wduplicated-branches  -Wmisleading-indentation -Wsign-conversion -Wpedantic -Wconversion -Woverloaded-virtual -Wunused -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align")