//
// Created by flavio on 26/06/20.
//
#include "Conectividade.h"
void LargeSSCFilterGraph(Graph<int> &gr){



    vector<int> aux;

    KosarajuGetMaxSizeStrongCC(gr,aux);
    cout << endl << "Maior Componente fortemente Conexa tem: " << aux.size() << " nós!" <<endl << endl;

    vector<int> removeVtx;
    sort(aux.begin(),aux.end());
    for(auto v : gr.getVertexSet()){

        int infoV = v->getInfo();
        if( find(aux.begin(),aux.end(),infoV) == aux.end()) {
            removeVtx.push_back(infoV);
        }

    }

    for(auto v: removeVtx){
        gr.removeVertex(v);
    }

  //Normalizar nós e valores de x e y min,max para obter mapa no graphView ajustado
    for(int i = 1; i <= gr.getVertexSet().size(); i ++){
        gr.getVertexSet()[i - 1]->setInfo(i);
    }

    gr.setMaxXGraphView((std::numeric_limits<double>::min() - 1) * -1);
    gr.setMinXGraphView(std::numeric_limits<double>::max());
    gr.setMaxYGraphView(((std::numeric_limits<double>::min() - 1) * -1));
    gr.setMinYGraphView(std::numeric_limits<double>::max());




    for(auto v: gr.getVertexSet()){
        gr.controlCoordsGraphView(v->getLocal().get_xMap(),v->getLocal().get_yMap());
    }


}


void FastSSCKosorajuFilter(vector<int> &aux,Graph<int> &gr){
    vector<int> removeVtx;
    sort(aux.begin(),aux.end());
    for(auto v : gr.getVertexSet()){

        int infoV = v->getInfo();
        if( find(aux.begin(),aux.end(),infoV) == aux.end()) {
            removeVtx.push_back(infoV);
        }

    }

    for(auto v: removeVtx){
        gr.removeVertex(v);
    }
    //Normalizar nós e valores de x e y min,max para obter mapa no graphView ajustado
    for(int i = 1; i <= gr.getVertexSet().size(); i ++){
        gr.getVertexSet()[i - 1]->setInfo(i);
    }

    gr.setMaxXGraphView((std::numeric_limits<double>::min() - 1) * -1);
    gr.setMinXGraphView(std::numeric_limits<double>::max());
    gr.setMaxYGraphView(((std::numeric_limits<double>::min() - 1) * -1));
    gr.setMinYGraphView(std::numeric_limits<double>::max());




    for(auto v: gr.getVertexSet()){
        gr.controlCoordsGraphView(v->getLocal().get_xMap(),v->getLocal().get_yMap());
    }



}


void printAllSccKosaraju(vector<vector<int> > &aux){
    cout << endl;
    for( auto SSC: aux){
        for(auto v: SSC)
            cout << v << " ";
        cout << endl;
    }
}

template<class T>
void KosarajuGetMaxSizeStrongCC(Graph<T> &graph,vector<int> &res){

    vector<vector<int>> aux;

    aux = graph.KosarajuMainAlgo();
    for(auto v: aux) {
        if (v.size() > res.size())
            res = v;
    }

}

void printMaxSizeSccKosoraju(vector<int> &res){
    cout << res.size() << " nós, os elementos da maior Componente Fortemente Conexa são:  ";
    for(auto v: res) {
        cout << v << " ";

    }
    cout << endl << endl;
}

vector<int> getMaxSizeKosarajuStrongCC(vector<vector<int>> &SCCs){

    vector<int> res;
    for(auto v: SCCs) {
        if (v.size() > res.size())
            res = v;
    }
    return res;
}


#include "Conectividade.h"
