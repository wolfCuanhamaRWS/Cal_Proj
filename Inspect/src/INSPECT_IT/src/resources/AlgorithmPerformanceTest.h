
#ifndef INSPECT_IT_ALGORITHMPERFORMANCETEST_H
#define INSPECT_IT_ALGORITHMPERFORMANCETEST_H

#include <limits>
#include <chrono>
#include "Graph.h"
#include "MapImport.h"
#include <algorithm>
#include <random>
#include <algorithm>
#include "menus.h"

#define INF std::numeric_limits<double>::max();
using namespace std::chrono;

using namespace std;
using namespace std::chrono;

void globalPerformanceTEst();

template<class T>
void DijkstraTest(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade);
template<class T>
void BellManFordTest(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade);

template<class T>
void FloydWarshallTestAllGraph(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade);

template<class T>
void KosarajuConectivityTEst(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade);

template<class T>
 void CalRoutesTest(Graph<T> &graph,string nosXYFich,string nosCoordGeoFich, string arestasFich, double velocMediaKH,unsigned  int numbInter,string nomeCidade);







#endif //INSPECT_IT_ALGORITHMPERFORMANCETEST_H
