

#ifndef EXAMPLE_HEURISTICSFINDROUTE_H
#define EXAMPLE_HEURISTICSFINDROUTE_H
#include "algorithm"
#include "Model/AutoridadePublica.h"
#include "Model/Graph.h"
#include "Utils/utils.h"


#define INF std::numeric_limits<double>::max()

enum AlgorithmMinDist {dijkstra,Bellman_Ford,FloyWarshall};

enum AlgorithmTmpViagInspec{TmpViag,TmpViagInspecFull,TmpViagInspectFullUrgency, TmpViagUrgency,justUrgency};

template <class T>
Vertex<T> *searchNearestAgEconoTViagTInspecFullUrgency(T source, Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,double &tmpViagemCounter,Brigada &brg, bool distOrFullCheck,bool GPSCheck,pair<int,double> idNoRadius){
    double tmpViagemInspec = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(source);
    else if( algorithm == Bellman_Ford)
        graph.bellmanFordShortestPath(source);

    double auxDistOrFullCheck = 0.0;
    if(distOrFullCheck)
        auxDistOrFullCheck = 1.0;

    //Achar vértice central para comparar coordenadas num certo raio
    bool checkCoords = true;
    Vertex<T> *centralV;
    if(GPSCheck){
        centralV = graph.findVertex(idNoRadius.first);
        if(centralV == NULL)
            checkCoords = true; // true para passar nas restrições
    }



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

            horaActual = tmpViagemCounter + brg.get_hora_inicio() + distVectV; //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
            auxVal = (distVectV + ((*it)->getTmpInpec() * auxDistOrFullCheck)); //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo

        }else {
            distVectV = v->getDist();
            horaActual = tmpViagemCounter + brg.get_hora_inicio() + distVectV; //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
            auxVal = (distVectV  + ((*it)->getTmpInpec() * auxDistOrFullCheck)); //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo
        }



        if(GPSCheck){
            checkCoords = GPSCoordsLimitation((*it)->get_idNo(),*centralV,idNoRadius,graph);


        }


        //controla tmpViagem mínimos caso em que é imposśivel ir de um nó para outro, horários de funcionamento, urgencia de inspeções
        if((tmpViagemInspec >  auxVal && auxVal != INF && horaActual >= (*it)->get_horario_funcionamento().first && horaActual  <= (*it)->get_horario_funcionamento().second && tmpViagemCounter + distVectV  + ((*it)->getTmpInpec() * auxDistOrFullCheck)  <= brg.get_horas_trabalho() && checkCoords) || (*it)->getUrgInspec() > pontuacaoUrgencia ) {

            tmpViagemInspec =  auxVal;
            resV = v;
            savePos = it;
            controlIterator = true;
            pontuacaoUrgencia = (*it)->getUrgInspec();
        }


    }

    if(!distOrFullCheck)
        auxDistOrFullCheck = 1.0;

    double checkPossiblePastHour;
    double limitFinalHour = (brg.get_hora_inicio() + brg.get_horas_trabalho());
    //Verificar se tempos de viagem e inspeções acumuladas ultrapassam o horário de trabalho da brigada em questão
    if(controlIterator) {
        checkPossiblePastHour =tmpViagemInspec + ((*savePos)->getTmpInpec() * auxDistOrFullCheck) + tmpViagemCounter;


        if (tmpViagemInspec < INF && (checkPossiblePastHour + brg.get_hora_inicio()) <= limitFinalHour)
            tmpViagemCounter += tmpViagemInspec + ((*savePos)->getTmpInpec() * auxDistOrFullCheck);
    }
    //apagamos agente economico para o qual ja verificamos ser o mais proximo da uma dada origem de partida e que tem maior urgencia em ser inspecionado e ou cumpre outras restrições
    //apagamos agentes economicos viáveis e que são contabilizados e não viáveis para a mesma rota da mesma brigada
    //Controla se itarador "aponta" para algo ou nao, de forma a conseguir eliminar agentes economicos de agEcono sem erros
    if(controlIterator &&  (checkPossiblePastHour + brg.get_hora_inicio() ) <= limitFinalHour)
        agEcono.erase(savePos);
    if(controlIterator &&  (checkPossiblePastHour + brg.get_hora_inicio() ) > limitFinalHour)
        agEcono.erase(savePos);
    //salvaguarda todos os casos em que agente economico não é viável a ser visitado, não retornando qualquer agEcono
    if(controlIterator && (checkPossiblePastHour + brg.get_hora_inicio() ) > limitFinalHour)
        return NULL;

    else
        return resV; // retorna null se nenhum agEcono for considerado tendo em conta as restrições verificadas
}


/**Função que seleciona agentes económicos usando a pontuação de urgência como principal critério!!!ahvai25
 *
 * @tparam T
 * @param source
 * @param graph
 * @param autPub
 * @param algorithm
 * @param agEcono
 * @param tmpViagemCounter
 * @param brg
 * @param distOrFullCheck
 * @return
 */
template <class T>
Vertex<T> *searchNextUrgency(T source, Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,double &tmpViagemCounter,Brigada &brg,bool GPSCheck,pair<int,double> idNoRadius ){

    double tmpViagemInspec = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(source);
    else if( algorithm == Bellman_Ford)
        graph.bellmanFordShortestPath(source);


    //Achar vértice central para comparar coordenadas num certo raio
    bool checkCoords = true;
    Vertex<T> *centralV;
    if(GPSCheck){
        centralV = graph.findVertex(idNoRadius.first);
        if(centralV == NULL)
            checkCoords = true; // true para passar nas restrições
    }


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

        //Caso em que usamos algoritmo FloydWarshall
        if(algorithm == FloyWarshall){
            distVectV = graph.getDistMin()[source][v->getInfo()];

            horaActual = tmpViagemCounter + brg.get_hora_inicio() + distVectV; //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
            //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo

        }else {
            distVectV = v->getDist();
            horaActual = tmpViagemCounter + brg.get_hora_inicio() + distVectV; //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
            //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo
        }


        if(GPSCheck){
            checkCoords = GPSCoordsLimitation((*it)->get_idNo(),*centralV,idNoRadius,graph);


        }

        //Visita sempre primeiro o AgEcono onde a brigada cumpre o horário de funcionamento do mesmo ao mesmo tempo que se prefere o mais urgente
        //caso em que é imposśivel ir de um nó para outro, horários de funcionamento, urgencia de inspeções
        if( distVectV != INF && horaActual >= (*it)->get_horario_funcionamento().first && horaActual  <= (*it)->get_horario_funcionamento().second && (tmpViagemCounter + distVectV  + (*it)->getTmpInpec()) <= brg.get_horas_trabalho() && (*it)->getUrgInspec() > pontuacaoUrgencia && checkCoords) {

            tmpViagemInspec = distVectV;
            resV = v;
            savePos = it;
            controlIterator = true;
            pontuacaoUrgencia = (*it)->getUrgInspec();
        }


    }

    double checkPossiblePastHour;
    double limitFinalHour = (brg.get_hora_inicio() + brg.get_horas_trabalho());
    //Verificar se tempos de viagem e inspeções acumuladas ultrapassam o horário de trabalho da brigada em questão
    if(controlIterator) {
        checkPossiblePastHour =tmpViagemInspec + ((*savePos)->getTmpInpec() ) + tmpViagemCounter;


        if (tmpViagemInspec < INF && (checkPossiblePastHour + brg.get_hora_inicio()) <= limitFinalHour)
            tmpViagemCounter += tmpViagemInspec + ((*savePos)->getTmpInpec() );
    }
    //apagamos agente economico para o qual ja verificamos ser o mais proximo da uma dada origem de partida e que tem maior urgencia em ser inspecionado e ou cumpre outras restrições
    //apagamos agentes economicos viáveis e que são contabilizados e não viáveis para a mesma rota da mesma brigada
    //Controla se itarador "aponta" para algo ou nao, de forma a conseguir eliminar agentes economicos de agEcono sem erros
    if(controlIterator &&  (checkPossiblePastHour + brg.get_hora_inicio() ) <= limitFinalHour)
        agEcono.erase(savePos);
    if(controlIterator &&  (checkPossiblePastHour + brg.get_hora_inicio() ) > limitFinalHour)
        agEcono.erase(savePos);
    //salvaguarda todos os casos em que agente economico não é viável a ser visitado, não retornando qualquer agEcono
    if(controlIterator && (checkPossiblePastHour + brg.get_hora_inicio() ) > limitFinalHour)
        return NULL;

    else
        return resV;
}




/**Função para obter agentes económicos tendo em conta tempo de viagem e ou zona limitada por um raio e inspeção entre outras restrições
 *
 * @tparam T
 * @param source
 * @param graph
 * @param autPub
 * @param algorithm
 * @param agEcono
 * @param tmpViagemCounter
 * @param brg
 * @param distOrFullCheck
 * @param GPSCheck
 * @param idNoRadius
 * @return
 */
template <class T>
Vertex<T> *searchNearestAgEconoTmpViagTmpInpecFull(T source, Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,double &tmpViagemCounter,Brigada &brg, bool distOrFullCheck,bool GPSCheck,pair<int,double> idNoRadius){
    double tmpViagemInspec = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(source);
    else if( algorithm == Bellman_Ford)
        graph.bellmanFordShortestPath(source);

    double auxDistOrFullCheck = 0.0;
    if(distOrFullCheck)
        auxDistOrFullCheck = 1.0;


    //Achar vértice central para comparar coordenadas num certo raio
    bool checkCoords = true;
    Vertex<T> *centralV;
    if(GPSCheck){
        centralV = graph.findVertex(idNoRadius.first);
        if(centralV == NULL)
            checkCoords = true; // true para passar nas restrições
    }




    //Variáveis globais usadas para comparações e guardar o agente económico pretendio
    vector<AgenteEconomico *>:: iterator savePos;
    bool controlIterator = false;
    Vertex<T> *resV = NULL;
    //Valor de pontuação de urgência a ser comparado entre agentes Económicos




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

            horaActual = tmpViagemCounter + brg.get_hora_inicio() + distVectV; //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
            auxVal = (distVectV + ((*it)->getTmpInpec() * auxDistOrFullCheck)); //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo

        }else {
            distVectV = v->getDist();
            horaActual = tmpViagemCounter + brg.get_hora_inicio() + distVectV; //Obter hora actual para verificar se inspeção será feita dentro do horário de funcionamento, tendo em conta o tempo de viagem até ao Ag. Econo.
            auxVal = (distVectV  + ((*it)->getTmpInpec() * auxDistOrFullCheck)); //Valor do tempo de viagem até ao Agente económico e inspeção do mesmo
        }



        if(GPSCheck){

            checkCoords = GPSCoordsLimitation((*it)->get_idNo(),*centralV,idNoRadius,graph);


        }


        //controla tmpViagem mínimos caso em que é imposśivel ir de um nó para outro, horários de funcionamento, urgencia de inspeções
        if(tmpViagemInspec >  auxVal && auxVal != INF && horaActual >= (*it)->get_horario_funcionamento().first && horaActual  <= (*it)->get_horario_funcionamento().second && tmpViagemCounter + distVectV  + ((*it)->getTmpInpec() * auxDistOrFullCheck)  <= brg.get_horas_trabalho() && checkCoords ) {

            tmpViagemInspec =  auxVal;
            resV = v;
            savePos = it;
            controlIterator = true;

        }


    }

    if(!distOrFullCheck)
        auxDistOrFullCheck = 1.0;

    double checkPossiblePastHour;
    double limitFinalHour = (brg.get_hora_inicio() + brg.get_horas_trabalho());
    //Verificar se tempos de viagem e inspeções acumuladas ultrapassam o horário de trabalho da brigada em questão
    if(controlIterator) {
        checkPossiblePastHour =tmpViagemInspec + ((*savePos)->getTmpInpec() * auxDistOrFullCheck) + tmpViagemCounter;


        if (tmpViagemInspec < INF && (checkPossiblePastHour + brg.get_hora_inicio()) <= limitFinalHour)
            tmpViagemCounter += tmpViagemInspec + ((*savePos)->getTmpInpec() * auxDistOrFullCheck);
    }
    //apagamos agente economico para o qual ja verificamos ser o mais proximo da uma dada origem de partida e que tem maior urgencia em ser inspecionado e ou cumpre outras restrições
    //apagamos agentes economicos viáveis e que são contabilizados e não viáveis para a mesma rota da mesma brigada
    //Controla se itarador "aponta" para algo ou nao, de forma a conseguir eliminar agentes economicos de agEcono sem erros
    if(controlIterator &&  (checkPossiblePastHour + brg.get_hora_inicio() ) <= limitFinalHour)
        agEcono.erase(savePos);
    if(controlIterator &&  (checkPossiblePastHour + brg.get_hora_inicio() ) > limitFinalHour)
        agEcono.erase(savePos);
    //salvaguarda todos os casos em que agente economico não é viável a ser visitado, não retornando qualquer agEcono
    if(controlIterator && (checkPossiblePastHour + brg.get_hora_inicio() ) > limitFinalHour)
        return NULL;

    else
        return resV;
}



/**Função para achar rotas, generalizando para usar dijktra ou bellman Ford FloydWarshall
 *Necessita sempre que grafo seja constituído por vértices que pertencem à mesma componente fortemente conexa
 * @tparam T
 * @param graph
 * @param brigada
 * @param autPub
 * @return
 */
template <class T>
pair<vector<int>,pair<double,int>> getRotaBrigada(Graph<T> &graph, AutoridadePublica &autPub,AlgorithmMinDist algorithm,vector<AgenteEconomico *> &agEcono,AlgorithmTmpViagInspec algorithmTmpViagInspec,Brigada &brg,bool GPSCheck,pair<int,double> idNoRadius ){
    double tmpViagInspecCounter = 0;
    pair<vector<int>,pair<double,int>> res;
    vector<int> resRotaBrig;
    auto v =  graph.findVertex(autPub.getIdNo());//temos de verificar se autoridade publica  existe no grafo


    if(v!= NULL && agEcono.size()!= 0) {
        // Escolhas das quatro formas de calcular as rotas, : Usando só TmpViagem ou TmpViagem + TmpInspec, TmpViagem + urgencia ou TmpViagem + TmpInspec * urgència
        if(algorithmTmpViagInspec == TmpViag)
            v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false,GPSCheck,idNoRadius);



        else if( algorithmTmpViagInspec == TmpViagInspecFull ){
            v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true,GPSCheck,idNoRadius);

        }
        else if(algorithmTmpViagInspec == TmpViagInspectFullUrgency){
            v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true,GPSCheck,idNoRadius);


        }
        else if(algorithmTmpViagInspec == TmpViagUrgency){
            v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false, GPSCheck,idNoRadius);

        }else {
            v = searchNextUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,GPSCheck,idNoRadius);

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
                v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false,GPSCheck,idNoRadius);



            else if( algorithmTmpViagInspec == TmpViagInspecFull ){
                v = searchNearestAgEconoTmpViagTmpInpecFull(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true,GPSCheck,idNoRadius);

            }
            else if(algorithmTmpViagInspec == TmpViagInspectFullUrgency){
                v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,true,GPSCheck,idNoRadius);


            }
            else if(algorithmTmpViagInspec == TmpViagUrgency){
                v = searchNearestAgEconoTViagTInspecFullUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,false,GPSCheck,idNoRadius);

            }
            else {
                v = searchNextUrgency(v->getInfo(),graph,autPub,algorithm,agEcono,tmpViagInspecCounter,brg,GPSCheck,idNoRadius);

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




/**FUnção para obter se um dado agente económico está dentro de um raio de ação escolhido ou não
 *
 * @tparam T
 * @param idNoAgEcono
 * @param centralVertex
 * @param idNoRadius
 * @param graph
 * @return
 */
template<class T>
bool GPSCoordsLimitation(int idNoAgEcono, Vertex<T> &centralVertex, pair<int,double> idNoRadius,Graph<T> &graph){

    Vertex<T> *vertexToCheck = graph.findVertex(idNoAgEcono);
    if( vertexToCheck != NULL) {
        double distBetweenVertex = centralVertex.getDistLatLong(vertexToCheck->getLocal());

        return distBetweenVertex <= idNoRadius.second;
    }
    return true; // restrições passam sem avaliar no caso de um agEcono não estar no mapa!


}


#endif //EXAMPLE_HEURISTICSFINDROUTE_H

