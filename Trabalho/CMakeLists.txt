cmake_minimum_required(VERSION 3.15)
project(CAL)

set(CMAKE_CXX_STANDARD 14)

add_executable(CAL  main.cpp
        Source/menus.cpp Header/menus.h
        Source/utils.cpp Header/utils.h
        Source/graph.cpp Header/graph.h
        Source/node.cpp Header/node.h
        Header/MutablePriorityQueue.h
        Header/Erro.h
        Source/AgenteEconomico.cpp Header/AgenteEconomico.h
        Source/Autoridade_Publica.cpp Header/Autoridade_Publica.h
        Source/connection.cpp Header/connection.h
        Source/Denuncia.cpp Header/Denuncia.h
        Header/edgetype.h
        Source/Inspetor.cpp Header/Inspetor.h)