
#include <iostream>
#include <vector>
#include <string>
#include "AutoridadePublica.h"

#include "menus.h"


void mainMenu(AutoridadePublica &autoridade) {

    while (true) {
        cout << "===================================================================================================================" << endl
             << "                       InspectIT: Rotas de Inspecao                                                                " << endl
             << "===================================================================================================================" << endl
             << "           AGENTES ECONOMICOS            |                 BRIGADAS                                                " << endl
             << "=========================================|=========================================================================" << endl
             << "Visualizar informacao dos agentes  [1]   |   Visualizar informacao das brigadas                                [5] " << endl
             << "Adicionar agente economico         [2]   |   Adicionar brigada                                                 [6] " << endl
             << "Inserir denuncia                   [3]   |   Remover brigada                                                   [7] " << endl
             << "Remover agente economico           [4]   |   Cálculo e Visualização de rota diaria  de uma brigada             [8] " << endl
             << "Exit                               [0]   |   Cálculo e Visualização de todas as rotas diárias das brigadas     [9] " << endl
             << "Exit                               [0]   |   Cálculo e Visualização de todas as rotas diárias das brigadas     [9] " << endl;



        int option;
        option = checkOption(0, 8);
        unsigned int input;
        double veloMedBrig = 0.0;
        if (option == 0)
        {
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
                option2 = checkOption(1,3);

                //caso em que escolho voltar atrás
                if(option2 == 0) {
                    return;
                }

                else {


                    cout << "Introduza velocidade média das brigadas: " << endl;

                    veloMedBrig = checkOption(0.0, 120);
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
                    cout << "Considerar tempo de inspeção de cada Agente Económico no cálculo das rotas? (yes: 1 or no: 2)"
                            << endl;
                    int option3 = 0;
                    option3 = checkOption(1, 2);

                    //Escolher algoritmos a utilizar
                    AlgorithmMinDist aux;
                    AlgorithmTmpViagInspec algoAux;
                    int option4 = 0;
                    cout << ""
                            "Algoritmos:" << endl
                         << "Dijkstra: 1" << endl
                         << "BellManFord: 2" << endl
                         << "Floyd-Warshall: 3" << endl;

                    option4 = checkOption(1, 3);
                    if (option4 == 1) {
                        aux = dijkstra;
                    } else if (option4 == 2)
                        aux = Bellman_Ford;
                    else
                        aux = FloyWarshall;

                    if (option3 == 1) {
                        algoAux = TmpViagInspecFull;
                    } else
                        algoAux = TmpViagDist;



                    calculateRoutes(gr,autoridade,aux,algoAux);
                    cout << "Voltar menu principal: 1";
                    option2 = checkOption(1,1);
                    if(option2 == 1)
                        return;

                }
        }
    }
}


template <class T>
void menuLoadMaps(Graph<T> &gr, int input, double velocidadeMediaBrigadas) {
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

        loadGraphNodesInfo(gr, "../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_nodes_xy.txt",
                           "../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_nodes_latlng.txt",
                           "../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_edges.txt",
                           velocidadeMediaBrigadas);


    }

    for(int v = 1; v <= gr.getVertexSet().size();  v++)
        gr.getVertexSet()[v -1]->setInfo(v);


}
template <class T>
void calculateRoutes(Graph<T> &gr,AutoridadePublica &AtPub,AlgorithmMinDist algorithm ,AlgorithmTmpViagInspec tmpViagInspec){
    vector<AgenteEconomico *> agEcono;

    for(auto AE: AtPub.get_agentes()) {
        agEcono.push_back(AE.second);
        agEcono.push_back(AE.second);
    }



    gr.findVertex(AtPub.getIdNo())->setTagType(AutPub);
    for(auto it : agEcono) {
        auto eV =  gr.findVertex(it->get_idNo());
        if (eV != NULL) {
            eV->setTagType(AgEcono);
        }
    }

    GraphViewer gv = drawGraph(gr,"Porto_Strong_Component",7778,EdgeType::UNDIRECTED, false);


    CalculateDrawRoutes(gv,gr,AtPub,agEcono,algorithm,tmpViagInspec,AllEconoAct);



}