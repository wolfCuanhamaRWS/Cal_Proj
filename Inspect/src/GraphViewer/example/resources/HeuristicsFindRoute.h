//
// Created by flavio on 16/06/20.
//

#ifndef EXAMPLE_HEURISTICSFINDROUTE_H
#define EXAMPLE_HEURISTICSFINDROUTE_H
#include "algorithm"
#include "AutoridadePublica.h"
#include "Graph.h"


#define INF std::numeric_limits<double>::max()

enum AlgorithmMinDist {dijkstra,Bellman_Ford,FloyWarshall};

enum AlgorithmTmpViagInspec{TmpViagDist,TmpViagInspecFull};


/*bool checkAgEconoValidity(AgenteEconomico &agEcono, double tmpoViagem,Brigada &brig,AutoridadePublica &autPub,double tmpTrabAcumulado){
    return(brig.get_hora_inicio() + tmpTrabAcumulado + tmpoViagem < agEcono.get_horario_funcionamento().second && (brig.get_hora_inicio() + tmpTrabAcumulado + tmpoViagem) >= agEcono.get_horario_funcionamento().first)


}*/








template <class T>
Vertex<T> *searchNearestAgEconoTmpViagTmpInpecFull(T source, Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,double &tmpViagemCounter,Brigada &brg, bool distOrFullCheck){
    double tmpViagemInspec = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(source);
    else
        graph.bellmanFordShortestPath(source);

    double auxDistOrFullCheck = 0.0;
    if(distOrFullCheck)
        auxDistOrFullCheck = 1.0;
    vector<AgenteEconomico *>:: iterator savePos;
    bool controlIterator = false;
    Vertex<T> *resV = NULL;
    for(auto it = agEcono.begin(); it != agEcono.end(); it++) {

        auto v = graph.findVertex((*it)->get_idNo());//Obter vetor correspondente ao agente económico a ser avaliado
        if(v == NULL) return resV;
        //Hora actual obtida usando tempo de viagens e inspeções a agentes económicos anteriores por uma certa brigada que tem um horário de início de trabalho e horas totais máximas de trabalho diário
        double horaActual = tmpViagemCounter + brg.get_hora_inicio() + v->getDist(); //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
        double auxVal = (v->getDist() + ((*it)->getTmpInpec() * auxDistOrFullCheck)); //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo
        if(tmpViagemInspec >  auxVal && auxVal != INF && horaActual >= (*it)->get_horario_funcionamento().first && horaActual  <= (*it)->get_horario_funcionamento().second && tmpViagemCounter + v->getDist() + ((*it)->getTmpInpec() * auxDistOrFullCheck)  <= brg.get_horas_trabalho()) {//controla tmpViagem mínimos e caso em que é imposśivel ir de um nó para outro

            tmpViagemInspec =  auxVal;
            resV = v;
            savePos = it;
            controlIterator = true;
        }


    }

    if(!distOrFullCheck)
        auxDistOrFullCheck = 1.0;

    if(tmpViagemInspec < INF && (tmpViagemInspec + ((*savePos)->getTmpInpec()* auxDistOrFullCheck) + tmpViagemCounter) <= (brg.get_hora_inicio() + brg.get_horas_trabalho()) )
        tmpViagemCounter += tmpViagemInspec + ((*savePos)->getTmpInpec()* auxDistOrFullCheck);
    if(controlIterator &&  tmpViagemCounter <= brg.get_horas_trabalho())//Controla se itarador "aponta" para algo ou nao, de forma a conseguir eliminar agentes economicos de agEcono sem erros
        agEcono.erase(savePos);//apagamos agente economico para o qual ja verificamos ser o mais proximo da uma dada origem de partida
    if((tmpViagemCounter + brg.get_hora_inicio() )>= (brg.get_hora_inicio() + brg.get_horas_trabalho()))
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
pair<vector<Vertex<T> *>,pair<double,int>> getRotaBrigada(Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,AlgorithmTmpViagInspec algorithmTmpViagInspec,Brigada &brg ){
    double tmpViagInspecCounter = 0;
    pair<vector<Vertex<T> *>,pair<double,int>> res;
    vector<Vertex<T> *> resRotaBrig;
    auto v =  graph.findVertex(autPub.getIdNo());//temos de verificar se autoridade publica  existe no grafo


    if(v!= NULL && agEcono.size()!= 0) {

        if(algorithmTmpViagInspec == TmpViagDist)
            v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false);



        else{
            v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true);
        }
        if(v!= NULL){
            resRotaBrig.push_back(v);
        }
        else{
            res.first = resRotaBrig;
            res.second.first = tmpViagInspecCounter;
            res.second.second = brg.get_id();
            return res;}

        //controlo de distribuição de rota para brigada tendo em conta que temos Ag. Econo. para distribuir e que brigada ainda temm tempo de trabalho a trabalhar
        while(agEcono.size()!=0 && tmpViagInspecCounter < brg.get_horas_trabalho()) {
            //Diferentes algoritmos
            if(algorithmTmpViagInspec == TmpViagDist)
                v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false);

            else{
                v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true);
            }
            if (v == NULL)
                break;
            else {
                resRotaBrig.push_back(v);

            }

        }

    }
    else{
        res.first = resRotaBrig;
        res.second.first = tmpViagInspecCounter;
        res.second.second = brg.get_id();
        return res;
    }

    res.first = resRotaBrig;
    res.second.first = tmpViagInspecCounter;
    res.second.second =  brg.get_id();;
    return res;


}


#endif //EXAMPLE_HEURISTICSFINDROUTE_H
