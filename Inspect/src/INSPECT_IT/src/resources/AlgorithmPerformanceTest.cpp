


#include "AlgorithmPerformanceTest.h"

enum TestType{Dijkstra, BellmanFord, FloydWarshall, Kosaraju, Routes};

template<class T>
void DijkstraTest(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){
     //semente aleatória para ser usada nos testes de performance
    srand(time(NULL));
    //Carregar mapa

    double result = 0.0;
    double minTmp = INF;
    double maxTmp = 0.0;
    double media = 0.0;

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich, arestasFich,  velocMediaKH);

    for(int v = 1; v <= graph.getVertexSet().size();  v++)
        graph.getVertexSet()[v -1]->setInfo(v);


    for(int n = 0; n< numbInter; n++){

        int source = 0;


        source = rand() % (graph.getVertexSet().size() );


        auto init = high_resolution_clock:: now();

        graph.dijkstraShortestPath(source);
        auto end =  high_resolution_clock::now();


        auto tmpCounter = chrono :: duration_cast<microseconds>(end - init);

        result += tmpCounter.count();
        minTmp = min(minTmp,(double) tmpCounter.count());
        maxTmp = max(maxTmp,(double) tmpCounter.count());

    }

    media = result /(double) numbInter;
    cout << nomeCidade << endl;
    cout << "Algoritmo Dijkstra" << endl;
    cout << "Valores de tempos em microssegundos" << endl;
    cout << "Numéro de iterações: " << numbInter << endl;
    cout << "Tempo máximo: " << maxTmp << endl;
    cout << "Tempo mínimo: " << minTmp << endl;
    cout << "Tempo médio: " << media << endl;
    cout << "Numéro de nós: " << graph.getVertexSet().size() <<endl;
    cout << "Número de arestas: " << graph.getNumberOfEdges() << endl;
    cout << "Total de tempo: " << result << endl;



}

void globalPerformanceTEst(){

    double velocMediaKH;
    //Testar algoritmos para as três cidades
    Graph<int> gr1;
    Graph<int> gr2;
    Graph<int> gr3;



    int option = 0;

    cout << "Qual a velocidade média pretende utilizar? " << endl;
    velocMediaKH = checkOption(0.0, 200.0);

    cout << "No que pretende testar a Performance?" << endl;
    cout << "Dijkstra: 1" << endl;
    cout << "BellmanFord: 2" << endl;
    cout <<"FloydWarshall: 3" << endl;
    cout << "Cálculo de rotas com uma ou mais brigadas: 4"<< endl;
    cout << "Kosaraju (Conetividade): 5" << endl;
    option = checkOption(1,5);


    cout << "Número de iterações para os testes: " << endl;
    int iter = checkOption(1, 10000000);

    switch (option) {
        case 1:
            cout << endl;
            DijkstraTest(gr1, "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_xy.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_latlng.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_edges.txt", velocMediaKH,iter,"Porto");
            cout << endl;
            DijkstraTest(gr2, "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_xy.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_latlng.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_edges.txt", velocMediaKH,iter,"Espinho");
            cout << endl;
            DijkstraTest(gr3, "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_nodes_xy.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_nodes_latlng.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_edges.txt", velocMediaKH,iter,"Penafiel");
            cout << endl;

            break;
        case 2:

            cout << endl;
            BellManFordTest(gr1, "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_xy.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_latlng.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_edges.txt", velocMediaKH,iter,"Porto");
            cout << endl;
            BellManFordTest(gr2, "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_xy.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_latlng.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_edges.txt", velocMediaKH,iter,"Espinho");
            cout << endl;
            BellManFordTest(gr3, "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_nodes_xy.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_nodes_latlng.txt",
                         "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_edges.txt", velocMediaKH,iter,"Penafiel");
            cout << endl;
            break;

        case 3:


            cout << endl;
            FloydWarshallTestAllGraph(gr1, "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_xy.txt",
                            "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_latlng.txt",
                            "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_edges.txt", velocMediaKH,iter,"Porto");
            cout << endl;
            FloydWarshallTestAllGraph(gr2, "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_xy.txt",
                            "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_latlng.txt",
                            "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_edges.txt", velocMediaKH,iter,"Espinho");
            cout << endl;
            FloydWarshallTestAllGraph(gr3, "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_nodes_xy.txt",
                            "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_nodes_latlng.txt",
                            "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_edges.txt", velocMediaKH,iter,"Penafiel");
            cout << endl;
            break;

        case 4:

            cout << endl;
            CalRoutesTest(gr1, "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_xy.txt",
                                      "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_latlng.txt",
                                      "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_edges.txt", velocMediaKH,iter,"Porto");
            cout << endl;
            CalRoutesTest(gr2, "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_xy.txt",
                                      "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_nodes_latlng.txt",
                                      "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_edges.txt", velocMediaKH,iter,"Espinho");
            cout << endl;
            CalRoutesTest(gr3, "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_nodes_xy.txt",
                                      "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_nodes_latlng.txt",
                                      "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_strong_edges.txt", velocMediaKH,iter,"Penafiel");
            cout << endl;
            break;

        case 5:

            cout << endl;
            KosarajuConectivityTEst(gr1, "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_full_nodes_xy.txt",
                          "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_full_nodes_latlng.txt",
                          "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_full_edges.txt", velocMediaKH,iter,"Porto");
            cout << endl;
            KosarajuConectivityTEst(gr2, "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_full_nodes_xy.txt",
                          "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_full_nodes_latlng.txt",
                          "../resources/graphs/MAPS_INSPECT_IT/EspinhoTeste/espinho_strong_edges.txt", velocMediaKH,iter,"Espinho");
            cout << endl;
            KosarajuConectivityTEst(gr3, "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_full_nodes_xy.txt",
                          "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_full_nodes_latlng.txt",
                          "../resources/graphs/MAPS_INSPECT_IT/PenafielTeste/penafiel_full_edges.txt", velocMediaKH,iter,"Penafiel");
            cout << endl;
            break;

        default:
            break;
            }

   //Testes para as rotas, deve usar todos os algoritmos, e restrições possíveis


}
template<class T>
void BellManFordTest(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){
     //semente aleatória para ser usada nos testes de performance
    srand(time(nullptr));
    //Carregar mapa

    double result = 0.0;
    double minTmp = INF;
    double maxTmp = 0.0;
    double media = 0.0;

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich, arestasFich,  velocMediaKH);

    for(int v = 1; v <= graph.getVertexSet().size();  v++)
        graph.getVertexSet()[v -1]->setInfo(v);



    for(int n = 0; n< numbInter; n++){

        int source = 0;


        source = rand() % graph.getVertexSet().size(); //Obter valor aleatório


        auto init = high_resolution_clock:: now();

        graph.bellmanFordShortestPath(source);
        auto end =  high_resolution_clock::now();


        auto tmpCounter = chrono :: duration_cast<microseconds>(end - init);

        result += tmpCounter.count();
        minTmp = min(minTmp,(double) tmpCounter.count());
        maxTmp = max(maxTmp,(double) tmpCounter.count());

    }
    media = result /(double) numbInter;
    cout << nomeCidade << endl;
    cout << "Algoritmo BellManFord" << endl;
    cout << "Valores de tempos em microssegundos" << endl;
    cout << "Numéro de iterações: " << numbInter << endl;
    cout << "Tempo máximo: " << maxTmp << endl;
    cout << "Tempo mínimo: " << minTmp << endl;
    cout << "Tempo médio: " << media << endl;
    cout << "Numéro de nós: " << graph.getVertexSet().size() <<endl;
    cout << "Número de arestas: " << graph.getNumberOfEdges() << endl;
    cout << "Total de tempo: " << result << endl;
    cout << "Valores de tempos em microssegundos" << endl;



}
template<class T>
void FloydWarshallTestAllGraph(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){
     //semente aleatória para ser usada nos testes de performance
    srand(time(NULL));
    //Carregar mapa

    double result = 0.0;
    double minTmp = INF;
    double maxTmp = 0.0;
    double media = 0.0;
    double tmpAux = 0.0;

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich, arestasFich,  velocMediaKH);
    for(int v = 1; v <= graph.getVertexSet().size();  v++)
        graph.getVertexSet()[v -1]->setInfo(v);



    cout << "Qual a margem de erro que quer utilizar para o algoritmo FloydWarshall: (Exemplo: 0.001 (horas) ) " << endl;

    double errorEPS = checkOption(0, 5);

    bool controlFirstTIme = true;
    for(int n = 0; n< numbInter; n++){
        Graph<int> aux;
        if(controlFirstTIme) {
            controlFirstTIme = false; // só excuta uma vez neste grafo
            graph.floydWarshallShortestPath(1, errorEPS);
            auto init = high_resolution_clock:: now();

            aux.floydWarshallShortestPath(1, errorEPS);
            auto end =  high_resolution_clock::now();
            auto tmpCounter = chrono :: duration_cast<microseconds>(end - init);

            result += tmpCounter.count();
            minTmp = min(minTmp,(double) tmpCounter.count());
            maxTmp = max(maxTmp,(double) tmpCounter.count());
        }
        else {
            // resto das vezes
            loadGraphNodesInfo(aux, nosXYFich, nosCoordGeoFich, arestasFich, velocMediaKH);

            auto init = high_resolution_clock:: now();

            aux.floydWarshallShortestPath(1, errorEPS);
            auto end =  high_resolution_clock::now();


            auto tmpCounter = chrono :: duration_cast<microseconds>(end - init);

            result += tmpCounter.count();
            minTmp = min(minTmp,(double) tmpCounter.count());
            maxTmp = max(maxTmp,(double) tmpCounter.count());


        }


    }

    //Tempos após algoritmos floydWarshall ter terminado:
    double result2 = 0.0;
    double minTmp2 = INF;
    double maxTmp2 = 0.0;
    double media2 = 0.0;


    for(int n = 0; n< numbInter; n++){

        int source = 0;


        source = rand() % graph.getVertexSet().size(); //Obter valor aleatório

        int dest = rand() % graph.getVertexSet().size();

        auto init = high_resolution_clock:: now();

        double gettmpViag = graph.getDistMin()[source][dest];
        auto end =  high_resolution_clock::now();


        auto tmpCounter = chrono :: duration_cast<microseconds>(end - init);

        result2 += tmpCounter.count();
        minTmp2 = min(minTmp,(double) tmpCounter.count());
        maxTmp2 = max(maxTmp,(double) tmpCounter.count());

    }

    media = result /(double) numbInter;
    media2 = result2/ (double) numbInter;

    cout << nomeCidade << endl;
    cout << "Algoritmo FloydWarshall" << endl;
    cout << "Valores de tempos em microssegundos" << endl;
    cout << "Numéro de iterações: " << numbInter << endl;
    cout << "Tempo máximo: " << maxTmp << endl;
    cout << "Tempo mínimo: " << minTmp << endl;
    cout << "Tempo médio:" << media << endl;
    cout << "Numéro de nós: " << graph.getVertexSet().size()<< endl;
    cout << "Número de arestas: " << graph.getNumberOfEdges() << endl;
    cout << "Tempo total :" << result<< endl;
    cout << "Tempos após algoritmo ter terminado : " << endl << endl;
    cout << "Tempo máximo: " << maxTmp2 << endl;
    cout << "Tempo mínimo: " << minTmp2 << endl;
    cout << "Tempo médio: " << media2 << endl;
    cout << "Tempo total :" << result2 << endl;
    cout << "Valores de tempos em microssegundos" << endl;

    }
template<class T>
void KosarajuConectivityTEst(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){

    //Carregar mapa

    double result = 0.0;
    double minTmp = INF;
    double maxTmp = 0.0;
    double media = 0.0;

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich, arestasFich,  velocMediaKH);

    for(int n = 0; n< numbInter; n++){

        auto init = high_resolution_clock:: now();

        graph.KosarajuMainAlgo();
        auto end =  high_resolution_clock::now();


        auto tmpCounter = chrono :: duration_cast<microseconds>(end - init);

        result += tmpCounter.count();
        minTmp = min(minTmp,(double) tmpCounter.count());
        maxTmp = max(maxTmp,(double) tmpCounter.count());

    }
    media = result /(double) numbInter;
    cout << nomeCidade << endl;
    cout << "Algoritmo de Conetividade Kosaraju" << endl;
    cout << "Valores de tempos em microssegundos" << endl;
    cout << "Numéro de iterações: " << numbInter << endl;
    cout << "Tempo máximo: " << maxTmp << endl;
    cout << "Tempo mínimo: " << minTmp << endl;
    cout << "Tempo médio: " << media << endl;
    cout << "Numéro de nós: " << graph.getVertexSet().size() << endl;
    cout << "Número de arestas: " << graph.getNumberOfEdges() << endl;
    cout << "Tempo total: : " << result << endl;


}

template<class T>
void CalRoutesTest(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){
     /*//semente aleatória para ser usada nos testes de performance
    srand(time(NULL));
    //Obter para todas as heurísticas possíveis

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich,arestasFich,velocMediaKH,numbInter,nomeCidade);
    for(int v = 1; v <= graph.getVertexSet().size();  v++)
        graph.getVertexSet()[v -1]->setInfo(v);

    media = media /(double) numbInter;
*/


}
