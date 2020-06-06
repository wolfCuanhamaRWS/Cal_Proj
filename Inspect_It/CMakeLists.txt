cmake_minimum_required(VERSION 3.10)
project(Inspect_It)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(Inspect_It main.cpp Tests/tests.cpp src/Graph.h src/MutablePriorityQueue.h src/AgenteEconomico.h src/AgenteEconomico.cpp src/AutoridadePublica.h src/AutoridadePublica.cpp src/Brigada.h src/Brigada.cpp src/Data.h src/Data.cpp src/utils.h src/utils.cpp
        src/GraphViewer/cpp/connection.cpp src/GraphViewer/cpp/connection.h
        src/GraphViewer/cpp/edgetype.h src/GraphViewer/cpp/graphviewer.cpp src/GraphViewer/cpp/graphviewer.h )

target_link_libraries(Inspect_It gtest gtest_main)
