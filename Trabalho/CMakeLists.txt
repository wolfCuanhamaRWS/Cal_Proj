cmake_minimum_required(VERSION 3.15)
project(CAL)

set(CMAKE_CXX_STANDARD 14)

add_executable(CAL  main.cpp
                    menus.cpp menus.h
                    utils.cpp utils.h
                    graph.cpp graph.h
                    node.cpp node.h
                    MutablePriorityQueue.h)