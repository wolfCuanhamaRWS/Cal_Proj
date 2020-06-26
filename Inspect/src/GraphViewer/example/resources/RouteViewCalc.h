//
// Created by flavio on 26/06/20.
//

#ifndef EXAMPLE_ROUTEVIEWCALC_H
#define EXAMPLE_ROUTEVIEWCALC_H
#include "Graph.h"
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

template<class T>
GraphViewer &drawGraph( Graph<T> &graph, std::string windowFich , unsigned int port,int typeEdge,bool otherLabel);

enum RouteCalculateAtEconoeRestriction{NoRestriction,AllEconoAct};


template<class T>
void CalculateDrawRoutes(GraphViewer &gv, Graph<T> &graph, AutoridadePublica &autPub,vector<AgenteEconomico *> &agEcono,AlgorithmMinDist algorithm,AlgorithmTmpViagInspec algorithmTmpViagInspec,RouteCalculateAtEconoeRestriction restriction);



#endif //EXAMPLE_ROUTEVIEWCALC_H
