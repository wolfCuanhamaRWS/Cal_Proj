#ifndef CAL_MENUS_H
#define CAL_MENUS_H
#include <iostream>

#include "Utils/utils.h"
#include "Model/AutoridadePublica.h"
#include "../GraphViewer/graphviewer.h"
#include "Algorithms/HeuristicsFindRoute.h"
#include "Controller/RouteViewCalc.h"
#include "Utils/MapImport.h"
#include "Algorithms/Conectividade.h"
#include "Algorithms/AlgorithmPerformanceTest.h"

using namespace std;

void printAutoridadePublicaMenu();
void autoridadePublicaMenu(AutoridadePublica &autoridade);
void mainMenu(AutoridadePublica &autoridade);
void menuLoadMaps(Graph<int> &graph,int  input,double velocidadeMediaBrigadas);
void getGraphFiltred(Graph<int> &gr);
void calculateRoutes(Graph<int> &gr,AutoridadePublica &AtPub,AlgorithmMinDist algorithm ,AlgorithmTmpViagInspec tmpViagInspec,RouteCalcRestriction restriction,bool GPSCheck, pair<int, double> idNoRadius);
void getIdNoAtPub( AutoridadePublica &autoridade,  Graph<int> &gr2);

#endif //CAL_MENUS_H
