cmake_minimum_required(VERSION 3.15)
project(Cal_Proj_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(Trabalho/Header)
include_directories(Trabalho/Source)

add_executable(Cal_Proj_master
        Trabalho/Header/AgenteEconomico.h
        Trabalho/Header/Autoridade_Publica.h
        Trabalho/Header/Local.h
        #Trabalho/Header/connection.h
        Trabalho/Header/Denuncia.h
        #Trabalho/Header/edgetype.h
        Trabalho/Header/Erro.h
        #Trabalho/Header/graph.h
        #Trabalho/Header/graphviewer.h
        Trabalho/Header/Brigada.h
        Trabalho/Header/menus.h
        #Trabalho/Header/MutablePriorityQueue.h
        #Trabalho/Header/node.h
        Trabalho/Header/utils.h
        Trabalho/Header/FileUtils.h
        Trabalho/Source/Local.cpp
        Trabalho/Source/AgenteEconomico.cpp
        Trabalho/Source/Autoridade_Publica.cpp
        #Trabalho/Source/connection.cpp
        Trabalho/Source/Denuncia.cpp
        #Trabalho/Source/graph.cpp
        #Trabalho/Source/graphviewer.cpp
        Trabalho/Source/Brigada.cpp
        Trabalho/Source/menus.cpp
        #Trabalho/Source/node.cpp
        Trabalho/Source/utils.cpp
        Trabalho/main.cpp
        Trabalho/TextFiles
        Trabalho/Source/Data.cpp
        Trabalho/Header/Data.h
        Trabalho/Source/FileUtils.cpp )
