#ifndef CAL_MENUS_H
#define CAL_MENUS_H
#include <iostream>

#include "utils.h"
#include "AutoridadePublica.h"
#include "graphviewer.h"
#include "HeuristicsFindRoute.h"
#include "RouteViewCalc.h"
#include "MapImport.h"
#include "Conectividade.h"

using namespace std;

void printAutoridadePublicaMenu();
void autoridadePublicaMenu(AutoridadePublica &autoridade);
void mainMenu(AutoridadePublica &autoridade);
void menuLoadMaps(Graph<int> &graph,int  input,double velocidadeMediaBrigadas);
void getGraphFiltred(Graph<int> &gr);
void calculateRoutes(Graph<int> &gr,AutoridadePublica &AtPub,AlgorithmMinDist algorithm ,AlgorithmTmpViagInspec tmpViagInspec,RouteCalcRestriction restriction);
void getIdNoAtPub( AutoridadePublica &autoridade,  Graph<int> &gr2);

#endif //CAL_MENUS_H
