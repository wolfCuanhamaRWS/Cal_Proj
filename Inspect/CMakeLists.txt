cmake_minimum_required(VERSION 3.16)
project(Inspect)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


include_directories(src)
add_executable(Inspect main.cpp Tests/tests.cpp src/Graph.h src/MutablePriorityQueue.h src/AgenteEconomico.h src/AgenteEconomico.cpp src/AutoridadePublica.h src/AutoridadePublica.cpp src/Brigada.h src/Brigada.cpp src/Data.h src/Data.cpp src/utils.h src/utils.cpp
            src/MapImport.h src/MapImport.cpp src/menus.h src/menus.cpp
        src/utils.h src/utils.cpp
        src/Local.cpp src/Local.h src/HeuristicsFindRoute.h)


target_link_libraries(Inspect gtest gtest_main)

