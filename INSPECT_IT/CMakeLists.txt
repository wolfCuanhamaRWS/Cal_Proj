cmake_minimum_required(VERSION 3.15)
project(INSPECT_IT)

set(CMAKE_CXX_STANDARD 14)
# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
#link_libraries(ws2_32 wsock32)

include_directories(src)




#file(src *.cpp)
add_executable( INSPECT_IT main.cpp src/GraphViewer/connection.cpp src/GraphViewer/connection.h
        src/GraphViewer/edgetype.h src/GraphViewer/graphviewer.cpp src/GraphViewer/graphviewer.h  src/Model/Data.h src/Model/Data.cpp src/Model/AgenteEconomico.h src/Model/AgenteEconomico.cpp src/Model/Brigada.h src/Model/AutoridadePublica.h
        src/Utils/MapImport.h src/View/menus.cpp src/Model/Local.h src/Utils/utils.h src/Utils/utils.cpp src/View/menus.cpp src/Model/Brigada.cpp src/Model/Local.cpp src/Utils/MapImport.cpp src/Model/AgenteEconomico.cpp
        src/Utils/Erro.h src/Model/Graph.h src/Model/MutablePriorityQueue.h src/View/menus.cpp src/View/menus.h src/Model/AutoridadePublica.cpp
        src/Algorithms/HeuristicsFindRoute.cpp src/Algorithms/HeuristicsFindRoute.h src/Controller/RouteViewCalc.cpp src/Controller/RouteViewCalc.h src/Algorithms/Conectividade.cpp src/Algorithms/Conectividade.h src/Algorithms/AlgorithmPerformanceTest.cpp src/Algorithms/AlgorithmPerformanceTest.h)
