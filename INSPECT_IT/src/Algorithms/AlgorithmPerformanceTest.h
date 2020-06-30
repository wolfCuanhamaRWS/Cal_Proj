
#ifndef INSPECT_IT_ALGORITHMPERFORMANCETEST_H
#define INSPECT_IT_ALGORITHMPERFORMANCETEST_H

#include <limits>
#include <chrono>
#include "Model/Graph.h"
#include "Utils/MapImport.h"
#include <algorithm>
#include <random>
#include <algorithm>
#include "View/menus.h"


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
void CalRoutesTest(Graph<T> &gr, int cityOption,double velocMediaKH,unsigned  int numbInter,string nomeCidade,AutoridadePublica &autoridade);






#endif //INSPECT_IT_ALGORITHMPERFORMANCETEST_H
