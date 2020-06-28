
#include <iostream>
#include <vector>
#include "AutoridadePublica.h"
#include "menus.h"


void mainMenu(AutoridadePublica &autoridade) {
    Graph<int> graphFloydWarshall; // grafo global
    bool counterFloydWarshallCalc = false;
    int saveoptionAux = 0;
    while (true) {
        cout
                << "==================================================================================================================="
                << endl
                << "                       InspectIT: Rotas de Inspecao                                                                "
                << endl
                << "==================================================================================================================="
                << endl
                << "           AGENTES ECONOMICOS            |                 BRIGADAS                                                "
                << endl
                << "=========================================|========================================================================="
                << endl
                << "Visualizar informacao dos agentes  [1]   |   Visualizar informacao das brigadas                                [5] "
                << endl
                << "Adicionar agente economico         [2]   |   Adicionar brigada                                                 [6] "
                << endl
                << "Inserir denuncia                   [3]   |   Remover brigada                                                   [7] "
                << endl
                << "Remover agente economico           [4]   |   Cálculo e Visualização das rotas das Brigadas                     [8] "
                << endl
                << "Exit                               [0]   |   Conectividade                                                     [9] "
                << endl
                << "                                             Performance de Algoritmos                                         [10]"
                << endl;


        int option;
        option = checkOption(0, 9);
        unsigned int input;
        double veloMedBrig = 0.0;

        if (option == 0) {
            autoridade.destrutor();
            break;
        }
        switch (option) {

            case 1: //Visualizar agentes económicos
                cout << endl << "Lista de todos os agentes economicos:" << endl;
                autoridade.imprimirAgentesEconomicos();
                wait();
                break;

            case 2: //Adicionar agente económico
                autoridade.adicionarAgenteEconomico();
                wait();
                break;

            case 3: //Inserir denuncia
            {
                cout << "Escreva a o id do agente economico que deseja prestar uma queixa" << endl;
                cin >> input;
                autoridade.inserirDenuncia(input);
                wait();
                break;
            }
            case 4: //Remover agente economico
            {
                cout << "Escreva o id do agente que deseja remover [EXIT 0]" << endl;
                cin >> input;
                if (input == 0) { return; }
                autoridade.removerAgente(input);
                wait();
                break;
            }

            case 5: //Visualizar brigadas
                cout << endl << "Lista de todos as brigadas:" << endl;
                autoridade.imprimirBrigadas();
                wait();
                break;

            case 6: //Adicionar brigada
                autoridade.adicionarBrigada();
                wait();
                break;

            case 7://Remover brigada
                cout << "Escreva o id da brigada que deseja remover[exit 0]:" << endl;
                cin >> input;
                if (input == 0) { return; }
                autoridade.removerBrigada(input);
                wait();
                break;

            case 8: //Visualizar rota diária
                int option2;

                cout << "Porto: 1" << endl
                     << "Espinho: 2" << endl
                     << "Penafiel: 3" << endl
                     << "Exit: 0" << endl;
                option2 = checkOption(1, 3);

                //caso em que escolho voltar atrás
                if (option2 == 0) {
                    return;
                } else {


                    cout << "Introduza velocidade média das brigadas: " << endl;

                    veloMedBrig = checkOption(0.0, 120.0);
                    Graph<int> gr;
                    menuLoadMaps(gr, option2, veloMedBrig);



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
                    cout << "Considerar tempo de inspeção de cada Agente Económico no cálculo das rotas? (Sim: 1 or Não: 2)"<< endl;

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


                    //Filtrar qual configuração tendo em conta tmpViagem e tmpInspeção pretendo utilizar
                    if (option3 == 1) {
                        algoAux = TmpViagInspecFull;
                    } else
                        algoAux = TmpViag;

                    cout << "Pretende que seja utilizado um critèrio de urgència de Inspeção  no cálculo das rotas? (Sim: 1 or Não: 2) " << endl;
                    int urgencyOption = 0;
                    urgencyOption = checkOption(1, 2);

                    //Filtrar quais critérios utilizar no calculo de rotas
                    if (option3 == 1 && urgencyOption == 1) {
                        algoAuxUrgency = TmpViagInspectFullUrgency;
                    } else if( option3 == 2 && algoAuxUrgency == 1)
                            algoAuxUrgency = TmpViagUrgency;


                    //Controlo de uso de outro mapa diferente com algoritmo floydWarshall
                    if(saveoptionAux != 0 && saveoptionAux != option2 && aux == FloyWarshall){
                        counterFloydWarshallCalc = false;
                        graphFloydWarshall.eraseGraph();

                    }

                    // Caso em que se utiliza floyWarshall, onde o grafo ficará com as distancias mínimas calculadas para calculo de rotas posteriores
                    double errorEPS = 0.0;
                    if(aux == FloyWarshall && !counterFloydWarshallCalc){
                        menuLoadMaps(graphFloydWarshall,option2,veloMedBrig);
                        cout << "Qual a margem de erro que quer utilizar para o algoritmo FloydWarshall: (Exemplo: 0.001) " << endl;
                        errorEPS = checkOption(0, 1);
                        counterFloydWarshallCalc = true;

                        saveoptionAux = option2;
                        graphFloydWarshall.floydWarshallShortestPath(1, errorEPS);

                        //Casos considerando urgència
                        if (urgencyOption == 1) {
                            calculateRoutes(graphFloydWarshall, autoridade, aux, algoAuxUrgency,AllEconoAct);
                        }
                        else{
                            //Casos sem considerar urgẽncia
                            calculateRoutes(graphFloydWarshall, autoridade, aux, algoAux,AllEconoAct);
                        }



                    }
                    //Apenas temos de calcular rotas, visto que estamos a usar o mesmmo mapa para o qual já se calculou todas as distancias entre cada par de veŕtices
                    else if(aux == FloyWarshall && counterFloydWarshallCalc){


                        if ( urgencyOption == 1) {
                            calculateRoutes(graphFloydWarshall, autoridade, aux, algoAuxUrgency,AllEconoAct);
                        } else
                            {
                            //Casos considerando urgència
                            calculateRoutes(graphFloydWarshall, autoridade, aux, algoAux,AllEconoAct);
                            }




                    }
                    //Caso de uso de outros algoritmos
                    else {

                        if (option3 == 1 && urgencyOption == 1) {
                            calculateRoutes(gr, autoridade, aux, algoAuxUrgency,AllEconoAct);
                        } else if( option3 == 2 && algoAuxUrgency == 1)
                            calculateRoutes(gr, autoridade, aux, algoAuxUrgency,AllEconoAct);
                        else{
                            calculateRoutes(gr, autoridade, aux, algoAux,AllEconoAct);
                        }
                    }


                    wait();


                }
                break;

            case 9:



                cout << "Porto: 1" << endl
                     << "Espinho: 2" << endl
                     << "Penafiel: 3" << endl
                     << "Exit: 0" << endl;
                int option4 ;
                option4 = checkOption(0, 3);

                //caso em que escolho voltar atrás
                if (option4 == 0) {
                    return;
                } else {


                    cout << "Introduza velocidade média das brigadas: " << endl;

                    veloMedBrig = checkOption(0.0, 120.0);


                    cout
                            << "Será mostrado o mapa completo da cidade selecionada e de seguida serão calculadas todas as componentes fortemente conexas."
                            << endl;
                    cout
                            << "Será escolhida para representar o mapa da cidade pretendida a componente fortemente conexa com maior número de nós."
                            << endl;


                    Graph<int> gr1;
                    Graph<int> gr2;
                    Graph<int> gr3;
                    if (option4 == 1) {
                        loadGraphNodesInfo(gr1, "../resources/graphs/PortoTeste/porto_full_nodes_xy.txt",
                                           "../resources/graphs/PortoTeste/porto_full_nodes_latlng.txt",
                                           "../resources/graphs/PortoTeste/porto_full_edges.txt", veloMedBrig);

                        //escolher se queremos direção das arestas no mapa
                        cout << "Pretende ver a direção das arestas ? (Sim: 1 Não: 0) " << endl;
                        int option5 = 0;
                        option5 = checkOption(0, 1);


                        //Mapa inicial



                        GraphViewer gv1 = drawGraph(gr1, autoridade, "Porto_Strong_Component", 7778,option5, false);





                        //Achar todas as componentes fortemente conexas
                        getGraphFiltred(gr1);


                        //Escolher localização da autoridade pública
                        getIdNoAtPub(autoridade,gr1);



                        //Mapa já com a maior compoente fortemente conexa do mapa inicial

                        vector<AgenteEconomico *> agEcono;
                        checkEconoAtPubTags(gr1,autoridade ,agEcono);

                        GraphViewer gv2 = drawGraph(gr1, autoridade, "Porto_Strong_Component", 7778,option5, false);

                        cout << "Não fechar janelas do graphView se quer continuar no programa: " << endl;
                        if(wait()){
                            gv1.closeWindow();
                            gv2.closeWindow();
                        }

                        break;


                    } else if (option4 == 2) {
                        loadGraphNodesInfo(gr2, "../resources/graphs/PortoTeste/EspinhoTeste/espinho_full_nodes_xy.txt",
                                           "../resources/graphs/PortoTeste/EspinhoTeste/espinho_full_nodes_latlng.txt",
                                           "../resources/graphs/PortoTeste/EspinhoTeste/espinho_full_edges.txt",
                                           veloMedBrig);




                        //escolher se queremos direção das arestas no mapa
                        cout << "Pretende ver a direção das arestas ? (Sim: 1 Não: 0) " << endl;
                        cout << "Para mais visiblidade escolha não!" << endl;
                        int option5 = 0;
                        option5 = checkOption(0, 1);

                        //Mapa inicial

                        GraphViewer gv1 =   drawGraph(gr2, autoridade, "Porto_Strong_Component", 7778, option5, false);


                        //Achar todas as componentes fortemente conexas

                        getGraphFiltred(gr2);




                        //Escolher localização da autoridade pública
                        getIdNoAtPub(autoridade,gr2);


                        //Mapa já com a maior compoente fortemente conexa do mapa inicial
                        vector<AgenteEconomico *> agEcono;
                        checkEconoAtPubTags(gr2, autoridade, agEcono);



                        GraphViewer gv2 =   drawGraph(gr2, autoridade, "Porto_Strong_Component", 7778, option5, false);

                        cout << "Não fechar janelas do graphView se quer continuar no programa: " << endl;
                        if(wait()){
                            gv1.closeWindow();
                            gv2.closeWindow();
                        }

                        break;

                    }
                    else{

                        loadGraphNodesInfo(gr3, "../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_nodes_xy.txt",
                                           "../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_nodes_latlng.txt",
                                           "../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_edges.txt",
                                           veloMedBrig);


                        //escolher se queremos direção das arestas no mapa
                        cout << "Pretende ver a direção das arestas ? (Sim: 1 Não: 0) " << endl;
                        cout << "Para mais visiblidade escolha não!" << endl;
                        int option5 = 0;
                        option5 = checkOption(0, 1);

                        //Mapa inicial

                        GraphViewer gv1 =   drawGraph(gr3, autoridade, "Porto_Strong_Component", 7778, option5, false);


                        //Achar todas as componentes fortemente conexas

                        getGraphFiltred(gr3);




                        //Escolher localização da autoridade pública
                        getIdNoAtPub(autoridade,gr3);


                        //Mapa já com a maior compoente fortemente conexa do mapa inicial
                        vector<AgenteEconomico *> agEcono;
                        checkEconoAtPubTags(gr3, autoridade, agEcono);



                        GraphViewer gv2 =   drawGraph(gr3, autoridade, "Porto_Strong_Component", 7778, option5, false);

                        cout << "Não fechar janelas do graphView se quer continuar no programa: " << endl;
                        if(wait()){
                            gv1.closeWindow();
                            gv2.closeWindow();
                        }

                        break;


                    }



                }

            default:
                return;

        }
    }
}

void menuLoadMaps(Graph<int> &gr, int input, double velocidadeMediaBrigadas) {
    AutoridadePublica AtPub("../resources/agentes.txt", "../resources/brigadas.txt");


    if (input == 1) {
        loadGraphNodesInfo(gr, "../resources/graphs/PortoTeste/porto_strong_nodes_xy.txt",
                           "../resources/graphs/PortoTeste/porto_strong_nodes_latlng.txt",
                           "../resources/graphs/PortoTeste/porto_strong_edges.txt", velocidadeMediaBrigadas);


    } else if (input == 2) {
        loadGraphNodesInfo(gr, "../resources/graphs/PortoTeste/EspinhoTeste/espinho_strong_nodes_xy.txt",
                           "../resources/graphs/PortoTeste/EspinhoTeste/espinho_strong_nodes_latlng.txt",
                           "../resources/graphs/PortoTeste/EspinhoTeste/espinho_strong_edges.txt",
                           velocidadeMediaBrigadas);

    } else {

        loadGraphNodesInfo(gr, "../resources/graphs/PortoTeste/PenafielTeste/penafiel_strong_nodes_xy.txt",
                           "../resources/graphs/PortoTeste/PenafielTeste/penafiel_strong_nodes_latlng.txt",
                           "../resources/graphs/PortoTeste/PenafielTeste/penafiel_strong_edges.txt",
                           velocidadeMediaBrigadas);


    }

    for(int v = 1; v <= gr.getVertexSet().size();  v++)
        gr.getVertexSet()[v -1]->setInfo(v);


}


void calculateRoutes(Graph<int> &gr,AutoridadePublica &AtPub,AlgorithmMinDist algorithm ,AlgorithmTmpViagInspec tmpViagInspec,RouteCalcRestriction restriction){
    vector<AgenteEconomico *> agEcono;
    restriction = AllEconoAct;
    //Meter tags de forma  a AE e ATPub  sejam reconhecidas
    checkEconoAtPubTags(gr,AtPub,agEcono);

    GraphViewer gv = drawGraph(gr,AtPub,"Porto_Strong_Component",7778,EdgeType::UNDIRECTED, false);


    CalculateDrawRoutes(gv,gr,AtPub,agEcono,algorithm,tmpViagInspec,restriction);



}


void getGraphFiltred(Graph<int> &gr){
    //Achar todas as componentes fortemente conexas
    vector<vector<int>> res;
    res = gr.KosarajuMainAlgo();
    cout << "Todas as Componentes Fortemente Conexas do grafo pretendido: " << endl;
    printAllSccKosaraju(res);

    //Obter grafo com componente a maior componente fortemente conexa
    vector<int> aux = getMaxSizeKosarajuStrongCC(res);
    printMaxSizeSccKosoraju(aux);
    FastSSCKosorajuFilter(aux, gr);


}

void getIdNoAtPub(AutoridadePublica &autoridade, Graph<int> &gr){
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

}