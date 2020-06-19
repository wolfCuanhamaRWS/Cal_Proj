//
// Created by flavio on 16/06/20.
//

#ifndef EXAMPLE_HEURISTICSFINDROUTE_H
#define EXAMPLE_HEURISTICSFINDROUTE_H
#include "algorithm"
#include "AutoridadePublica.h"
#include "Graph.h"
#define INF std::numeric_limits<double>::max()

enum Algorithm {dijkstra,Bellman_Ford};

template <class T>
Vertex<T> *searchNearestAgEconoTmpViagem(Graph<T> &graph, AutoridadePublica &autPub,AtividadeEconomica atEcono,Algorithm algorithm){
    double tmpViagem = INF;
    //Aplicação do algoritmo pretendido
    if(algorithm == dijkstra)
        graph.dijkstraShortestPath(autPub.getIdNo());
    else
        graph.bellmanFordShortestPath(autPub.getIdNo());

    Vertex<T> *resV = NULL;
    for(auto agEcono: autPub.get_agentes()) {
        if (agEcono.second->getAtividadeEconomica() == atEcono) {
            auto v = graph.findVertex(agEcono.first);
            if(tmpViagem > v->getDist()) {

                tmpViagem = min(tmpViagem, v->getDist());
                resV = v;
            }
        }

    }

    return resV;
}

/**Função para achar rotas, generalizar para usar dijktra ou bellman Ford
 *
 * @tparam T
 * @param graph
 * @param brigada
 * @param autPub
 * @return
 */
template <class T>
vector<Vertex<T> *> getRotaBrigada(Graph<T> &graph, Brigada &brigada,AutoridadePublica &autPub){
    double counterTmpViagemInspec;
    vector<Vertex<T>> res;
    graph.dijkstraShortestPath(autPub.getIdNo());
    pair<Vertex<T > *, double> aux;
    vector<AgenteEconomico *> agEconoAux;

    //Filtrar
    for(auto agEcono : autPub.get_agentes())
        if(brigada.get_atividades_economicas() == Todas)
            agEconoAux.push_back(agEcono.second);
        else if(brigada.get_atividades_economicas() == agEcono.second->getAtividadeEconomica())
            agEconoAux.push_back(agEcono.second);

    while(counterTmpViagemInspec <= brigada.get_horas_trabalho() || !agEconoAux.empty()) {
        double tmpViagem = INF;
        for (auto agEcon: agEconoAux) {

            Vertex<T> *v = graph.findVertex(agEcon->get_idNo());
            if (  v != NULL  && (brigada.get_hora_inicio() + counterTmpViagemInspec) < agEcon->get_horario_funcionamento().second && (brigada.get_hora_inicio() + counterTmpViagemInspec) >= agEcon->get_horario_funcionamento().first ) {
                if(tmpViagem < v->getDist()) {
                    tmpViagem = v->getDist();
                    aux.first=v;
                    aux.second = tmpViagem;
                }


            }
            if(v != NULL) {
                graph.dijkstraShortestPath(v->getInfo());// novo vértice origem a verificar
                res.push_back(aux.first);
                counterTmpViagemInspec += aux.second;
            }

        }


    }
}


#endif //EXAMPLE_HEURISTICSFINDROUTE_H
