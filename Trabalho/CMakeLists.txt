cmake_minimum_required(VERSION 3.15)
project(CAL)

set(CMAKE_CXX_STANDARD 14)

add_executable(CAL  main.cpp
        Source/menus.cpp Header/menus.h
        Source/utils.cpp Header/utils.h
        Source/graph.cpp Header/graph.h
        Source/node.cpp Header/node.h
        Header/MutablePriorityQueue.h)