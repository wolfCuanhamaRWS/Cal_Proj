/*Flavio 06/06/2020
 * Reutilização de:
 * Algoritmos e funções resolvidos e testados referentes à aula Prática
 * Graph.h
 *
 *
 *
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
    void setDist(double dist);
    void setPath(Vertex<T> &path);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue comparam fields dist
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
	 vector<Vertex<T> *> vertexSet;    // vertex set
	 vector<vector<double>> distMin;

	 vector<vector<Vertex<T>*>>  pathMin;


public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &origin);    //TODO...
	void dijkstraShortestPath(const T &origin);      //TODO...
	void bellmanFordShortestPath(const T &orig);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...
    //ex3-)b

    vector<T> bfs(const T &source) const;


    void dfsVisit(Vertex<T> *v, vector<T> &res) const;


    vector<T> dfs() const;


    bool removeVertex(const T &in);
};




template<class T>
void Vertex<T>::setDist(double dist) {
    this->dist = dist;
}

template<class T>
void Vertex<T>::setPath(Vertex<T> &path) {
    this->path = path;
}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));


	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    //actualizar matriz, pois nos testes adicionamos sempre todos os vértices primeiro
    // e depois adicionamos as arestas(estando o número de vértices já totalmente definido

    auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/
/**Grafo dirigido não pesado(ignorar pesos das arestas)(sem peso nas arestas/pesos ==1
 *O número de arestas é que incdica tamanho do caminho mínimo pretendido
 * Actualizar caminhos para cada vértice apartir de um vértice de origem para todos os outros
 *Usar método básico: bfs + cálculo de distâncias
 * @tparam T
 * @param orig
 */
template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	// TODO
    Vertex<T> *initialV = findVertex(orig);

    double nill = std::numeric_limits<double>::max();
    //1
    for (auto w: vertexSet) {
        w->dist = nill;//O nosso infinito
        w->visited = false;
    }

    //Usar fila FIFO para novos vértices alcançados/vértice inicial
    queue<Vertex<T>*> bfsV;//usa-se isto para ir obtendo vértices em que teremos de marcar como visitado e explorar os vertices adjacentes
    initialV->dist = 0;

    bfsV.push(initialV);


    //fila permite ir acumulando para cada w vértice,  as distencias desde aux vértice já processado
    while(!bfsV.empty()){
        Vertex<T> *aux = bfsV.front();//vértice a ser explorado
        bfsV.pop();//vértice processado

        //guardamos informação de vertice já explorado num vector, sendo assim os vértices mostrados por pesquisa em largura
        //exploramos os vértices possíveis adjacentes ao vértice atrás processado
        for(auto w: aux->adj){//para cada vertice adjacente de w (vamos às arestas (Edge) de w)
            if(w.dest->dist == nill) {//vamos ver aqueles vértices que ainda não foram processados

                bfsV.push(w.dest);//próximos vértices em que vamos explorar vértices adjacentes
               //actualizamos distencias desde o vértice dado inicial até os vértices w
                //usando bfs garantimos ordem pretendida
                w.dest->dist = aux->dist + 1;
                w.dest->path = aux;//guarda vértice antecedente (começando num vértice qualquer inicial até este)
            }
        }


    }




}

/**Parecido com o caso grafo dirigido sem pesos, mas agora arestas têm peso!
 *Sem pesos negativos
 * Algoritmo ganancioso Com uso de filas de prioridade alteráveis (mínimo á cabeça)
 * Usar Fibonacci Heaps para que "Decrease-key " seja feito em tempo amortizado O(1)!
 * Fazer refactor do código, usando variáveis auxiliares para buscar vértices das arestas
 * Correr ciclos fazendo "cast" para o que sabemos que vamos iterar(arestas por exemplo)
 * @tparam T
 * @param origin
 */
template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	// TODO

    for(auto v: this->vertexSet){
        v->dist = INF;
        v->path = NULL;
        //não é necessário para o que queremos, mas até dá uma boa ideia do que se passa no código, utilizando
        v->processing = false;
        v->visited = false;
    }
    Vertex<T> *originV = findVertex(origin);//vértice inicial
    originV->dist= 0;//distancia do vértice de origem escolhido a ele próprio é zero!Importante

    MutablePriorityQueue<Vertex<T> > min_priority_queue;//fila com vértices, onde estes têm field indexqueue!


    min_priority_queue.insert(originV);//apontador para vértice é passado na função

    originV->processing = true;//vértice de origem  a ser processado/está na fila de prioridade//desnecessário
    while(!min_priority_queue.empty()){

        //greedy strategy
        Vertex<T> *auxV = min_priority_queue.extractMin();//obter vértice extraído da fila de prioridade mutável

        //verificar vértices nas arestas de v, de forma a comparar pesos de arestas e tamanho de caminhos acumulados
        for(auto w = auxV->adj.begin(); w != auxV->adj.end(); w++){
            /**dist(w) acumulada ao vértice origem é infinita ou maior que a dist(v) acumulada desde a origem(vértice escolhido)
             * até vértice v +  o peso da aresta entre vértice v e w
             * Logo, há um caminho desde a origem até vértice w passando pelo vértice antecessor v que é mais curto
             * Fazendo a devida actualização da dist(w)->Ver numenclatura usada nas teóricas!
             */
            if((*w).dest->dist > auxV->dist + (*w).weight ){
                double auxINF =(*w).dest->dist;//distancia acumulada desde a origem até vértice w para verificar caso do ser infinito->não está na fila de prioridade

                (*w).dest->dist = auxV->dist + (*w).weight;
                (*w).dest->path = auxV;//vértice anterior deste vértice do caminho será auxV




                //primeira vez que "passamos aqui" ao "explorar" grafo
                if(auxINF == INF) {//dist acumulada do vértice adjacente a auxV da aresta era INFINITO-> esse vértice ainda não está na fila de prioridade mutável
                    Vertex<T> *auxDestVFromAdj = (*w).dest;

                    min_priority_queue.insert(auxDestVFromAdj);//mesma explicação de porquê usar , assim passo apontador
                    auxDestVFromAdj->processing = true;//estamos a processar este vértice, visto que foi introduzido na fila de prioridades
                }


                //vértice da aresta já existe na fila, logo tem de ver a sua prioridade na fila alterada/diminuída,pois vertice w passa a fazer parte de
                //caminho mais curto
                else {
                    Vertex<T> *auxDestVFromAdj = (*w).dest;
                    //Alterando indíces do vértice  na fila de prioridade
                    min_priority_queue.decreaseKey(auxDestVFromAdj);

                }
            }

        }
        //desnecessário
        auxV->visited = true; //vector já foi "visitado" visto que já processamos todas as arestas/vértices adjacentes deste para  fila de prioridade
                            //e actualizamos todas as dist acumuladas/path em relação aos seus vértices adjacentes!
    }


}



/**Permite existência de arestas negativas
 *
 * @tparam T
 * @param orig
 */
template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
    for(Vertex<T> *v : vertexSet){
        v->dist = INF;
        v->path = NULL;
        v->visited = false;//não é necessário
        v->processing = false;//não é necessário

    }

    Vertex<T> *sOrigSearch = findVertex(orig);
    sOrigSearch->dist = 0;
    /**No mínimo temos uma aresta entre um vértice source e um dest qualquer
     * no Máximo temos V -1 arestas entre um vértice source e dest
     *
     */
    for(int i = 1; i < vertexSet.size() - 1; i++){//número máximo de arestas entre um vértice e outro

        for(Vertex<T> *v: this->vertexSet) {//iterar vértices

            for (Edge<T> w :v->adj) {//arestas no vértive v

                if (w.dest->getDist() > v->getDist() + w.weight) {
                    w.dest->setDist(v->getDist() + w.weight);
                    w.dest->path = v;
                }

            }
        }
    }

    //Verificar ciclos de peso negativo
    for(Vertex<T> *v:this-> vertexSet) {
        for(Edge<T> w: v->adj) {
            if (v->getDist() + w.weight < w.dest->getDist()) {
                cout << "there are cycles of negative weight\n";
                return;//fail
            }
        }
    }






}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const {
    vector<T> res;
    // TODO

    Vertex<T> *aux = findVertex(dest);
    stack<T> getPath;//uso de pilha para ordem que queremos
    getPath.push(aux->getInfo());

    //vou guardando os vértices antecessores desde o vértice dest até à origem
    //Origem terá dist == 0
    while (aux->getDist() != 0) {

        aux = aux->getPath();//próximo vector, que é  antecessoer do vertice aux actual
        getPath.push(aux->getInfo());//guardar info do vertice

    }
    while (!getPath.empty()){//guardar path desde origem até dest por esta ordem
        res.push_back(getPath.top());
        getPath.pop();
    }


	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
    // TODO

    //inicializar matriz de adjacencias
    //Iteração k = 0, onde  k>= 0 && k <= numberVertex
    int numbVertex = getNumVertex();
    /**Usaremos indíces de 1 até numVertex para bater certo com a numeração normalmente usada para os nós, onde
     * onde se numera os nós de 1 até n ,evita ter de usar i +1, j + 1
     *
     */
    //matriz para as distancias do algoritmo floyd warshal
    distMin = vector<vector<double>>(numbVertex +1,vector<double>(numbVertex + 1,INF));
    //vector para guardador predecessores de vertices e assim obter os nós/vértices do caminho mais curto pretendido
    pathMin = vector<vector<Vertex<T> *>>(numbVertex + 1,vector<Vertex<T>*>(numbVertex + 1,NULL));

    //Incializar matrizes com os valores adjacentes iniciais do grafos/distancias entre vértices
    // por apenas uma aresta de distancia.
    //vértices sem arestas entre si, ficam com distancia infinita!
    for(int i = 1; i < numbVertex + 1; i++)
        for(int j = 1; j < numbVertex + 1; j++){
            if( i == j) {
                distMin[i][j] = 0;//distancia Minima de um nó para si próprio
                // o predecessor do caminho de um nó para si próprio é nulo
            }
            //predecessores iniciais, tendo em conta informações de arestas do grafo
            //distancias minimas iniciais inicializas com os pesos de arestas que ligam vértices directamente com apenas uma aresta
            Vertex<T> *w = vertexSet[i -1];
            for(Edge<T> v: w->adj)

                if(v.dest->getInfo() == j) {
                    distMin[i][j] = v.weight;

                }
            //se temos dist <INF entre vertice i, j separados por uma aresta
            // o predecessor neste caso é o vector i
            if(distMin[i][j] < INF)
                pathMin[i][j] = w;
        }


    //Aqui, usando programação dinâmica iremos obter as distancias minimas entre vértice orig e dest pretendido!
    /**Para qualquer par de vértices {\displaystyle (i,j)}(i,j)
     * em {\displaystyle V}V, considere todos os caminhos de {\displaystyle i}i
     * a {\displaystyle j}j cujos vértices intermédios pertencem ao subconjunto
     * {\displaystyle {1,2,3\ldots ,k}}{1,2,3\ldots ,k}, e {\displaystyle p}p como
     * o mais curto de todos eles;
O algoritmo explora um relacionamento entre o caminho {\displaystyle p}p e os
     caminhos mais curtos de {\displaystyle i}i a {\displaystyle j}j com todos
     os vértices intermédios em {\displaystyle {1,2,3\ldots ,k-1}}{1,2,3\ldots ,k-1};
O relacionamento depende de {\displaystyle k}k ser ou não um vértice intermédio
     do caminho {\displaystyle p}p.
     *https://pt.wikipedia.org/wiki/Algoritmo_de_Floyd-Warshall
     *
     *
     */

    for(int k = 1; k < numbVertex + 1; k++){//vértices intermédios a serem verificados entre caminhos i, j
        for(int i = 1; i < numbVertex + 1; i++)
            for(int j = 1; j < numbVertex + 1; j++) {
                //Se distMin entre i e j menor que a distMin passando pelo veŕtice k
                //esse vértice pertence ao caminho mais curto que pretendemos
                if(distMin[i][j] > distMin[i][k] + distMin[k][j]){
                    distMin[i][j] = distMin[i][k] + distMin[k][j];
                    //predecessor no caminho entre i e j é vértice intermédio k (= 1,2,...n)
                    pathMin[i][j] = pathMin[k][j];
                }


            }
    }
    //ao iterar todos os caminhos entre i, j tendo em conta todos os vértices intermédios possíveis
    //Ficamos com as disMin entre qualquer vértice e predecessores nesses caminhos

}
template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
    Vertex<T> *v = pathMin[orig][dest];


    res.push_back(dest);

    while(true){
        res.push_back(v->getInfo());
        v = pathMin[orig][v->getInfo()];
        if(v->getInfo() == orig)
            break;
    }

    res.push_back(orig);//push no final da orig, pois usamos orig como condição no ciclo while
    //quando chegamos à origem já percorremos o caminho mais curto entre dest e orig
    reverse(res.begin(),res.end());//trocar ordem dos elementos de vector pra termos: orig->w->v->...dest
    return res;


}



/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    // TODO (10 lines)
    // HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
    // HINT: take advantage of "removeEdgeTo" to remove incoming edges.
    //Temos de eliminar arestas in and out para este vertice
    Vertex<T> *aux = this->findVertex(in);//Obter apontador para o apontador do vertice pretendido

    if(aux!= NULL) {
        for(auto it = this->vertexSet.begin(); it != this->vertexSet.end(); it++) {
            (*it)->removeEdgeTo(aux);//remover arestas de outros vertices para o vertice que vamos apagar

        }
        //apagar vértice do grafo
        for (auto it = this->vertexSet.begin(); it != this->vertexSet.end(); it++) {
            if((*it)->info == in) {//iterador é apontador para um apontador de um vértice dentro do vecttor de apontadores de vértices usando Template
                this->vertexSet.erase(it);//apagamos vértice
                it--;//é desnecessário
                break;
            }
        }
        return true;
    }
    else return false;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
    // TODO (7 lines)
    vector<T> res;

    for(auto it = this->vertexSet.begin(); it != this->vertexSet.end(); it++) {
        (*it)->visited = false;


    }

    for(auto it = this->vertexSet.begin(); it != this->vertexSet.end(); it++)
        if((*it)->visited == false)
            dfsVisit((*it), res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    // TODO (7 lines)
    v->visited = true;
    res.push_back(v->info);
    for(auto it = v->adj.begin(); it != v->adj.end(); it++){
        if( (*it).dest->visited == false)
            dfsVisit(it->dest,res);



    }



}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 *
 * Queues are a type of container adaptors which operate in a first
 * in first out (FIFO) type of arrangement. Elements are inserted at
 * the back (end) and are deleted from the front.
 * Pesquisa em largura (breadth-first search)
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    // TODO (22 lines)
    vector<T> res;
    // HINT: Use the flag "visited" to mark newly discovered vertices .
    // HINT: Use the "queue<>" class to temporarily store the vertices.
    //https://www.geeksforgeeks.org/queue-cpp-stl/
    queue<Vertex<T>*> bfsV;//usa-se isto para ir obtendo vértices em que teremos de marcar como visitado e explorar os vertices adjacentes

    for(auto v: this->vertexSet)
        v->visited = false;
    bfsV.push(findVertex(source));



    while(!bfsV.empty()){
        Vertex<T> *aux = bfsV.front();//vértice a ser explorado
        bfsV.pop();//vértice processado/visitado
        aux->visited = true;
        res.push_back(aux->info);//guardamos informação de vertice já explorado num vector, sendo assim os vértices mostrados por pesquisa em largura
        //exploramos os vértices possíveis adjacentes ao vértice atrás processado
        for(auto w: aux->adj){//para cada vertice adjacente de w (vamos às arestas (Edge) de w)
            if(!(w.dest->visited))

                bfsV.push(w.dest);//próximos vértices em que vamos explorar vértices adjacentes e marcar como visitado


        }


    }


    return res;
}




#endif /* GRAPH_H_ */
