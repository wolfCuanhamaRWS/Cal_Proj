


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

    AutoridadePublica autoridade ("../resources/agentes.txt","../resources/brigadas.txt");

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
           /*FloydWarshallTestAllGraph(gr1, "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_xy.txt",
                            "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_nodes_latlng.txt",
                            "../resources/graphs/MAPS_INSPECT_IT/PortoTeste/porto_strong_edges.txt", velocMediaKH,iter,"Porto");
*/
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
            CalRoutesTest(gr1, 1, velocMediaKH,iter,"Porto",autoridade);
            cout << endl;
            CalRoutesTest(gr2, 2, velocMediaKH,iter,"Espinho",autoridade);
            cout << endl;
            CalRoutesTest(gr3, 3, velocMediaKH,iter,"Penafiel",autoridade);
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

            auto init = high_resolution_clock:: now();

            graph.floydWarshallShortestPath(1, errorEPS);
            auto end =  high_resolution_clock::now();
            auto tmpCounter = chrono :: duration_cast<microseconds>(end - init);

            result += tmpCounter.count();
            minTmp = min(minTmp,(double) tmpCounter.count());
            maxTmp = max(maxTmp,(double) tmpCounter.count());
        }
        else {
            // resto das vezes
            loadGraphNodesInfo(aux, nosXYFich, nosCoordGeoFich, arestasFich, velocMediaKH);
            for(int v = 1; v <= aux.getVertexSet().size();  v++)
                aux.getVertexSet()[v -1]->setInfo(v);
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


    for(int n = 0; n< numbInter + 100; n++){


        auto init = high_resolution_clock:: now();

        double gettmpViag = graph.getDistMin()[5][5];
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
    cout << "Tempo total :" << result<< endl<< endl;
    cout << "Tempos após algoritmo ter terminado : " << endl;
    cout << "Tempo máximo: " << maxTmp2 << endl;
    cout << "Tempo mínimo: " << minTmp2 << endl;
    cout << "Tempo médio: " << media2 << endl;
    cout << "Tempo total :" << result2 << endl;


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
void CalRoutesTest(Graph<T> &gr, int cityOption,double velocMediaKH,unsigned  int numbInter,string nomeCidade,AutoridadePublica &autoridade){




    menuLoadMaps(gr, cityOption, velocMediaKH);
    for(int v = 1; v <= gr.getVertexSet().size();  v++)
        gr.getVertexSet()[v -1]->setInfo(v);


    //Escolher localização da autoridade pública
    cout << "Introduza o valor para o nó que identifica a Autoridade Pública: " << endl;
    int idNo = 0;
    bool check = true;
    while (check) {
        idNo = checkOption(1, gr.getNumVertex());
        for (auto w: autoridade.get_agentes()) {
            if (!(w.second->get_idNo() == idNo)) {
                check = false;

            } else {
                check = true;
                break;
            }

        }

    }
    autoridade.setIdNo(idNo);
    cout << "Considerar tempo de inspeção de cada Agente Económico no cálculo das rotas? (Sim: 1 ou Não: 2)"<< endl;


    int option3 = 0;
    option3 = checkOption(1, 2);

    //Escolher algoritmos a utilizar
    AlgorithmMinDist aux;
    AlgorithmTmpViagInspec algoAux;
    AlgorithmTmpViagInspec algoAuxUrgency;
    int option7 = 0;
    cout << ""
            "Algoritmos:" << endl
         << "Dijkstra: 1" << endl
         << "BellManFord: 2" << endl
         << "Floyd-Warshall: 3" << endl;

    option7 = checkOption(1, 3);
    if (option7 == 1) {
        aux = dijkstra;
    } else if (option7 == 2)
        aux = Bellman_Ford;
    else
        aux = FloyWarshall;


    cout << "Pretende limitar inspeções a uma zona limitada escolhendo um local e raio envolvente? (Sim: 1 Não: 2)" << endl;


    //Tratar opção de usar coordenadas GPS ou não
    int GpsChoice = 0;
    GpsChoice = checkOption(1,2);
    int idNoOptoion = 0;
    double radius = 0.0;
    bool GpsCheck = false;
    pair<int, double>idNoRadius;

    if( GpsChoice == 1){
        cout << "Indique o IdNo da zona pretendida no mapa: " << endl;
        idNoRadius.first = checkOption(1, gr.getVertexSet().size());
        GpsCheck = true;
        cout << "Indique o valor do raio pretendido em Km: " << endl;
        idNoRadius.second = checkOption(0.0,1000.0);
    }



    //Filtrar qual configuração tendo em conta tmpViagem e tmpInspeção pretendo utilizar
    if (option3 == 1) {
        algoAux = TmpViagInspecFull;
    } else
        algoAux = TmpViag;

    cout << "Pretende que seja também utilizado um critèrio de urgència de Inspeção  no cálculo das rotas? (Sim: 1 ou Não: 2) " << endl;
    cout << "Pretende que a urgència de inspeção seja o principal factor: 3" << endl;

    int urgencyOption = 0;
    urgencyOption = checkOption(1, 3);

    //Filtrar quais critérios utilizar no calculo de rotas
    if (option3 == 1 && urgencyOption == 1) {
        algoAuxUrgency = TmpViagInspectFullUrgency;
    } else if( option3 == 2 && algoAuxUrgency == 1)
        algoAuxUrgency = TmpViagUrgency;
    else if(urgencyOption == 3){
        algoAux = justUrgency;


    }

    RouteCalcRestriction restriction;

    cout << "Pretende que especialidades das brigadas sejam respeitadas? (Sim: 1 Não: 2): " << endl;

    int optionRestrition = checkOption(1,2);

    if(optionRestrition == 1)
        restriction = AllEconoAct;
    else
        restriction = NoRestriction;

    double result = 0.0;
    double minTmp = INF;
    double maxTmp = 0.0;
    double media = 0.0;
    double tmpAux = 0.0;
    double errorEPS = 0.0;

    if(aux == FloyWarshall ){
        cout << "Qual a margem de erro que quer utilizar para o algoritmo FloydWarshall: (Exemplo: 0.001) " << endl;
        double errorEPS = checkOption(0, 5);

        gr.floydWarshallShortestPath(1, errorEPS);

    }
    vector<AgenteEconomico *> agEcono2;
    for(auto AE: autoridade.get_agentes())
        agEcono2.push_back(AE.second);


        // Caso em que se utiliza floyWarshall, onde o grafo ficará com as distancias mínimas calculadas para calculo de rotas posteriores

        if (aux == FloyWarshall) {


            //Apenas uma brigada que vão sendo escolhidas aleatoriamente escolhida

            //Casos considerando urgència
            if (urgencyOption == 1) {

                for (int n = 0; n < numbInter; n++) {
                    int brigIndex = rand() % 1 + autoridade.get_brigadas().size();
                    Brigada brg1 = *autoridade.get_brigadas()[brigIndex];


                    vector<AgenteEconomico *> auxAgEcono;
                    if(restriction == AllEconoAct) {
                        for (auto v: agEcono2)
                            if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                brg1.get_atividades_economicas() == Todas)
                                auxAgEcono.push_back(v);
                    }
                    else{//sem restrições de especialidade de inspeção
                        for (auto v: agEcono2)
                            auxAgEcono.push_back(v);


                    }

                    auto init = std::chrono::high_resolution_clock::now();
                    getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAuxUrgency, brg1, GpsCheck,
                                   idNoRadius);
                    auto end = std::chrono::high_resolution_clock::now();


                    auto tmpCounter = duration_cast<microseconds>(end - init);

                    result += tmpCounter.count();
                    minTmp = min(minTmp, (double) tmpCounter.count());
                    maxTmp = max(maxTmp, (double) tmpCounter.count());
                }

                cout << nomeCidade << endl;
                cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
                cout << "Valores de tempos em microssegundos" << endl;
                cout << "Escolha de Brigadas Aleatória" << endl;
                cout << "Numéro de iterações: " << numbInter << endl;
                cout << "Tempo máximo: " << maxTmp << endl;
                cout << "Tempo mínimo: " << minTmp << endl;
                cout << "Tempo médio: " << media << endl;
                cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
                cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
                cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
                cout << "Tempo total: : " << result << endl << endl << endl;


            } else {
                //Casos sem considerar urgẽncia
                for (int n = 0; n < numbInter; n++) {
                    int brigIndex = rand() % 1 + autoridade.get_brigadas().size();
                    Brigada brg1 = *autoridade.get_brigadas()[brigIndex];


                    vector<AgenteEconomico *> auxAgEcono;
                    if(restriction == AllEconoAct) {
                        for (auto v: agEcono2)
                            if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                brg1.get_atividades_economicas() == Todas)
                                auxAgEcono.push_back(v);
                    }
                    else{//sem restrições de especialidade de inspeção
                        for (auto v: agEcono2)
                            auxAgEcono.push_back(v);


                    }
                    auto init = std::chrono::high_resolution_clock::now();
                    getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAux, brg1, GpsCheck, idNoRadius);
                    auto end = std::chrono::high_resolution_clock::now();


                    auto tmpCounter = duration_cast<microseconds>(end - init);

                    result += tmpCounter.count();
                    minTmp = min(minTmp, (double) tmpCounter.count());
                    maxTmp = max(maxTmp, (double) tmpCounter.count());
                }

                media = result / (double) numbInter;
                cout << nomeCidade << endl;
                cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
                cout << "Valores de tempos em microssegundos" << endl;
                cout << "Escolha de Brigadas Aleatória" << endl;
                cout << "Numéro de iterações: " << numbInter << endl;
                cout << "Tempo máximo: " << maxTmp << endl;
                cout << "Tempo mínimo: " << minTmp << endl;
                cout << "Tempo médio: " << media << endl;
                cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
                cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
                cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
                cout << "Tempo total: : " << result << endl << endl << endl;


            }


        }

            //Caso de uso de outros algoritmos uma brigada de cada vez aleatórias
        else {

            if (option3 == 1 && urgencyOption == 1) {

                for (int n = 0; n < numbInter; n++) {
                    int brigIndex = rand() % 1 + autoridade.get_brigadas().size();
                    Brigada brg1 = *autoridade.get_brigadas()[brigIndex];


                    vector<AgenteEconomico *> auxAgEcono;
                    if(restriction == AllEconoAct) {
                        for (auto v: agEcono2)
                            if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                brg1.get_atividades_economicas() == Todas)
                                auxAgEcono.push_back(v);
                    }
                    else{//sem restrições de especialidade de inspeção
                        for (auto v: agEcono2)
                            auxAgEcono.push_back(v);


                    }

                    auto init = std::chrono::high_resolution_clock::now();
                    getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAuxUrgency, brg1, GpsCheck,
                                   idNoRadius);
                    auto end = std::chrono::high_resolution_clock::now();


                    auto tmpCounter = duration_cast<microseconds>(end - init);

                    result += tmpCounter.count();
                    minTmp = min(minTmp, (double) tmpCounter.count());
                    maxTmp = max(maxTmp, (double) tmpCounter.count());
                }

                media = result / (double) numbInter;
                cout << nomeCidade << endl;
                cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
                cout << "Valores de tempos em microssegundos" << endl;
                cout << "Escolha de Brigadas Aleatória" << endl;
                cout << "Numéro de iterações: " << numbInter << endl;
                cout << "Tempo máximo: " << maxTmp << endl;
                cout << "Tempo mínimo: " << minTmp << endl;
                cout << "Tempo médio: " << media << endl;
                cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
                cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
                cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
                cout << "Tempo total: : " << result << endl << endl << endl;


            } else if (option3 == 2 && algoAuxUrgency == 1) {


                for (int n = 0; n < numbInter; n++) {
                    int brigIndex = rand() % 1 + autoridade.get_brigadas().size();
                    Brigada brg1 = *autoridade.get_brigadas()[brigIndex];


                    vector<AgenteEconomico *> auxAgEcono;
                    if(restriction == AllEconoAct) {
                        for (auto v: agEcono2)
                            if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                brg1.get_atividades_economicas() == Todas)
                                auxAgEcono.push_back(v);
                    }
                    else{//sem restrições de especialidade de inspeção
                        for (auto v: agEcono2)
                            auxAgEcono.push_back(v);


                    }
                    auto init = std::chrono::high_resolution_clock::now();
                    getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAuxUrgency, brg1, GpsCheck,
                                   idNoRadius);
                    auto end = std::chrono::high_resolution_clock::now();


                    auto tmpCounter = chrono::duration_cast<microseconds>(end - init);

                    result += tmpCounter.count();
                    minTmp = min(minTmp, (double) tmpCounter.count());
                    maxTmp = max(maxTmp, (double) tmpCounter.count());
                }

                media = result / (double) numbInter;
                cout << nomeCidade << endl;
                cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
                cout << "Valores de tempos em microssegundos" << endl;
                cout << "Escolha de Brigadas Aleatórias" << endl;
                cout << "Numéro de iterações: " << numbInter << endl;
                cout << "Tempo máximo: " << maxTmp << endl;
                cout << "Tempo mínimo: " << minTmp << endl;
                cout << "Tempo médio: " << media << endl;
                cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
                cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
                cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
                cout << "Tempo total: : " << result << endl << endl << endl;

            } else {


                for (int n = 0; n < numbInter; n++) {
                    int brigIndex = rand() % 1 + autoridade.get_brigadas().size();
                    Brigada brg1 = *autoridade.get_brigadas()[brigIndex];


                    vector<AgenteEconomico *> auxAgEcono;
                    if(restriction == AllEconoAct) {
                        for (auto v: agEcono2)
                            if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                brg1.get_atividades_economicas() == Todas)
                                auxAgEcono.push_back(v);
                    }
                    else{//sem restrições de especialidade de inspeção
                        for (auto v: agEcono2)
                            auxAgEcono.push_back(v);


                    }



                    auto init = std::chrono::high_resolution_clock::now();
                    getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAux, brg1, GpsCheck, idNoRadius);
                    auto end = std::chrono::high_resolution_clock::now();


                    auto tmpCounter = duration_cast<microseconds>(end - init);

                    result += tmpCounter.count();
                    minTmp = min(minTmp, (double) tmpCounter.count());
                    maxTmp = max(maxTmp, (double) tmpCounter.count());
                }

                media = result / (double) numbInter;
                cout << nomeCidade << endl;
                cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
                cout << "Valores de tempos em microssegundos" << endl;
                cout << "Escolha de Brigadas Aleatórias" << endl;
                cout << "Numéro de iterações: " << numbInter << endl;
                cout << "Tempo máximo: " << maxTmp << endl;
                cout << "Tempo mínimo: " << minTmp << endl;
                cout << "Tempo médio: " << media << endl;
                cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
                cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
                cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
                cout << "Tempo total: : " << result << endl << endl << endl;


            }
        }


        //Caso de uso de todas as brigadas

        double result2 = 0.0;
        double minTmp2 = INF;
        double maxTmp2 = 0.0;
        double media2 = 0.0;
        double tmpAux2 = 0.0;


        vector<AgenteEconomico *> agEcono;
        for (auto AE: autoridade.get_agentes()) {
            agEcono.push_back(AE.second);

        }


        if (aux == FloyWarshall) {




            //Casos considerando urgència
            if (urgencyOption == 1) {

                for (int n = 0; n < numbInter; n++) {

                    for (int i = 1; i <= autoridade.get_brigadas().size(); i++) {
                        Brigada brg1 = *autoridade.get_brigadas()[i];
                        vector<AgenteEconomico *> auxAgEcono;
                        if(restriction == AllEconoAct) {
                            for (auto v: agEcono)
                                if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                    brg1.get_atividades_economicas() == Todas)
                                    auxAgEcono.push_back(v);
                        }
                        else{//sem restrições de especialidade de inspeção
                            for (auto v: agEcono)
                                auxAgEcono.push_back(v);


                        }


                        auto init =std::chrono::high_resolution_clock::now();
                        getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAuxUrgency, brg1, GpsCheck,
                                       idNoRadius);
                        auto end = std::chrono::high_resolution_clock::now();


                        auto tmpCounter = duration_cast<microseconds>(end - init);

                        result2 += tmpCounter.count();
                        minTmp2 = min(minTmp2, (double) tmpCounter.count());
                        maxTmp2 = max(maxTmp2, (double) tmpCounter.count());
                    }
                }
                media2 = result2 / (double) numbInter;

                cout << nomeCidade << endl;
                cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
                cout << "Valores de tempos em microssegundos" << endl;
                cout << "Utilização de todas as Brigadas" << endl;
                cout << "Numéro de iterações: " << numbInter << endl;
                cout << "Tempo máximo: " << maxTmp2 << endl;
                cout << "Tempo mínimo: " << minTmp2 << endl;
                cout << "Tempo médio: " << media2 << endl;
                cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
                cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
                cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
                cout << "Tempo total: : " << result << endl << endl << endl;


            } else {
                //Casos sem considerar urgẽncia
                for (int n = 0; n < numbInter; n++) {

                    for (int i = 1; i <= autoridade.get_brigadas().size(); i++) {
                        Brigada brg1 = *autoridade.get_brigadas()[i];
                        vector<AgenteEconomico *> auxAgEcono;
                        if(restriction == AllEconoAct) {
                            for (auto v: agEcono)
                                if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                    brg1.get_atividades_economicas() == Todas)
                                    auxAgEcono.push_back(v);
                        }
                        else{//sem restrições de especialidade de inspeção
                            for (auto v: agEcono)
                                auxAgEcono.push_back(v);


                        }


                        auto init = std::chrono::high_resolution_clock::now();
                        getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAux, brg1, GpsCheck, idNoRadius);
                        auto end = std::chrono::high_resolution_clock::now();


                        auto tmpCounter = duration_cast<microseconds>(end - init);

                        result2 += tmpCounter.count();
                        minTmp2 = min(minTmp2, (double) tmpCounter.count());
                        maxTmp2 = max(maxTmp2, (double) tmpCounter.count());
                    }
                }
                media2 = result2 / (double) numbInter;

                cout << nomeCidade << endl;
                cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
                cout << "Valores de tempos em microssegundos" << endl;
                cout << "Utilização de todas as Brigadas" << endl;
                cout << "Numéro de iterações: " << numbInter << endl;
                cout << "Tempo máximo: " << maxTmp2 << endl;
                cout << "Tempo mínimo: " << minTmp2 << endl;
                cout << "Tempo médio: " << media2 << endl;
                cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
                cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
                cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
                cout << "Tempo total: : " << result << endl << endl << endl;


            }


        }

        //Caso de uso de outros algoritmos uma brigada de cada vez aleatórias


        if (option3 == 1 && urgencyOption == 1) {
            for (int n = 0; n < numbInter; n++) {

                for (int i = 1; i <= autoridade.get_brigadas().size(); i++) {
                    Brigada brg1 = *autoridade.get_brigadas()[i];
                    vector<AgenteEconomico *> auxAgEcono;
                    if(restriction == AllEconoAct) {
                        for (auto v: agEcono)
                            if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                brg1.get_atividades_economicas() == Todas)
                                auxAgEcono.push_back(v);
                    }
                    else{//sem restrições de especialidade de inspeção
                        for (auto v: agEcono)
                            auxAgEcono.push_back(v);


                    }


                    auto init = std::chrono::high_resolution_clock::now();
                    getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAuxUrgency, brg1, GpsCheck,
                                   idNoRadius);
                    auto end = std::chrono::high_resolution_clock::now();


                    auto tmpCounter = duration_cast<microseconds>(end - init);

                    result2 += tmpCounter.count();
                    minTmp2 = min(minTmp2, (double) tmpCounter.count());
                    maxTmp2 = max(maxTmp2, (double) tmpCounter.count());
                }
            }
            media2 = result2 / (double) numbInter;

            cout << nomeCidade << endl;
            cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
            cout << "Valores de tempos em microssegundos" << endl;
            cout << "Utilização de todas as Brigadas" << endl;
            cout << "Numéro de iterações: " << numbInter << endl;
            cout << "Tempo máximo: " << maxTmp2 << endl;
            cout << "Tempo mínimo: " << minTmp2 << endl;
            cout << "Tempo médio: " << media2 << endl;
            cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
            cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
            cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
            cout << "Tempo total: : " << result << endl << endl << endl;


        } else if (option3 == 2 && algoAuxUrgency == 1) {


            for (int n = 0; n < numbInter; n++) {

                for (int i = 1; i <= autoridade.get_brigadas().size(); i++) {
                    Brigada brg1 = *autoridade.get_brigadas()[i];
                    vector<AgenteEconomico *> auxAgEcono;
                    if(restriction == AllEconoAct) {
                        for (auto v: agEcono)
                            if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                brg1.get_atividades_economicas() == Todas)
                                auxAgEcono.push_back(v);
                    }
                    else{//sem restrições de especialidade de inspeção
                        for (auto v: agEcono)
                            auxAgEcono.push_back(v);


                    }


                    auto init = std::chrono::high_resolution_clock::now();
                    getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAuxUrgency, brg1, GpsCheck,
                                   idNoRadius);
                    auto end = std::chrono::high_resolution_clock::now();


                    auto tmpCounter = duration_cast<microseconds>(end - init);

                    result2 += tmpCounter.count();
                    minTmp2 = min(minTmp2, (double) tmpCounter.count());
                    maxTmp2 = max(maxTmp2, (double) tmpCounter.count());
                }
            }
            media2 = result2 / (double) numbInter;

            cout << nomeCidade << endl;
            cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
            cout << "Valores de tempos em microssegundos" << endl;
            cout << "Utilização de todas as Brigadas" << endl;
            cout << "Numéro de iterações: " << numbInter << endl;
            cout << "Tempo máximo: " << maxTmp2 << endl;
            cout << "Tempo mínimo: " << minTmp2 << endl;
            cout << "Tempo médio: " << media2 << endl;
            cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
            cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
            cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
            cout << "Tempo total: : " << result << endl << endl << endl;

        } else {


            for (int n = 0; n < numbInter; n++) {

                for (int i = 1; i <= autoridade.get_brigadas().size(); i++) {
                    Brigada brg1 = *autoridade.get_brigadas()[i];
                    vector<AgenteEconomico *> auxAgEcono;
                    if(restriction == AllEconoAct) {
                        for (auto v: agEcono)
                            if (v->getAtividadeEconomica() == brg1.get_atividades_economicas() ||
                                brg1.get_atividades_economicas() == Todas)
                                auxAgEcono.push_back(v);
                    }
                    else{//sem restrições de especialidade de inspeção
                        for (auto v: agEcono)
                            auxAgEcono.push_back(v);


                    }
                    auto init = std::chrono::high_resolution_clock::now();
                    getRotaBrigada(gr, autoridade, aux, auxAgEcono, algoAux, brg1, GpsCheck, idNoRadius);
                    auto end = std::chrono::high_resolution_clock::now();


                    auto tmpCounter = duration_cast<microseconds>(end - init);

                    result2 += tmpCounter.count();
                    minTmp2 = min(minTmp2, (double) tmpCounter.count());
                    maxTmp2 = max(maxTmp2, (double) tmpCounter.count());
                }
            }
            media2 = result2 / (double) numbInter;

            cout << nomeCidade << endl;
            cout << "Algoritmo Cálculo de rotas (TSP)" << endl;
            cout << "Valores de tempos em microssegundos" << endl;
            cout << "Utilização de todas as Brigadas" << endl;
            cout << "Numéro de iterações: " << numbInter << endl;
            cout << "Tempo máximo: " << maxTmp2 << endl;
            cout << "Tempo mínimo: " << minTmp2 << endl;
            cout << "Tempo médio: " << media2 << endl;
            cout << "Numéro de nós: " << gr.getVertexSet().size() << endl;
            cout << "Número de arestas: " << gr.getNumberOfEdges() << endl;
            cout << "Número de agentes Económicos: " << autoridade.get_agentes().size() << endl;
            cout << "Tempo total: : " << result << endl << endl << endl;
        }


        wait();


    }