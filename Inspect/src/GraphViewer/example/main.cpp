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
string verifyTagColor(Tag type);
int verifyTagSize(Tag type);
void drawGraphFromFile(std::string name, unsigned int port);
void drawGraph(Graph<int> &graph,std::string windowFich, unsigned int port,int typeEdge,bool otherLabel);

string verifyTagColor(Tag type){
    if(type == AutPub){
        return RED;

    }
    else if(type == AgEcono){
        return BLUE;

    }
    else{
        return MAGENTA;

    }

}

int verifyTagSize(Tag type){
    if(type == AutPub){
        return 40;
    }
    else if(type == AgEcono){
        return 30;
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


void drawGraph(Graph<int> &graph, std::string windowFich , unsigned int port,int typeEdge,bool otherLabel){

    std::ifstream window("../resources/graphs/"+windowFich+"/window.txt");
    std::string  background_path;

    int n_nodes, n_edges, height, width, v1, v2,  scale, dynamic, thickness, size, dashed, curved;
    double x, y;
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

        x = (x - graph.getMinXGraphView() )* (width - 100) / (graph.getMaxXGraphView() - graph.getMinXGraphView()) + 25 ;

        y = (y - graph.getMinYGraphView()) * (height - 50) / (graph.getMaxYGraphView() - graph.getMinYGraphView()) + 25;

        int idNo = graph.getVertexSet().at(i)->getInfo();
        gv->addNode(idNo , (x*scale),(y*scale));


        //damos cor ao vertice consoante o seu tipo


        gv->setVertexSize(idNo, verifyTagSize(graph.getVertexSet().at(i)->getTagType()));


        gv->setVertexColor(idNo, verifyTagColor(graph.getVertexSet().at(i)->getTagType()));



        if(graph.getVertexSet().at(i)->getTagType() == AutPub) {

            gv->setVertexLabel(idNo, "AutPub");
        }
        else if(graph.getVertexSet().at(i)->getTagType() == AgEcono) {

            gv->setVertexLabel(idNo, "AgEcono");
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
            gv->addEdge(counterEdges,orig,dest,typeEdge);
            gv->setEdgeColor(counterEdges, "black");

            gv->setEdgeThickness(counterEdges, 1);
            counterEdges++;
        }


    }

    //rearranjar grafo com novo conteúdo
    gv->rearrange();

}




int main() {

   Graph<int> graph;
    //id, h_t, h_i, A_E




    /*AtPub.addBrigada(new Brigada (1,8,9,Obras)); //id, h_t, h_i, A_E
    AtPub.addAgenteEcon(&ag1);
    AtPub.addAgenteEcon(&ag2);
    AtPub.addAgenteEcon(&ag3);*/

    // graph,"../resources/graphs/PortoTeste/porto_strong_nodes_xy.txt", "../resources/graphs/PortoTeste/porto_strong_nodes_latlng.txt","../resources/graphs/PortoTeste/porto_strong_edges.txt",40.0 );
    // "../resources/graphs/GridGraphs/16x16/nodes.txt", "../resources/graphs/GridGraphs/16x16/nodes.txt","../resources/graphs/GridGraphs/16x16/edges.txt",40.0 );
    //"../resources/graphs/GridGraphs/16x16/nodes.txt", "../resources/graphs/GridGraphs/16x16/nodes.txt","../resources/graphs/GridGraphs/16x16/edges.txt",40.0 );
   // loadGraphNodesInfo(graph,"../resources/graphs/PortoTeste/porto_strong_nodes_xy.txt", "../resources/graphs/PortoTeste/porto_strong_nodes_latlng.txt","../resources/graphs/PortoTeste/porto_strong_edges.txt",40.0 );
    //Sinalizar AutPub


    //sinalizar AutPub








  //  signal(SIGINT, SIG_IGN);
   // drawGraphFromFile("random", 7778);
   // drawGraphFromFile("star", 7773);
    //drawGraphFromFile("rainbow", 7774);
   // drawGraphFromFile("Porto_Strong_Component", 7772);
   // drawGraph(graph,"Porto_Strong_Component",7777,EdgeType::DIRECTED, true);
   // getchar();


    /*vector<vector<int>> saveAllSCC = graph.KosarajuMainAlgo();
    for(auto vectorSCC: saveAllSCC) {
       // cout << "hey" << endl;
        for (auto v: vectorSCC)
            cout << v << " ";
        cout << endl;
    }*/









    /*
    Local l1(0,0,0,0);
    Local l2(2,4,0,0);
     gr.addCompleteVertex(new Vertex<int> (0,l1));
    gr.addCompleteVertex(new Vertex<int> (1,l2));
      Local l3(1,1,0,0);

      gr.addCompleteVertex(new Vertex<int> (2,l3));
      Local l4(3,6,0,0);

      gr.addCompleteVertex( new Vertex<int> (3,l4));
      Local l5(4,4,0,0);

      gr.addCompleteVertex(new Vertex<int> (4,l5));
     // gr.addEdge(0,1,2);
     gr.addEdge(1,2,5);
      gr.addEdge(2, 1,4);
      gr.addEdge(2,3,6);
      gr.addEdge(3, 4,10);
      gr.addEdge(4,3,3);
*/

   // drawGraph(g,"Porto_Strong_Component",7776,EdgeType::DIRECTED, true);
  /* for(int i = 0; i < graph.getVertexSet().size(); i++) {
       graph.getVertexSet()[i]->setInfo(i);

   }

    vector<vector<int>> saveAllSCC = graph.KosarajuMainAlgo();*/
    //Graph<int> gr = g.getInverseEdgesGraph();
    //vector<int> aux = gr.dfs()

    /*for(auto v: aux){
        cout << v << " ";

    }
    */
   /* for(auto vectorSCC: saveAllSCC) {
        // cout << "hey" << endl;
        cout << vectorSCC.size() << endl;
        for (auto v: vectorSCC)
            cout << v << " ";
        cout << endl;
    }*/

   // graph.dijkstraShortestPath(0);

   // vector<int> aux = graph.getPathTo(25850);

   // graph.dijkstraShortestPath(0);
   // vector<int> aux = graph.getPathTo(25850);
    /*for(auto v: aux)
        cout << v << " ";
    cout << endl<< "Penafiel_full_map:" << endl;*/
    //Obter maior SCC com nós das brigadas e AGE
   //for(int i = 0; i < saveAllCC.)
   // Graph<int> graph2;
  //  loadGraphNodesInfo(graph2,"../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_nodes_xy.txt", "../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_nodes_latlng.txt","../resources/graphs/PortoTeste/PenafielTeste/penafiel_full_edges.txt",40.0 );



   // for(int i = 1; i< gr.getNumVertex() + 1; i++)
     //   gr.getVertexSet()[i - 1]->setInfo(i);
   // drawGraph(gr,"Porto_Strong_Component",7776,EdgeType::DIRECTED, true);
    //gr.floydWarshallShortestPath3(1,0.0001);
   // vector<int> aux=  gr.getfloydWarshallPath3(137,10041);

    Graph< int> gr;
    signal(SIGINT, SIG_IGN);

    /*AgenteEconomico ag1(1,Obras,500,make_pair(9,19),new Denuncias(3,5),new Inspecoes(10,1),new Data(2019,12,11),5);
    AgenteEconomico ag2(2,Obras,500,make_pair(9,19),new Denuncias(4,5),new Inspecoes(11,1),new Data(2019,12,11),10);
    AgenteEconomico ag3(3,Obras,500,make_pair(9,19),new Denuncias(2,5),new Inspecoes(9,2),new Data(2019,12,10),11);
*/
    loadGraphNodesInfo(gr,"../resources/graphs/GridGraphs/4x4/nodes.txt", "../resources/graphs/GridGraphs/4x4/nodes.txt","../resources/graphs/GridGraphs/4x4/edges.txt",40000.0);

    AutoridadePublica AtPub("src/GraphViewer/example/resources/agentes.txt","src/GraphViewer/example/resources/brigadas.txt");


    //Primeiro caso homogéneo com capacidade limitada da brigada que vai a todos os AgEcono
    AtPub.setIdNo(0);
    int idAtPub = AtPub.getIdNo();
    vector<AgenteEconomico *> agEcono;

    for(auto AE: AtPub.get_agentes())
        agEcono.push_back(AE.second);

    graph.findVertex(AtPub.getIdNo())->setTagType(AutPub);
    for(auto it : AtPub.get_agentes()) {
      auto eV =  graph.findVertex(it.second->get_idNo());
        if (eV != NULL) {
            eV->setTagType(AgEcono);
        }
    }




    Brigada brg1(1,8,9,Obras);
    auto aux = getRotaBrigada(gr,AtPub,Obras,dijkstra,agEcono,TmpViagInspecFull,*AtPub.get_brigadas().at(0));

    for(auto v: aux)
        cout << v->getInfo() <<" ";
    cout << endl;
   drawGraph(gr,"Porto_Strong_Component",7777,EdgeType::DIRECTED, true);



   //for(auto brg: map com brigadas



   }


/*

    vector<vector<int>> saveAllSCC2 = graph2.KosarajuMainAlgo();
    int size;
    vector<int > saveStrong;
    for(auto vectorSCC: saveAllSCC2) {
        // cout << "hey" << endl;
        cout <<"Size: " << vectorSCC.size() << endl;
        if(vectorSCC.size() == 3964) {
            saveStrong = vectorSCC;
            size = vectorSCC.size();
            cout << "-------------------------------------------------------------" << endl;
        }
        for (auto v: vectorSCC)
            cout << v << " ";
        cout << endl;
    }
    cout << "Certo:" << saveStrong.size()<< endl;
    for (auto v: saveStrong)
        cout << v << " ";
    cout << endl;

     drawGraph(graph2,"Porto_Strong_Component",7777,EdgeType::UNDIRECTED, false);
    vector<vector<double>> distMin2 = vector<vector<double>>(30000, vector<double>(30000, INF));
    //vector para guardador predecessores de vertices e assim obter os nós/vértices do caminho mais curto pretendido
    vector<vector<int>> pathMin2 = vector<vector<int>>(30000, vector<int>(30000, -1));
*/


    //  graph.floydWarshallShortestPath(0.001);
   /* vector<int> aux2 = graph.getPathTo(1000);
    for(auto v: aux2)
        cout << v << " ";
    */

    /* cout << graph.getMaxId() << endl;
     graph.dijkstraShortestPath(11);
     vector<int> aux = graph.getPathTo(26803);

     if(aux.size() == 0){
         cout << "Caminho impossível, sem ligação" << endl;
     }
     for(int i = 0; i < aux.size(); i++)
         cout << aux.at(i) <<" " << endl;

     cout << graph.findVertex(11)->getDist() << " " << "distMin de origem!" << endl;
     int sum = 0;
     for(int i = 0; i < aux.size(); i++) {
         sum += graph.findVertex(aux.at(i))->getDist();

     }
     cout << sum;*/
/*
    for(int i = 0; i < graph.getVertexSet().size(); i++) {

        graph.getVertexSet()[i]->setInfo(i);

    }



    graph.floydWarshallShortestPath(0.001);


    vector<int> aux = graph.getfloydWarshallPath(11,221);
    if(aux.size() == 0){
        cout << "Caminho impossível, sem ligação" << endl;
    }
    for(int i = 0; i < aux.size(); i++)
        cout << aux.at(i) <<" " << endl;


    return 0;*/






