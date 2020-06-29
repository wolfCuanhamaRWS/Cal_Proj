#include <string>

#include <cstdio>
#include "graphviewer.h"
#include <csignal>
#include "AgenteEconomico.h"
#include "AutoridadePublica.h"
#include <vector>
#include "Graph.h"
#include "MapImport.h"
#include "HeuristicsFindRoute.h"
#include "menus.h"
#include "Conectividade.h"



int main() {
    /*Graph<int> gr;

    AutoridadePublica AtPub ("../resources/agentes.txt","../resources/brigadas.txt");
    loadGraphNodesInfo(gr, "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_full_nodes_xy.txt",
                       "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_full_nodes_latlng.txt",
                       "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_full_edges.txt",
                       40);

    drawGraph(gr,AtPub,"Porto_Strong_Component",7778,EdgeType::UNDIRECTED, false);

    LargeSSCFilterGraph(gr);


    drawGraph(gr,AtPub,"Porto_Strong_Component",7778,EdgeType::UNDIRECTED, false);

    Graph<int> gr2;
    //mainMenu(AtPub);
    loadGraphNodesInfo(gr2, "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_xy.txt",
                       "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_latlng.txt",
                       "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_edges.txt",
                      40);

    drawGraph(gr2,AtPub,"Porto_Strong_Component",7778,EdgeType::UNDIRECTED, false);*/

    AutoridadePublica AtPub ("../resources/agentes.txt","../resources/brigadas.txt");
    mainMenu(AtPub);
    AtPub.destrutor();
    return 0;
}

