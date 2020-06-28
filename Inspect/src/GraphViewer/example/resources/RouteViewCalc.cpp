//
// Created by flavio on 26/06/20.
//

#include "RouteViewCalc.h"



string verifyTagColor(Tag type){
    if(type == AutPub){
        return RED;

    }
    else if(type == AgEcono){
        return BLUE;

    }
    else{
        return LIGHT_GRAY;

    }

}

int verifyTagSize(Tag type){
    if(type == AutPub){
        return 30;
    }
    else if(type == AgEcono){
        return 20;
    }
    else{
        return 3;
    }

}

void drawGraphFromFile(std::string name, unsigned int port){
    std::ifstream nodes("../resources/graphs/"+name+"/nodes.txt");
    std::ifstream edges("../resources/graphs/"+name+"/edges.txt");
    std::ifstream window("../resources/graphs/"+name+"/window.txt");
    std::string line, background_path;
    std::istringstream iss;
    unsigned int n_nodes, n_edges, height, width, v1, v2, type, scale, dynamic, thickness, size, dashed, curved;
    float x, y;
    char color[20], label[256], icon_path[256], flow[256], weight[256];

    window >> width >> height >> dynamic >> scale >> dashed >> curved >> background_path;
    GraphViewer *gv = new GraphViewer(width, height, dynamic, port);
    gv->setBackground(background_path);
    gv->createWindow(width, height);
    gv->defineEdgeDashed(dashed);
    gv->defineEdgeCurved(curved);

    // read num of nodes
    std::getline(nodes, line);
    iss.str(line);
    iss >> n_nodes;

    // draw nodes
    for(int i = 0; i < n_nodes;i++) {
        std::getline(nodes, line);
        sscanf( line.c_str(), "(%f, %f, %s , %s , %u, %s )", &x, &y, color, label, &size, icon_path);
        gv->addNode(i , x*scale, y*scale);
        gv->setVertexColor(i, color);
        if (label[0] != '-')
            gv->setVertexLabel(i, label);
        if (icon_path[0] != '-')
            gv->setVertexIcon(i, std::string(icon_path));
        gv->setVertexSize(i, size);
    }

    // read num of edges
    std::getline(edges, line);
    sscanf( line.c_str(), "%d", &n_edges);

    //draw edges
    for(int i = 0; i < n_edges ; i++) {
        std::getline(edges, line);
        sscanf( line.c_str(), "(%u, %u, %u, %s ,%u, %s , %s , %s )", &v1, &v2, &type, color, &thickness, label, flow, weight);
        (type)? gv->addEdge(i, v1, v2, EdgeType::DIRECTED): gv->addEdge(i, v1, v2, EdgeType::UNDIRECTED);
        gv->setEdgeColor(i, color);
        gv->setEdgeThickness(i, thickness);
        if (label[0] != '-')
            gv->setEdgeLabel(i, label);
        if (flow[0] != '%')
            gv->setEdgeFlow(i, atoi(flow));
        if (weight[0] != '%')
            gv->setEdgeWeight(i, atoi(weight));
    }

    gv->rearrange();
}


void CalculateDrawRoutes(GraphViewer &gv, Graph<int> &graph, AutoridadePublica &autPub,vector<AgenteEconomico *> &agEcono,AlgorithmMinDist algorithm,AlgorithmTmpViagInspec algorithmTmpViagInspec,RouteCalcRestriction restriction){
    vector<pair<vector<int>,pair<double,int >> > res;



    //Visitamos todos os agentes económicos sem ter em conta a atividade económica e especialidades das Brigadas
    if(restriction == NoRestriction) {
        for (int i = 1; i <= autPub.get_brigadas().size(); i++) {
            Brigada brg1 = *autPub.get_brigadas()[i];
            auto auxRote = getRotaBrigada(graph, autPub, algorithm, agEcono, algorithmTmpViagInspec, brg1);
            res.push_back(auxRote);

            //Imprimir identificação dos agentes económicos, brigada e tempo de trabalho acumulado da rota

            if (auxRote.first.size() != 0) {
                cout << "Agentes Económicos Inspecionados: ";
                for (auto v: auxRote.first)//imprimir id próprio de cada agente económico inspecionado por uma brigada
                    for(auto w: autPub.get_agentes())
                        if(w.second->get_idNo() == v)
                            cout << w.second->get_id() << " ";
                cout << "|TmpViagInspecBrig: " << auxRote.second.first << " |Brigada: " << auxRote.second.second
                     << endl;
            }
        }
    }
    else  {
        for (int i = 1; i <= autPub.get_brigadas().size(); i++) {
            Brigada brg1 = *autPub.get_brigadas()[i];
            vector<AgenteEconomico *> aux;
            //Filtrar agentes económicos
            for(auto AE: agEcono)
                if(AE->getAtividadeEconomica() == brg1.get_atividades_economicas() || brg1.get_atividades_economicas() == Todas)
                    aux.push_back(AE);
            auto auxRote = getRotaBrigada(graph, autPub, algorithm, aux, algorithmTmpViagInspec, brg1);
            res.push_back(auxRote);

            //Apagar agentes económicos que já foram distribuídos a uma brigada
            for(auto v = agEcono.begin(); v != agEcono.end(); v++ )
                if((*v)->getAtividadeEconomica() == brg1.get_atividades_economicas() || brg1.get_atividades_economicas() == Todas)
                    if(find(aux.begin(),aux.end(),(*v)) == aux.end()) {//AgEcono em vector agEconojá foi distribuido por uma brigada
                        agEcono.erase(v);
                        v--;
                    }
            //Imprimir identificação dos agentes económicos, brigada e tempo de trabalho acumulado da rota
            if (auxRote.first.size() != 0) {
                cout << "Agentes Económicos Inspecionados: ";
                for (auto v: auxRote.first)//imprimir id próprio de cada agente económico inspecionado por uma brigada
                    for(auto w: autPub.get_agentes())
                        if(w.second->get_idNo() == v)
                            cout << w.second->get_id() << " ";
                cout << "|TmpViagInspecBrig: " << auxRote.second.first << " |Brigada: " << auxRote.second.second
                     << endl;
            } else{//caso em que brigada não faz qualquer inspeção
                cout << "|TmpViagInspecBrig: " << auxRote.second.first << " |Brigada: " << auxRote.second.second
                     << endl;
            }

        }
    }





    vector<pair<vector<int>,pair<double,int>>> resRoute;

    for(int v = 0; v < res.size();  v++){

        //Para cada par com vector dos vertices/agEcono visitados , e par com TmpViagInspec da brigada e brigada referente a uma determinada rota obtida
        auto agEconoIdNoVector = res.at(v).first;
        vector<int> auxSave; // vector que será utilizado para obter rotas entre todos os agentes económicos

        if(algorithm == dijkstra) {
            //Caminhoda AuPtublica até ao primeiro agente económico
            graph.dijkstraShortestPath(autPub.getIdNo());

        }
        else if(algorithm == Bellman_Ford)
            graph.bellmanFordShortestPath(autPub.getIdNo());

        //Caminho compelto da AuPublica até ao primeiro agente económico


        if(agEconoIdNoVector.size() != 0) {
            if(algorithm == FloyWarshall){
                auxSave = graph.getfloydWarshallPath(autPub.getIdNo(),agEconoIdNoVector.at(0));

            }else {
                auxSave = graph.getPathTo(agEconoIdNoVector.at(0));
                //par a guardar referente a cada brigada e caminho completo
            }


            //Obter totalidade de  cada rota
            for (int i = 0; i < agEconoIdNoVector.size() - 1; i++) {

                if(algorithm == FloyWarshall){
                    //caminhos desde cada agEcono i para o i+1 referido no vector com os agEcomoVisitados FloydWarshall
                    auto pathVEc = graph.getfloydWarshallPath(agEconoIdNoVector.at(i),agEconoIdNoVector.at(i + 1));
                    pathVEc.erase(pathVEc.begin());//eliminar primeiro vértice, para evitar repetições entre viagens de cada agEcono para outro AgEcono

                    for (auto w: pathVEc)
                        auxSave.push_back(w);

                }else {

                    //caminhos desde cada agEcono i para o i+1 referido no vector com os agEcomoVisitados
                    graph.dijkstraShortestPath(agEconoIdNoVector.at(i));
                    auto pathVEc = graph.getPathTo(agEconoIdNoVector.at(i + 1));
                    pathVEc.erase(
                            pathVEc.begin());//eliminar primeiro vértice, para evitar repetições entre viagens de cada agEcono para outro AgEcono

                    for (auto w: pathVEc)
                        auxSave.push_back(w);
                }
            }
        }
        //Guradamos rota, brigada e tempo de trabalho utilizado nessa mesma rota
        pair<vector<int>,pair<double,int>> pairSave (auxSave,pair<double,int>(res.at(v).second.first,res.at(v).second.second));

        //vector com a informação de todas as rotas e respectivas brigadas
        resRoute.push_back(pairSave);
    }

    //Imprmir e vizualizar rotas de todas as brigadas
    for(auto brigFullRoutes: resRoute) {
        vector<int> resBrig = brigFullRoutes.first;
        cout << "|TmpViagInspecBrig: " << brigFullRoutes.second.first << " |Brigada: " << brigFullRoutes.second.second  << " |";
        cout << " |Nós visitados: ";
        if(resBrig.size() != 0)

            for (int v: resBrig)
                cout << v << " ";
        cout << endl;
    }


    cout << "Não fechar janela do graphView se quer continuar no programa: " << endl << endl;
    bool close = true;
   int option = 0;
   int optionVisual= 0;
   cout <<"Deseja visualizar de forma automática as rotas: 1 " << endl;
   cout << "Deseja controlar o aparecimento das rotas: 2" << endl;

   optionVisual = checkOption(1,2);
    while(close) {
        int counterNewEdges = graph.getNumberOfEdges() + 10; // + 10 para evitar sobreposição de arestas existentes ao desenhar rotas com arestas no grafo
        for (auto pairAux: resRoute) {
            vector<int> edgesRemove;
            for (int i = 1; i < pairAux.first.size(); i++) {
                if(counterNewEdges % 2 == 0) {
                    gv.addEdge(counterNewEdges, pairAux.first.at(i - 1), pairAux.first.at(i), EdgeType::DIRECTED);

                }
                else if(counterNewEdges % 5  == 0 && counterNewEdges % 2 != 0 ) {
                    gv.addEdge(counterNewEdges, pairAux.first.at(i - 1), pairAux.first.at(i), EdgeType::UNDIRECTED);
                    gv.setEdgeLabel(counterNewEdges, to_string(pairAux.second.second));
                }
                else{gv.addEdge(counterNewEdges, pairAux.first.at(i - 1), pairAux.first.at(i), EdgeType::UNDIRECTED);}

                gv.setEdgeColor(counterNewEdges,"RED");
                gv.setEdgeThickness(counterNewEdges,5);


                edgesRemove.push_back(counterNewEdges);
                counterNewEdges++;

            }
            gv.rearrange();
            if(optionVisual == 1)
                sleep(8);
            else{
                wait();
            }

            for (auto v: edgesRemove)//remove arestas criadas para de seguida vermos caminho percorrida pela próxima brigada
                gv.removeEdge(v);

            gv.rearrange();
            sleep(1);
        }

        cout <<"Pretende voltar ao menu principal ? (Sim: 1 ou Não: 2)" ;
        option = checkOption(1,2);
        if(option == 2) {
            cout << "Deseja visualizar de forma automática as rotas: 1 " << endl;
            cout << "Deseja controlar o aparecimento das rotas: 2" << endl;

            optionVisual = checkOption(1, 2);
            wait();
        }
        else {
            gv.closeWindow();
            return;
        }
    }

}



GraphViewer &drawGraph( Graph<int> &graph,AutoridadePublica &AtPub, string windowFich, unsigned int port,int typeEdge,bool otherLabel){


    std::ifstream window("../resources/graphs/"+windowFich+"/window.txt");
    std::string  background_path;

    int n_nodes, n_edges, height, width, v1, v2,  dynamic, thickness, size, dashed, curved;
    double x, y,scale;
    char label[256], icon_path[256], flow[256], weight[256];

    window >> width >> height >> dynamic >> scale >> dashed >> curved >> background_path;
    GraphViewer *gv = new GraphViewer(width, height, dynamic, port);
    if(background_path !="-")
        gv->setBackground(background_path);
    gv->createWindow(width, height);
    gv->defineEdgeDashed(dashed);
    gv->defineEdgeCurved(curved);

    // read num of nodes
    n_nodes = graph.getNumVertex();


    // draw nodes
    for(int i = 0; i < n_nodes;i++) {

        x = graph.getVertexSet().at(i)->getLocal().get_xMap();
        y = graph.getVertexSet().at(i)->getLocal().get_yMap();

        x = (x - graph.getMinXGraphView() )* (width - 500 )/ ((graph.getMaxXGraphView() - graph.getMinXGraphView()) + 50 );

        y = (y - graph.getMinYGraphView()) * (height -220) / ((graph.getMaxYGraphView() - graph.getMinYGraphView()) + 50);

        int idNo = graph.getVertexSet().at(i)->getInfo();
        gv->addNode(idNo , (x*scale),(y*scale));


        //damos cor ao vertice consoante o seu tipo


        gv->setVertexSize(idNo, verifyTagSize(graph.getVertexSet().at(i)->getTagType()));


        gv->setVertexColor(idNo, verifyTagColor(graph.getVertexSet().at(i)->getTagType()));



        if(graph.getVertexSet().at(i)->getTagType() == AutPub) {

            gv->setVertexLabel(idNo, "AP: " + to_string(idNo));
        }
        else if(graph.getVertexSet().at(i)->getTagType() == AgEcono) {
            for(auto w: AtPub.get_agentes())
                if(w.second->get_idNo() == idNo)
                    gv->setVertexLabel(idNo,to_string(w.second->get_id()));
        }
        else{
            if(otherLabel)
                gv->setVertexLabel(idNo,to_string(idNo));
        }

    }

    // read num of edges

    int counterEdges= 0;
    //draw edges
    for(int i = 0; i < n_nodes ; i++) {

        // sscanf( line.c_str(), "(%u, %u, %u, %s ,%u, %s , %s , %s )", &v1, &v2, &type, color, &thickness, label, flow, weight);
        int listEdgesN = graph.getVertexSet().at(i)->getEdges().size();
        for(int j = 0; j < listEdgesN; j++){
            int orig;
            int dest;

            //Obter ids de cada vértice a ser ligada o de origem e destino
            orig = graph.getVertexSet().at(i)->getInfo();
            dest = graph.getVertexSet().at(i)->getEdges().at(j).getDest()->getInfo();
            //Configuraçao,informação e definição da aresta entre dois pares de nós
            if(graph.getVertexSet().at(i)->getEdges().at(j).getDest() != NULL) {
                gv->addEdge(counterEdges, orig, dest, typeEdge);
                gv->setEdgeColor(counterEdges, "LIGHT_GRAY");

                gv->setEdgeThickness(counterEdges, 1);
                counterEdges++;
            }
        }


    }

    //rearranjar grafo com novo conteúdo
    gv->rearrange();

    return *gv;
}
