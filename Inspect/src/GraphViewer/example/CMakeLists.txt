cmake_minimum_required(VERSION 3.15)
project(example)

set(CMAKE_CXX_STANDARD 11)
# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
#link_libraries(ws2_32 wsock32)

include_directories(src)
include_directories(lib)
include_directories(resources)
include_directories(example)


#file(resources *.cpp)
add_executable( example main.cpp  lib/connection.cpp lib/graphviewer.cpp resources/Data.h resources/Data.cpp resources/AgenteEconomico.h resources/AgenteEconomico.cpp resources/Brigada.h resources/AutoridadePublica.h
        resources/MapImport.h resources/menus.cpp resources/Local.h resources/utils.h resources/utils.cpp resources/menus.cpp resources/Brigada.cpp resources/Local.cpp resources/MapImport.cpp resources/AgenteEconomico.cpp
        resources/Erro.h resources/Graph.h resources/MutablePriorityQueue.h resources/menus.cpp resources/menus.h resources/AutoridadePublica.cpp
        resources/HeuristicsFindRoute.cpp resources/HeuristicsFindRoute.h resources/RouteViewCalc.cpp resources/RouteViewCalc.h)
