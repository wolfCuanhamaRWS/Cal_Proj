//
// Created by flavio on 06/06/20.
//
#include "MapImport.h"

template<class T>
Graph<int> loadGraphNodesInfo(string nosXYFich,string nosCoordGeoFich, string arestasFich,double velocMediaKH){

    Graph<int> grafo;

    //para filtrar informação pretendida
    string linhaXY;
    string linhaLatLong;
    string arestaLinha;
    //Para manipular ficheiros
    fstream nosCoordsXY;
    fstream nosCoordsGeoAux;
    fstream arestasNos;

    nosCoordsXY.open(nosXYFich);
    nosCoordsGeoAux.open(nosCoordGeoFich);
    //Obter numero de nós ficheiro com coords X e Y
    getline(nosCoordsXY, linhaXY);
    int numNos = stoi(linhaXY);

    //Obter numero de nós ficheiro com lat long
    getline(nosCoordsGeoAux,linhaLatLong);


    //Obter id's e coordenadas x,y de cada nó de um mapa escolhido mas também lat e long dos dois ficheiros
    for(int i = 0; i < numNos; i++){
        getline(nosCoordsXY, linhaXY);
        getline(nosCoordsGeoAux,linhaLatLong);


        //filtrar carateres que não interessam
        stringstream auxFiltrar(linhaLatLong);
        int info;
        double xMap;
        double yMap;
        string getCaract;
        //filtrar: ( e , para obter id
        getline(auxFiltrar,getCaract,'(');
        getline(auxFiltrar,getCaract,',');
        info = stoi(getCaract);

        //obter lat
        getline(auxFiltrar,getCaract,',');
        xMap = stod(getCaract);
        //obter long
        getline(auxFiltrar, getCaract,')');

        yMap = stod(getCaract);

        //nó com valores da latitude e longitude
        Local local(xMap,yMap);
        stringstream auxFiltrar2(linhaXY);


        //filtrar: ( e , para obter ID do nosso nó
        getline(auxFiltrar2,getCaract,'(');
        getline(auxFiltrar2,getCaract,',');
        info = stoi( getCaract);

        //obter x
        getline(auxFiltrar2,getCaract,',');
        xMap = stod(getCaract);
        //obter y
        getline(auxFiltrar2, getCaract,')');

        yMap = stod(getCaract);

        //Completamos nó/Local com valores x e y usados para representar mapa
        local.set_xMap(xMap);
        local.set_yMap(yMap);

        //Criar vértice para inserir no grafo e inserir nó/Local respetivo


        Vertex<int> aux(info);
        aux.setLocal(local);

        grafo.addVertex(info);

    }

    nosCoordsGeoAux.close();
    nosCoordsXY.close();

    //buscar arestas do grafo entre os nós constituintes


    arestasNos.open(arestasFich);


    getline(arestasNos,arestaLinha);

    //numero de arestas
    int numb_arestas = stoi(arestaLinha);

    //Adicionar arestas com o tempo de viagem entre cada par de nós ligados por arestas
    for(int i= 0; i < numb_arestas; i++){
        getline(arestasNos,arestaLinha);
        string getCaract;

        int orig ;
        int dest;

        stringstream auxFilter(arestaLinha);

        //obter vetor de origem
        getline(auxFilter,getCaract,'(');
        getline(auxFilter,getCaract,',');

        orig = stoi(getCaract);

        getline(auxFilter,getCaract,')');

        dest = stoi(getCaract);

        //adicionar aresta ao par de vértices obtido calculando tempo de viagem entre eles usando latitude e longitude
        double tmpViag;

        auto v1 = grafo.findVertex(orig);
        auto v2 = grafo.findVertex(dest);

        //Obter tempo de viagem entre
        tmpViag = v1->getTempViagem(v2->getLocal(),velocMediaKH);
        grafo.addEdge(orig, dest,tmpViag);



    }
    arestasNos.close();

}
