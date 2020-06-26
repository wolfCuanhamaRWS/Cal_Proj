#ifndef CAL_MENUS_H
#define CAL_MENUS_H
#include <iostream>

#include "utils.h"
#include "AutoridadePublica.h"
#include "graphviewer.h"
#include "HeuristicsFindRoute.h"
#include "RouteViewCalc.h"

using namespace std;

void printAutoridadePublicaMenu();
void autoridadePublicaMenu(AutoridadePublica &autoridade);
void mainMenu(AutoridadePublica &autoridade);
template<class T>
void menuLoadMaps(Graph<T> &graph,int  input,double velocidadeMediaBrigadas);
template<class T>
void calculateRoutes(Graph<T> &gr,AutoridadePublica &AtPub,AlgorithmMinDist algorithm ,AlgorithmTmpViagInspec tmpViagInspec);

#endif //CAL_MENUS_H
