
/*

#include "AlgorithmPerformanceTest.h"

enum TestType{Dijkstra, BellmanFord, FloydWarshall, Kosaraju, Routes};

template<class T>
void DijkstraTest(Graph<T> graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){

    //Carregar mapa

    double result = 0.0;
    double minTmp = INF;
    double maxTmp = 0.0;
    double media = 0.0;

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich, arestasFich,  velocMediaKH);

    for(int n = 0; n< numbInter; n++){

        int source = 0;


        source = rand() % graph.getVertexSet().size();


        auto init = high_resolution_clock:: now();

        graph.dijkstraShortestPath(source);
        auto end =  high_resolution_clock::now();


        auto tmpCounter = chrono :: duration_cast<microseconds>(init - end);

        result += tmpCounter.count();
        minTmp = min(minTmp,(double) tmpCounter.count());
        maxTmp = max(maxTmp,(double) tmpCounter.count());

    }
    cout << nomeCidade << endl;
    cout << "Algoritmo Dijkstra" << endl;
    cout << "Numéro de iterações: " << numbInter << endl;
    cout << "Tempo máximo: " << maxTmp << endl;
    cout << "Tempo mínimo: " << minTmp << endl;
    cout << "Tempo médio:" << media << endl;
    cout << "Numéro de nós: " << graph.getVertexSet().size();
    cout << "Número de arestas: " << graph.getNumberOfEdges();
    cout << "Total de tempo: " << result << endl;


}

void globalPerformanceTEst(){
    int source;
    int dest;
    double velocMediaKH;
    //Testar algoritmos para as três cidades
    Graph<int> gr1;
    Graph<int> gr2;
    Graph<int> gr3;
    graph<int>

    /


    cout << "Qual a velocidade média pretende utilizar? " << endl;
    velocMediaKH = checkOption(0.0, 200.0);


    cout << "Quais nós pretende testar?" << endl;

    cout << "Nó de origem: " ;
    source = checkOption(1, graph.getVertexSet().size());

    cout << "Nó de destino: "

    dest = checkOption(1, )





   //Testes para as rotas, deve usar todos os algoritmos, e restrições possíveis


}
template<class T>
void BellManFordTest(Graph<T> graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){

    //Carregar mapa

    double result = 0.0;
    double minTmp = INF;
    double maxTmp = 0.0;
    double media = 0.0;

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich, arestasFich,  velocMediaKH);

    for(int n = 0; n< numbInter; n++){

        int source = 0;


        source = rand() % graph.getVertexSet().size(); //Obter valor aleatório


        auto init = high_resolution_clock:: now();

        graph.bellmanFordShortestPath(source);
        auto end =  high_resolution_clock::now();


        auto tmpCounter = chrono :: duration_cast<microseconds>(init - end);

        result += tmpCounter.count();
        minTmp = min(minTmp,(double) tmpCounter.count());
        maxTmp = max(maxTmp,(double) tmpCounter.count());

    }

    cout << nomeCidade << endl;
    cout << "Algoritmo BellManFord" << endl;
    cout << "Numéro de iterações: " << numbInter << endl;
    cout << "Tempo máximo: " << maxTmp << endl;
    cout << "Tempo mínimo: " << minTmp << endl;
    cout << "Tempo médio:" << media << endl;
    cout << "Numéro de nós: " << graph.getVertexSet().size();
    cout << "Número de arestas: " << graph.getNumberOfEdges();
    cout << "Tempo total: : " << result << endl;



}
template<class T>
void FloydWarshallTestAllGraph(Graph<T> graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){

    //Carregar mapa

    double result = 0.0;
    double minTmp = INF;
    double maxTmp = 0.0;
    double media = 0.0;
    double tmpAux = 0.0;

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich, arestasFich,  velocMediaKH);
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
            auto tmpCounter = chrono :: duration_cast<microseconds>(init - end);

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


            auto tmpCounter = chrono :: duration_cast<microseconds>(init - end);

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

        double gettmpViag = graph.getDistMin[source][dest];
        auto end =  high_resolution_clock::now();


        auto tmpCounter = chrono :: duration_cast<microseconds>(init - end);

        result2 += tmpCounter.count();
        minTmp2 = min(minTmp,(double) tmpCounter.count());
        maxTmp2 = max(maxTmp,(double) tmpCounter.count());

    }



    cout << nomeCidade << endl;
    cout << "Algoritmo FloydWarshall" << endl;
    cout << "Numéro de iterações: " << numbInter << endl;
    cout << "Tempo máximo: " << maxTmp << endl;
    cout << "Tempo mínimo: " << minTmp << endl;
    cout << "Tempo médio:" << media << endl;
    cout << "Numéro de nós: " << graph.getVertexSet().size();
    cout << "Número de arestas: " << graph.getNumberOfEdges();
    cout << "Tempo total :" << result;
    cout << "Tempos após algoritmo ter terminado: " << endl;
    cout << "Tempo máximo: " << maxTmp2 << endl;
    cout << "Tempo mínimo: " << minTmp2 << endl;
    cout << "Tempo médio:" << media2 << endl;
    cout << "Tempo total :" << result2;

    }
template<class T>
void KosarajuConectivityTEst(Graph<T> graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade){

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


        auto tmpCounter = chrono :: duration_cast<microseconds>(init - end);

        result += tmpCounter.count();
        minTmp = min(minTmp,(double) tmpCounter.count());
        maxTmp = max(maxTmp,(double) tmpCounter.count());

    }

    cout << nomeCidade << endl;
    cout << "Algoritmo de Conetividade Kosaraju" << endl;
    cout << "Numéro de iterações: " << numbInter << endl;
    cout << "Tempo máximo: " << maxTmp << endl;
    cout << "Tempo mínimo: " << minTmp << endl;
    cout << "Tempo médio:" << media << endl;
    cout << "Numéro de nós: " << graph.getVertexSet().size();
    cout << "Número de arestas: " << graph.getNumberOfEdges();
    cout << "Tempo total: : " << result << endl;


}

template<class T>
void CalRoutesTest(Graph<T> graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade,unsigned int numBrigadas){

    //Obter para todas as heurísticas possíveis

    loadGraphNodesInfo(graph,nosXYFich,nosCoordGeoFich,arestasFich,velocMediaKH,numbInter,nomeCidade);





}*/
