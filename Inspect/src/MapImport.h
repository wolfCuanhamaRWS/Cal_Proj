//
// Created by flavio on 06/06/20.
//

#ifndef INSPECT_IT_MAPIMPORT_H
#define INSPECT_IT_MAPIMPORT_H

#include "Graph.h"
#include "Graph.h"
#include <string>
#include <fstream>
#include <sstream>



/**Função que importa latitude, longitude, coordenadas X , Y e arestas referentes aos nós de um mapa à escolha
 *
 * @param nosXYFich
 * @param nosCoordGeoFich
 * @param arestasFich
 * @param velocMediaKH velocidade média escolhida que brigadas terão
 * @return grafo preenchido com todos os nós de um mapa escolhido
 */
Graph<Local> loadGraphNodesInfo(string nosXYFich,string nosCoordGeoFich, string arestasFich,double velocMediaKH);









#endif //INSPECT_IT_MAPIMPORT_H
