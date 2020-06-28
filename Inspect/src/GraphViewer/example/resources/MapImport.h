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
#include "AutoridadePublica.h"



/**Função que importa latitude, longitude, coordenadas X , Y e arestas referentes aos nós de um mapa à escolha
 *Grafo passado por referência ou a informação perder-se apõs função ser executada!
 * @param nosXYFich
 * @param nosCoordGeoFich
 * @param arestasFich
 * @param velocMediaKH velocidade média escolhida que brigadas terão
 * @return grafo preenchido com todos os nós de um mapa escolhido
 */
void loadGraphNodesInfo(Graph<int> &grafo,string nosXYFich,string nosCoordGeoFich, string arestasFich,double velocMediaKH);

void controlCoordsGraphView(Graph<int> &graph,double, double y);

void checkEconoAtPubTags(Graph<int> &gr, AutoridadePublica &AtPub,vector<AgenteEconomico *> &agEcono);






#endif //INSPECT_IT_MAPIMPORT_H
