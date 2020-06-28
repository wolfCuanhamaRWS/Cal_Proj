#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <csignal>
#include <sstream>
#include <random>
#include <time.h>
#include <chrono>
#include "../src/Graph.h"
#include "../src/AgenteEconomico.h"
#include "../src/AutoridadePublica.h"
#include "../src/Local.h"
#include "../src/Brigada.h"
#include "../src/menus.h"
#include "../src/MapImport.h"
#include "HeuristicsFindRoute.h"
using namespace std;
using testing::Eq;


Graph<int> CreateTestGraph2() {

    Graph<int> graph;
   //id, h_t, h_i, A_E

   AgenteEconomico ag1(1,Obras,50,make_pair(9,19),new Denuncias(3,5),new Inspecoes(10,1),new Data(2019,12,11),2);
   AgenteEconomico ag2(2,Obras,50,make_pair(9,19),new Denuncias(4,5),new Inspecoes(11,1),new Data(2019,12,11),14);
   AgenteEconomico ag3(3,Obras,50,make_pair(9,19),new Denuncias(2,5),new Inspecoes(9,2),new Data(2019,12,10),22);


    AutoridadePublica AtPub(1,3);
    AtPub.addBrigada(new Brigada (1,8,9,Obras)); //id, h_t, h_i, A_E

    AtPub.addAgenteEcon(&ag1);
    AtPub.addAgenteEcon(&ag2);
    AtPub.addAgenteEcon(&ag3);
    AtPub.setIdNo(7);

   loadGraphNodesInfo(graph,"../src/Mapas/GridGraphs/4x4/nodes.txt", "../src/Mapas/GridGraphs/4x4/nodesLatLng.txt","../src/Mapas/GridGraphs/4x4/edges.txt",40.0 );

    //Sinalizar AutPub
    cout << graph.getMaxXGraphView() << endl;
    for(auto it : AtPub.get_agentes()){
        auto et = graph.findVertex(it.second->get_idNo());
        if( et != NULL){
            et->setTagType(AgEcono);


        }
    }

    //sinalizar AutPub
    auto et = graph.findVertex(AtPub.getIdNo());
    if( et != NULL){
        et->setTagType(AutPub);


    }

    cout << ag1.get_id() << endl;


    cout << graph.getMaxXGraphView() << endl;

    cout << graph.getNumVertex()<< "NumVertex" << endl;

    return graph;

}


/**
 * Auxiliary functions to tests...
 *
 */
Graph<int> CreateTestGraph() {
    Graph<int> myGraph;

    for(int i = 1; i <= 7; i++)
        myGraph.addVertex(i);

    myGraph.addEdge(1, 2, 2);
    myGraph.addEdge(1, 4, 7);
    myGraph.addEdge(2, 4, 3);
    myGraph.addEdge(2, 5, 5);
    myGraph.addEdge(3, 1, 2);
    myGraph.addEdge(3, 6, 5);
    myGraph.addEdge(4, 3, 1);
    myGraph.addEdge(4, 5, 1);
    myGraph.addEdge(4, 6, 6);
    myGraph.addEdge(4, 7, 4);
    myGraph.addEdge(5, 7, 2);
    myGraph.addEdge(6, 4, 3);
    myGraph.addEdge(7, 6, 4);

    return myGraph;
}

template <typename T1, typename T2>
basic_ostream<char>& operator<<(basic_ostream<char> & strm, const pair<T1, T2>& kvPair)
{
    strm << "(" << kvPair.first << ", " << kvPair.second << ")";
    return strm;
}


void geneateRandomGridGraph(int n, Graph<pair<int,int>> & g) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            g.addVertex(make_pair(i,j));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                    if ((di != 0) != (dj != 0) && i+di >= 0 && i+di < n && j+dj >= 0 && j+dj < n)
                        g.addEdge(make_pair(i,j), make_pair(i+di,j+dj), dis(gen));
}

template <class T>
void checkAllPaths(Graph<T> &g, string expected) {
    stringstream ss;
    vector<Vertex<T>* > vs = g.getVertexSet();
    for(unsigned int i = 0; i < vs.size(); i++) {
        ss << vs[i]->getInfo() << "<-";
        if ( vs[i]->getPath() != NULL )
            ss << vs[i]->getPath()->getInfo();
        ss << "|";
    }
    EXPECT_EQ(expected, ss.str());
}

template <class T>
void checkSinglePath(vector<T> path, string expected) {
    stringstream ss;
    for(unsigned int i = 0; i < path.size(); i++)
        ss << path[i] << " ";
    EXPECT_EQ(expected, ss.str());
}

/**
 * Unit tests... must be uncommented to proceed...
 */

 /*//Uncomment the test below...
TEST(Inspect, test_unweightedShortestPath) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.unweightedShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-1|5<-2|6<-3|7<-4|");
    checkSinglePath(myGraph.getPathTo(7), "3 1 4 7 ");

    myGraph.unweightedShortestPath(5);
    checkSinglePath(myGraph.getPathTo(6), "5 7 6 ");
}*/



 //Uncomment the test below...
TEST(Inspect, test_dijkstra) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.dijkstraShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    myGraph.dijkstraShortestPath(1);
    checkAllPaths(myGraph, "1<-|2<-1|3<-4|4<-2|5<-4|6<-4|7<-5|");
    checkSinglePath(myGraph.getPathTo(7), "1 2 4 5 7 ");

    myGraph.dijkstraShortestPath(5);
    checkSinglePath(myGraph.getPathTo(6), "5 7 6 ");

    myGraph.dijkstraShortestPath(7);
    checkSinglePath(myGraph.getPathTo(1), "7 6 4 3 1 ");
}

/*

 //Uncomment the test below...
TEST(Inspect, test_performance_dijkstra) {
    for (int n = 10; n <= 100; n += 10) {
        Graph< pair<int,int> > g;
        cout << "Dijkstra generating grid " << n << " x " << n << " ..." << endl;
        geneateRandomGridGraph(n, g);
        cout << "Dijkstra processing grid " << n << " x " << n << " ..." << endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g.dijkstraShortestPath(make_pair(i,j));
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        cout << "Dijkstra processing grid " << n << " x " << n << " average time (micro-seconds)=" << (elapsed / (n*n)) << endl;
    }
}

*/

 //Uncomment the test below...
TEST(Inspect, test_bellmanFord) {
    Graph<int> myGraph = CreateTestGraph();

    myGraph.bellmanFordShortestPath(3);
    checkAllPaths(myGraph, "1<-3|2<-1|3<-|4<-2|5<-4|6<-3|7<-5|");

    myGraph.bellmanFordShortestPath(1);
    checkSinglePath(myGraph.getPathTo(7), "1 2 4 5 7 ");

    myGraph.bellmanFordShortestPath(5);
    checkSinglePath(myGraph.getPathTo(6), "5 7 6 ");

    myGraph.bellmanFordShortestPath(7);
    checkSinglePath(myGraph.getPathTo(1), "7 6 4 3 1 ");


}



 //Uncomment the test below...
TEST(Inspect, test_floydWarshall) {
    Graph<int> myGraph = CreateTestGraph();
    myGraph.floydWarshallShortestPath(1,0.0001);
    checkSinglePath(myGraph.getfloydWarshallPath(1, 7), "1 2 4 5 7 ");
    checkSinglePath(myGraph.getfloydWarshallPath(5, 6), "5 7 6 ");
    checkSinglePath(myGraph.getfloydWarshallPath(7, 1), "7 6 4 3 1 ");
}
TEST(Inspect, test_searchNearestAgEconoTmpViagem){

    Graph<int> gr;

    AgenteEconomico ag1(1,Obras,50,make_pair(9,19),new Denuncias(3,5),new Inspecoes(10,1),new Data(2019,12,11),11);
    AgenteEconomico ag2(2,Obras,50,make_pair(9,19),new Denuncias(4,5),new Inspecoes(11,1),new Data(2019,12,11),5);
    AgenteEconomico ag3(3,Obras,50,make_pair(9,19),new Denuncias(2,5),new Inspecoes(9,2),new Data(2019,12,10),9);


    AutoridadePublica AtPub(1,3);
    AtPub.addBrigada(new Brigada (1,8,9,Obras)); //id, h_t, h_i, A_E

    AtPub.addAgenteEcon(&ag1);
    AtPub.addAgenteEcon(&ag2);
    AtPub.addAgenteEcon(&ag3);
    AtPub.setIdNo(0);

    loadGraphNodesInfo(gr,"src/INSPECT_IT/src/resources/graphs/GridGraphs/4x4/nodes.txt", "src/INSPECT_IT/src/graphs/GridGraphs/4x4/nodes.txt","src/INSPECT_IT/src/graphs/GridGraphs/4x4/edges.txt",40.0);





    Vertex<int> *res = searchNearestAgEconoTmpViagem(gr,AtPub,Obras,dijkstra);

    EXPECT_EQ(res->getInfo(), 5);

  //  drawGraph(gr,"Porto_Strong_Component",7776,EdgeType::DIRECTED, true);


}



