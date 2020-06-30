//
// Created by flavio on 26/06/20.
//

#ifndef EXAMPLE_ROUTEVIEWCALC_H
#define EXAMPLE_ROUTEVIEWCALC_H
#include "Model/Graph.h"
#include <string>
#include <cstdio>
#include "../GraphViewer/graphviewer.h"
#include <csignal>
#include "Model/AgenteEconomico.h"
#include "Model/AutoridadePublica.h"
#include <vector>
#include "Model/Graph.h"
#include "Algorithms/HeuristicsFindRoute.h"
#include "sstream"
#include "fstream"
string verifyTagColor(Tag type);
int verifyTagSize(Tag type);
void drawGraphFromFile(std::string name, unsigned int port);
GraphViewer &drawGraph( Graph<int> &graph,AutoridadePublica &AtPub, std::string windowFich , unsigned int port,int typeEdge,bool otherLabel);

enum RouteCalcRestriction{NoRestriction,AllEconoAct};
void CalculateDrawRoutes(GraphViewer &gv, Graph<int> &graph, AutoridadePublica &autPub,vector<AgenteEconomico *> &agEcono,AlgorithmMinDist algorithm,AlgorithmTmpViagInspec algorithmTmpViagInspec,RouteCalcRestriction restriction,bool GPSCheck,pair<int,double> idNoRadius);



#endif //EXAMPLE_ROUTEVIEWCALC_H
