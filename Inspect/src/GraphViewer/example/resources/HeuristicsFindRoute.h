//
// Created by flavio on 16/06/20.
//

#ifndef EXAMPLE_HEURISTICSFINDROUTE_H
#define EXAMPLE_HEURISTICSFINDROUTE_H
#include "algorithm"
#include "AutoridadePublica.h"
#include "Graph.h"
#include "utils.h"


#define INF std::numeric_limits<double>::max()

enum AlgorithmMinDist {dijkstra,Bellman_Ford,FloyWarshall};

enum AlgorithmTmpViagInspec{TmpViag,TmpViagInspecFull,TmpViagInspectFullUrgency, TmpViagUrgency};
template <class T>
Vertex<T> *searchNearestAgEconoTViagTInspecFullUrgency(T source, Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,double &tmpViagemCounter,Brigada &brg, bool distOrFullCheck);



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
pair<vector<int>,pair<double,int>> getRotaBrigada(Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,AlgorithmTmpViagInspec algorithmTmpViagInspec,Brigada &brg ){
    double tmpViagInspecCounter = 0;
    pair<vector<int>,pair<double,int>> res;
    vector<int> resRotaBrig;
    auto v =  graph.findVertex(autPub.getIdNo());//temos de verificar se autoridade publica  existe no grafo


    if(v!= NULL && agEcono.size()!= 0) {
        // Escolhas das quatro formas de calcular as rotas, : Usando só TmpViagem ou TmpViagem + TmpInspec, TmpViagem + urgencia ou TmpViagem + TmpInspec * urgència
        if(algorithmTmpViagInspec == TmpViag)
            v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false);



        else if( algorithmTmpViagInspec == TmpViagInspecFull ){
            v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true);

        }
        else if(algorithmTmpViagInspec == TmpViagInspectFullUrgency){
            v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true);


        }
        else{
            v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false);

        }

        if(v!= NULL){
            resRotaBrig.push_back(v->getInfo());
        }
        else{
            res.first = resRotaBrig;
            res.second.first = tmpViagInspecCounter;
            res.second.second = brg.get_id();
            return res;}

        //controlo de distribuição de rota para brigada tendo em conta que temos Ag. Econo. para distribuir e que brigada ainda temm tempo de trabalho a trabalhar
        while(agEcono.size()!=0 && tmpViagInspecCounter < brg.get_horas_trabalho()) {
            //Diferentes algoritmos
            if(algorithmTmpViagInspec == TmpViag)
                v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false);



            else if( algorithmTmpViagInspec == TmpViagInspecFull ){
                v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true);

            }
            else if(algorithmTmpViagInspec == TmpViagInspectFullUrgency){
                v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true);


            }
            else{
                v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false);

            }


            if (v == NULL)
                break;
            else {
                resRotaBrig.push_back(v->getInfo());

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

template <class T>
Vertex<T> *searchNearestAgEconoTViagTInspecFullUrgency(T source, Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,double &tmpViagemCounter,Brigada &brg, bool distOrFullCheck){
    double tmpViagemInspec = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(source);
    else if( algorithm == Bellman_Ford)
        graph.bellmanFordShortestPath(source);

    double auxDistOrFullCheck = 0.0;
    if(distOrFullCheck)
        auxDistOrFullCheck = 1.0;

    //Variáveis globais usadas para comparações e guardar o agente económico pretendio
    vector<AgenteEconomico *>:: iterator savePos;
    bool controlIterator = false;
    Vertex<T> *resV = NULL;
    //Valor de pontuação de urgência a ser comparado entre agentes Económicos
    double pontuacaoUrgencia = (INF - 1) *  -1;



    for(auto it = agEcono.begin(); it != agEcono.end(); it++) {

        //Obter nó correspondente ao agente económico a ser avaliado
        Vertex<T> *v = graph.findVertex((*it)->get_idNo());
        if(v == NULL) return resV; // se não existe no nosso grafo, não pode ser inspecionado
        //Valor de pontuação de urgência a ser comparado entre agentes Económicos

        //Hora actual obtida usando tempo de viagens e inspeções a agentes económicos anteriores por uma certa brigada que tem um horário de início de trabalho e horas totais máximas de trabalho diário
        double distVectV = 0.0;
        double horaActual = 0.0;
        double auxVal = 0.0;
        //Caso em que usamos algoritmo FloydWarshall
        if(algorithm == FloyWarshall){
            distVectV = graph.getDistMin()[source][v->getInfo()];

            double horaActual = tmpViagemCounter + brg.get_hora_inicio() + distVectV; //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
            double auxVal = (distVectV + ((*it)->getTmpInpec() * auxDistOrFullCheck)); //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo

        }else {
            distVectV = v->getDist();
            double horaActual = tmpViagemCounter + brg.get_hora_inicio() + distVectV; //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
            double auxVal = (distVectV  + ((*it)->getTmpInpec() * auxDistOrFullCheck)); //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo
        }
        //controla tmpViagem mínimos caso em que é imposśivel ir de um nó para outro, horários de funcionamento, urgencia de inspeções
        if(tmpViagemInspec >  auxVal && auxVal != INF && horaActual >= (*it)->get_horario_funcionamento().first && horaActual  <= (*it)->get_horario_funcionamento().second && tmpViagemCounter + distVectV  + ((*it)->getTmpInpec() * auxDistOrFullCheck)  <= brg.get_horas_trabalho() && (*it)->getUrgInspec() > pontuacaoUrgencia ) {

            tmpViagemInspec =  auxVal;
            resV = v;
            savePos = it;
            controlIterator = true;
            pontuacaoUrgencia = (*it)->getUrgInspec();
        }


    }

    if(!distOrFullCheck)
        auxDistOrFullCheck = 1.0;
    //Verificar se tempos de viagem e inspeções acumuladas ultrapassam o horário de trabalho da brigada em questão
    if(tmpViagemInspec < INF && (tmpViagemInspec + ((*savePos)->getTmpInpec()* auxDistOrFullCheck) + tmpViagemCounter) <= (brg.get_hora_inicio() + brg.get_horas_trabalho()) )
        tmpViagemCounter += tmpViagemInspec + ((*savePos)->getTmpInpec()* auxDistOrFullCheck);


    //Controla se itarador "aponta" para algo ou nao, de forma a conseguir eliminar agentes economicos de agEcono sem erros
    if(controlIterator &&  tmpViagemCounter <= brg.get_horas_trabalho())
        agEcono.erase(savePos);//apagamos agente economico para o qual ja verificamos ser o mais proximo da uma dada origem de partida e que tem maior urgencia em ser inspecionado



    if((tmpViagemCounter + brg.get_hora_inicio() )>= (brg.get_hora_inicio() + brg.get_horas_trabalho()))
        return NULL;

    else
        return resV;
}





#endif //EXAMPLE_HEURISTICSFINDROUTE_H
