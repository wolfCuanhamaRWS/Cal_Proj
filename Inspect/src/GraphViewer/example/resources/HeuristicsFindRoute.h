//
// Created by flavio on 16/06/20.
//

#ifndef EXAMPLE_HEURISTICSFINDROUTE_H
#define EXAMPLE_HEURISTICSFINDROUTE_H
#include "algorithm"
#include "AutoridadePublica.h"
#include "Graph.h"


#define INF std::numeric_limits<double>::max()

enum AlgorithmMinDist {dijkstra,Bellman_Ford};

enum AlgorithmTmpViagInspec{TmpViag,TmpViagInspec,TmpViagInspecFull};


/*bool checkAgEconoValidity(AgenteEconomico &agEcono, double tmpoViagem,Brigada &brig,AutoridadePublica &autPub,double tmpTrabAcumulado){
    return(brig.get_hora_inicio() + tmpTrabAcumulado + tmpoViagem < agEcono.get_horario_funcionamento().second && (brig.get_hora_inicio() + tmpTrabAcumulado + tmpoViagem) >= agEcono.get_horario_funcionamento().first)


}*/

template <class T>
Vertex<T> *searchNearestAgEconoTmpViagTmpInpec(T source, Graph<T> &graph, AutoridadePublica &autPub,AtividadeEconomica atEcono,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono){
    double tmpViagem = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(source);
    else
        graph.bellmanFordShortestPath(source);

    vector<AgenteEconomico *>:: iterator savePos;
    bool controlIterator = false;
    Vertex<T> *resV = NULL;
    for(auto it = agEcono.begin(); it != agEcono.end(); it++) {

        auto v = graph.findVertex((*it)->get_idNo());
        if(v == NULL) return resV;
        double auxVal = (v->getDist() + (autPub.get_agentes().at(v->getInfo())->getTmpInpec()));
        if(tmpViagem >  auxVal && auxVal != INF) {//controla tmpViagem mínimos e caso em que é imposśivel ir de um nó para outro

            tmpViagem =  auxVal;
            resV = v;
            savePos = it;
            controlIterator = true;
        }


    }
    if(controlIterator)//Controla se itarador "aponta" para algo ou nao, de forma a conseguir eliminar agentes economicos de agEcono sem erros
        agEcono.erase(savePos);//apagamos agente economico para o qual ja verificamos ser o mais proximo da uma dada origem de partida
    return resV;
}





template <class T>
Vertex<T> *searchNearestAgEconoTmpViagem(T source, Graph<T> &graph, AutoridadePublica &autPub,AtividadeEconomica atEcono,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono){
    double tmpViagem = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(source);
    else
        graph.bellmanFordShortestPath(source);

    vector<AgenteEconomico *>:: iterator savePos;
    Vertex<T> *resV = NULL;
    for(auto it = agEcono.begin(); it != agEcono.end(); it++) {

            auto v = graph.findVertex((*it)->get_idNo());
            if(v == NULL) return resV;

            if(tmpViagem > v->getDist()) {

                tmpViagem = min(tmpViagem, v->getDist());
                resV = v;
                savePos = it;

            }


    }
    agEcono.erase(savePos);//apagamos agente economico para o qual ja verificamos ser o mais proximo da uma dada origem de partida
    return resV;
}



template <class T>
Vertex<T> *searchNearestAgEconoTmpViagTmpInpecFull(T source, Graph<T> &graph, AutoridadePublica &autPub,AtividadeEconomica atEcono,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,double &tmpViagemCounter,Brigada &brg){
    double tmpViagemInspec = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(source);
    else
        graph.bellmanFordShortestPath(source);

    vector<AgenteEconomico *>:: iterator savePos;
    bool controlIterator = false;
    Vertex<T> *resV = NULL;
    for(auto it = agEcono.begin(); it != agEcono.end(); it++) {

        auto v = graph.findVertex((*it)->get_idNo());//Obter vetor correspondente ao agente económico a ser avaliado
        if(v == NULL) return resV;
        //Hora actual obtida usando tempo de viagens e inspeções a agentes económicos anteriores por uma certa brigada que tem um horário de início de trabalho e horas totais máximas de trabalho diário
        double horaActual = tmpViagemCounter + brg.get_hora_inicio() + v->getDist(); //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
        double auxVal = (v->getDist() + (autPub.get_agentes().at(v->getInfo())->getTmpInpec())); //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo
        if(tmpViagemInspec >  auxVal && auxVal != INF && horaActual >= (*it)->get_horario_funcionamento().first && horaActual < (*it)->get_horario_funcionamento().second ) {//controla tmpViagem mínimos e caso em que é imposśivel ir de um nó para outro

            tmpViagemInspec =  auxVal;
            resV = v;
            savePos = it;
            controlIterator = true;
        }


    }
    if(tmpViagemInspec < INF && tmpViagemInspec  )
        tmpViagemCounter += (tmpViagemInspec + (*savePos)->getTmpInpec());
    if(controlIterator)//Controla se itarador "aponta" para algo ou nao, de forma a conseguir eliminar agentes economicos de agEcono sem erros
        agEcono.erase(savePos);//apagamos agente economico para o qual ja verificamos ser o mais proximo da uma dada origem de partida
    if(tmpViagemCounter > (brg.get_hora_inicio() + brg.get_horas_trabalho()))
        return NULL;

    else
        return resV;
}









/**Função para achar rotas, generalizando para usar dijktra ou bellman Ford
 *Necessita sempre que grafo seja constituído por vértices que pertencem à mesma componente fortemente conexa
 * @tparam T
 * @param graph
 * @param brigada
 * @param autPub
 * @return
 */
template <class T>
vector<Vertex<T> *> getRotaBrigada(Graph<T> &graph, AutoridadePublica &autPub,AtividadeEconomica atEcono,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,AlgorithmTmpViagInspec algorithmTmpViagInspec,Brigada &brg ){
    double tmpViagInspecCounter = 0;

    vector<Vertex<T> *> resRotaBrig;
    auto v =  graph.findVertex(autPub.getIdNo());//temos de verificar se autoridade publica  existe no grafo


    if(v!= NULL && agEcono.size()!= 0) {

        if(algorithmTmpViagInspec == TmpViag)
            v = searchNearestAgEconoTmpViagem(v->getInfo(),graph,autPub,atEcono,algorithm,agEcono);
        else if(algorithmTmpViagInspec == TmpViagInspec)
            v = searchNearestAgEconoTmpViagTmpInpec(v->getInfo(),graph,autPub,atEcono,algorithm,agEcono);
        else{
            v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,atEcono,algorithm,agEcono,tmpViagInspecCounter,brg);
        }
        if(v!= NULL){
            resRotaBrig.push_back(v);
        }
        else{ return resRotaBrig;}

        //controlo de distribuição de rota para brigada tendo em conta que temos Ag. Econo. para distribuir e que brigada ainda temm tempo de trabalho a trabalhar
        while(agEcono.size()!=0 && tmpViagInspecCounter < brg.get_horas_trabalho()) {
            //Diferentes algoritmos
            if(algorithmTmpViagInspec == TmpViag)
                v = searchNearestAgEconoTmpViagem(v->getInfo(),graph,autPub,atEcono,algorithm,agEcono);

            else if(algorithmTmpViagInspec == TmpViagInspec)
                v = searchNearestAgEconoTmpViagTmpInpec(v->getInfo(),graph,autPub,atEcono,algorithm,agEcono);

            else{
                v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,atEcono,algorithm,agEcono,tmpViagInspecCounter,brg);
            }
            if (v == NULL)
                break;
            else {
                resRotaBrig.push_back(v);

            }

        }

    }
    else{
        return resRotaBrig;
    }

    return  resRotaBrig;


}


#endif //EXAMPLE_HEURISTICSFINDROUTE_H
