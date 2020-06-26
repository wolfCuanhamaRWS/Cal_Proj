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
#include "algorithm"
#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stack>
#include "MutablePriorityQueue.h"
#include "Local.h"
#include <stdio.h>
#include <climits>
#include "math.h"

#define PI 3.14159265358979323846
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

enum Tag {AutPub,AgEcono, Other};

template <class T>
class Vertex {

	T info;
	vector<Edge<T> > adj;		// outgoing edges
    Local local;                // Classe Local com (x,y) e longitude e latitude para usar no graphView e calcular tempos distancias/tempos de viagem
	Tag type = Other;
	double dist = 0;
	Vertex<T> *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	Local getLocal() const;
	void  setLocal(Local &local);

	Vertex(T in, Local &local){
	    this->info = in;
	    this->local =local;

	}
    vector<Edge<T> > getEdges(){return adj;}
	T getInfo() const;
    /**Função utilizada para obter tempo de viagem entre dois locais usando longitude e latitude
	 *
	 *
	 * @param dest Local de destino
	 * @param velocKmH velocidade média de um veículo
	 * @return valor do tempo de viagem
	 */
    double getTempViagem(Local dest ,double velocKmH);

    void setInfo(T info){this->info = info;}
    Tag getTagType() const;
    void setTagType(Tag type);
	double getDist() const;
	Vertex *getPath() const;
    void setDist(double dist);
    void setPath(Vertex<T> &path);
    bool getVisited(){ return visited;}
    Local getLocal(){return local;}
    void setVisited(bool visited){ this->visited = visited;}
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue comparam fields dist
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;

};

template<class T>
double Vertex<T>::getTempViagem( Local dest,double velocKmH) {
    //Factor multiplicação para obter distancia
    double deg2radMultiplier = PI / 180;
    //Local origem
    double lat1 = local.get_latitude() * deg2radMultiplier;
    double long1 = local.get_longitude() * deg2radMultiplier;
    //Local Destino
    double lat2 = dest.get_latitude() * deg2radMultiplier;
    double long2 = dest.get_longitude() * deg2radMultiplier;


    double radius = 6378.137; // earth mean radius defined by WGS84
    double dlon = long2 - long1;
    double result = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(dlon)) * radius;

    result = result / velocKmH;
    return result;

}


template <class T>
Local Vertex<T>:: getLocal() const { return local ;}

template <class T>
void Vertex<T>:: setLocal(Local &local){
    this->local = local;
}

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Tag Vertex<T>:: getTagType() const {return type;}


template <class T>
void Vertex<T>:: setTagType(Tag type)  {this->type = type;}


/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back( Edge<T>(d, w));
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
    double getWeight(){return weight;}
	Vertex<T> *getDest(){return dest;}
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {

    double ** W = nullptr; // dist
    int **P = nullptr; // path



    vector<Vertex<T> *> vertexSet;    // vértices para guardar Locais
    vector<vector<double>> distMin; //Matriz para algoritmo FloyWarshall e não só
    int MaxIdNo = (std::numeric_limits<double>::min() -1)* - 1;
    vector<vector<Vertex<T> *>> pathMin; //Matriz para algoritmo FloydWarshall e não só
    double minXGraphView = std::numeric_limits<double>::max();
    double maxXGraphView = (std::numeric_limits<double>::min() - 1) * -1;
    double numberOfEdges = 0;
    double minYGraphView = std::numeric_limits<double>::max();
    double maxYGraphView = (std::numeric_limits<double>::min() - 1) * -1;


public:
    //Graph();
    vector<vector<Vertex<T> *>> getPathMin() { return pathMin; }
    int findVertexIdx(const T &in) const;
    vector<vector<double>> getDistMin() { return distMin; }

    int getNumberOfEdges() const { return numberOfEdges; }

    void setNumberOfEdges(double numbOfEdg) { numberOfEdges = numbOfEdg; }

    double getMinXGraphView() const { return minXGraphView; }

    void setMinXGraphView(double minX) { minXGraphView = minX; }

    double getMinYGraphView() const { return minYGraphView; }

    void setMinYGraphView(double minY) { minYGraphView = minY; }

    double getMaxXGraphView() const { return maxXGraphView; }

    void setMaxXGraphView(double maxX) { maxXGraphView = maxX; }

    int getMaxYGraphView() const { return maxYGraphView; }

    void setMaxYGraphView(double maxY) { maxYGraphView = maxY; }
    void  controlCoordsGraphView(double x, double y);

    int getMaxId(){
        return MaxIdNo;
    }

    Vertex<T> *findVertex(const T &in) const;

    bool addVertex(const T &in);

    bool addCompleteVertex(Vertex<T> *aux) {
        controlCoordsGraphView(aux->getLocal().get_xMap(),aux->getLocal().get_yMap());
        MaxIdNo = max(MaxIdNo, aux->getInfo());
        if (findVertex(aux->getInfo()) != NULL)//só adicionamos se vértice não existir
            return false;

        this->setNumberOfEdges(aux->getEdges().size() + getNumberOfEdges());

        vertexSet.push_back(aux);
        return true;


    }

	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

    bool relax(Vertex<T> *vOrig, Vertex<T> *wDest, double edgeValue);
	void unweightedShortestPath(const T &origin);
	void dijkstraShortestPath(const T &origin);
	void bellmanFordShortestPath(const T &orig);
	vector<T> getPathTo(const T &dest) const;

	// Distancia mínima entre  todos os pares de vértices para guardar numa tabela de pré-processamento


    vector<T> getfloydWarshallPath(const T &orig, const T &dest) const;
    void floydWarshallShortestPath(unsigned int indexStartidNodes, double errorEPS);
    vector<T> bfs(const T &source) const;


    void dfsVisit(Vertex<T> *v, vector<T> &res) const;


    vector<T> dfs() const;
    void increasingTimeOrder(Vertex<T> *vertex, stack<Vertex<T> *> &stackVertex);
    Graph<T > getInverseEdgesGraph();
    vector<vector<T>> KosarajuMainAlgo();
    void saveStrongCC(Vertex<T> *v,vector<T> &saveSSC);
    vector<T> KisorajuGetMaxSizeStrongCC(Graph<T> graph);

    bool removeVertex(const T &in);

};

template<class T>
void  Graph<T>::controlCoordsGraphView(double x, double y){
    if(this->getMinXGraphView() >= x)
        this->setMinXGraphView(x);

    if(this->getMaxXGraphView() <= x){
        this->setMaxXGraphView(x);
    }

    if(this->getMaxYGraphView() <= y)
        this->setMaxYGraphView(y);

    if(this->getMinYGraphView() >= y)
        this->setMinYGraphView(y);

}


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
	return nullptr;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
   /* int size = vertexSet.size();
    MaxIdNo = max(MaxIdNo, size);
    MaxIdNo = max(MaxIdNo, in);*/

	if ( findVertex(in) != nullptr)
		return false;
	else {
        vertexSet.push_back(new Vertex<T>(in));


        return true;
    }
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
	if (v1 == nullptr|| v2 == nullptr)
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

/**FUNÇÃO que verifica relaxamento em relação a uma aresta ,
 * tendo emconta algoritmos de camminho mais curto como Dijkstra etc
* Avalia se valor acumulado até wdest para suposta distancia minima usando por exemplo Dijktra
 * é maior que o valor acumulado até vOrig + peso da aresta edgeValue até wDest
 * Se maior, encontramos um caminho com vOrig como antecessor de wDest com pesos acumulados de arestasm menos
 * do que até agora temos guardado em wDest->dist
 * @tparam T
 * @param v Vértice origem da aresta a ser avaliada
 * @param w Vértice destino de aresta a ser avaliada
 * @param weight valor da aresta entre vértices v e w
 * @return true
 */
template<class T>
bool Graph<T>::relax(Vertex<T> *vOrig, Vertex<T> *wDest, double edgeValue) {
    if (wDest->dist > vOrig->dist + edgeValue ) { //avalia valores minimos acumulados até vértice wDest
        wDest->dist = vOrig->dist + edgeValue; // se valor actual acumulado até wDest menor que valor acumulado até vorig + eddgeValue(até wDest)
        wDest->path = vOrig; // actualizamos valor distMin que estaamos a procurar até vértice wDest, com vértice antecessor vOrig guardado em wDest->path
        return true;
    }
    else
        return false;
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

    for(auto v: this->vertexSet){ // inicializar valores para usar algoritmos
        v->dist = INF;
        v->path = nullptr;
       
        //não é necessário para o que queremos, mas até dá uma boa ideia do que se passa no código, utilizando
       // v->processing = false;
       // v->visited = false;
    }
    Vertex<T> *originV = findVertex(origin);//vértice inicial
    originV->dist= 0;//distancia do vértice de origem escolhido a ele próprio é zero!Importante

    MutablePriorityQueue<Vertex<T> > min_priority_queue;//fila com vértices, onde estes têm field indexqueue!


    min_priority_queue.insert(originV);//apontador para vértice é passado na função

    // vértice de origem  a ser processado/está na fila de prioridade//desnecessário
   //originV->processing = true;

    while(!min_priority_queue.empty()){

        //greedy strategy
        auto auxV = min_priority_queue.extractMin();//obter vértice extraído da fila de prioridade mutável
       // auxV-> visited = true;
        //verificar vértices nas arestas de v, de forma a comparar pesos de arestas e tamanho de caminhos acumulados
        for(auto wDest :auxV->adj){ // verificar arestas e vértices destino das memas
            /**dist(w) acumulada ao vértice origem é infinita ou maior que a dist(v) acumulada desde a origem(vértice escolhido)
             * até vértice v +  o peso da aresta entre vértice v e w
             * Logo, há um caminho desde a origem até vértice w passando pelo vértice antecessor v que é mais curto
             * Fazendo a devida actualização da dist(w)->Ver numenclatura usada nas teóricas!
             */
            auto pastDist = wDest.dest->dist;//distancia acumulada desde a origem até vértice w para verificar caso do ser infinito->não está na fila de prioridade

            if(relax(auxV,wDest.dest,wDest.weight)) {
                 if (pastDist == INF) { //dist acumulada do vértice adjacente a auxV da aresta era INFINITO-> esse vértice ainda não está na fila de prioridade mutável
                     min_priority_queue.insert(wDest.dest); //primeira vez que "passamos aqui" ao "explorar" grafo
                    // wDest.dest-> processing = true;
                     //(*w)->dest->processing = true;//estamos a processar este vértice, visto que foi introduzido na fila de prioridades(desnecessário)

                 }
                    //vértice da aresta já existe na fila, logo tem de ver a sua prioridade na fila alterada/diminuída,pois vertice w passa a fazer parte de
                    //caminho mais curto
                else {
                    min_priority_queue.decreaseKey(wDest.dest);
                }

            }

        }

    }
        //desnecessário
     //   Wdest.dest->visited = true; //vector já foi "visitado" visto que já processamos todas as arestas/vértices adjacentes deste para  fila de prioridade
                            //e actualizamos todas as dist acumuladas/path em relação aos seus vértices adjacentes!
}

/**Permite existência de arestas negativas
 *
 * @tparam
 * @param orig
 */
template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
    for(Vertex<T> *v : vertexSet){
        v->dist = INF;
        v->path = NULL;
      //  v->visited = false;//não é necessário
       // v->processing = false;//não é necessário

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
    if( aux == nullptr || aux->dist == INF)// se vértice não existir ou for desconectado após se chamar algorimto de rotams mínimas de uma origem para todos os outros (dijktra etc)
        return res; // retorna vetor vazio

    stack<T> getPath;//uso de pilha para ordem que queremos
    getPath.push(aux->getInfo());

    //vou guardando os vértices antecessores desde o vértice dest até à origem
    //Origem terá dist == 0
    while (aux != nullptr) { //chegámos ao fim



    res.push_back(aux->getInfo());
    aux = aux->getPath();//próximo vector, que é  antecessoer do vertice aux actual tendo sido um algoritmo de caminho mínimo de uma origem para todos os outros vértices

    }

    /*
    while (!getPath.empty()){//guardar path desde origem até dest por esta ordem
        res.push_back(getPath.top());
        getPath.pop();
    }
*/
    reverse(res.begin(),res.end());
    
	return res;
}
/**************** All Pairs Shortest Path  ***************/

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    vector<T> res;
    Vertex<T> *v = pathMin[orig][dest];


    res.push_back(dest);

    while(v->getInfo() != orig){
        res.push_back(v->getInfo());
        v = pathMin[orig][v->getInfo()];


    }
    res.push_back(orig);
    // res.push_back(orig);//push no final da orig, pois usamos orig como condição no ciclo while
    //quando chegamos à origem já percorremos o caminho mais curto entre dest e orig

    reverse(res.begin(),res.end());//trocar ordem dos elementos de vector pra termos: orig->w->v->...dest
    return res;

}
/**Função que calcula distancias mínimas entre cada par de vértices
 * Possibilita o uso de numeração de vértices começando por 0 ou por 1
 * Ter sempre em conta, que numeração de nós  por ordem crescente, 1 em 1 possibilita
 * aceder a nós de forma mais rápida , daí o algoritmo ser usado tendo sempre antes de ter
 * essa forma de numeração
 * @tparam T
 * @param indexStartidNodes valores 0 ou 1 consoante o identificação de vértices pretenidade
 * @param errorEPS erro pretendido que queremos que seja tido em conta
 */
template<class T>
void Graph<T>::floydWarshallShortestPath(unsigned int indexStartidNodes, double errorEPS) {

    if(indexStartidNodes< 0 || indexStartidNodes > 1) {
        cerr << "Valor para ajustar indíce do vetor com nós incorreto" << endl;
        return;
    }
   // if(minXGraphView == 0)
    //inicializar matriz de adjacencias
    //Iteração k = 0, onde  k>= 0 && k <= numberVertex
    int numbVertex = getNumVertex();

    //matriz para as distancias do algoritmo floyd warshal
    distMin = vector<vector<double>>(numbVertex + indexStartidNodes,vector<double>(numbVertex + indexStartidNodes,INF));
    //vector para guardador predecessores de vertices e assim obter os nós/vértices do caminho mais curto pretendido
    pathMin = vector<vector<Vertex<T> *>>(numbVertex + indexStartidNodes,vector<Vertex<T>*>(numbVertex + indexStartidNodes,NULL));

    //Incializar matrizes com os valores adjacentes iniciais do grafos/distancias entre vértices
    // por apenas uma aresta de distancia.
    //vértices sem arestas entre si, ficam com distancia infinita!
    for(int i = indexStartidNodes; i < numbVertex + indexStartidNodes; i++)
        for(int j = indexStartidNodes; j < numbVertex + indexStartidNodes; j++){
            if( i == j) {
                distMin[i][j] = 0;//distancia Minima de um nó para si próprio
                // o predecessor do caminho de um nó para si próprio é nulo
            }
            //predecessores iniciais, tendo em conta informações de arestas do grafo
            //distancias minimas iniciais inicializas com os pesos de arestas que ligam vértices directamente com apenas uma aresta
            Vertex<T> *w = vertexSet[i -indexStartidNodes];
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
    //ao iterar todos os caminhos entre i, j tendo em conta todos os vértices intermédios possíveis
    //Ficamos com as disMin entre qualquer vértice e predecessores nesses caminhos
    for(int k = indexStartidNodes; k < numbVertex + indexStartidNodes; k++){//vértices intermédios a serem verificados entre caminhos i, j
        for(int i = indexStartidNodes; i < numbVertex + indexStartidNodes; i++)
            for(int j = indexStartidNodes; j < numbVertex + indexStartidNodes; j++) {
                //Se distMin entre i e j menor que a distMin passando pelo veŕtice k
                //esse vértice pertence ao caminho mais curto que pretendemos
                if(distMin[i][k] != INF &&
                   distMin[k][j] != INF &&  (distMin[i][j]  - errorEPS) > distMin[i][k] + distMin[k][j]){//TEnta-se evitar propagação de erros usando valor escolhido
                    distMin[i][j] = distMin[i][k] + distMin[k][j];
                    //predecessor no caminho entre i e j é vértice intermédio k (= 1,2,...n)
                    pathMin[i][j] = pathMin[k][j];
                }


            }
    }


}

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

    if(aux!= nullptr) {
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
/**
 *
 * @tparam T
 * @return
 */
template <class T>
void Graph<T> :: saveStrongCC(Vertex<T> *v, vector<T> &saveSSC) {
    v->setVisited(true);

    saveSSC.push_back(v->getInfo());

    for(Edge<T> adjV: v->adj )
        if(adjV.dest->getVisited() == false){
            saveStrongCC(adjV.dest,saveSSC); // chamda recursiva para ir obetendo todos os SCC
        }
}

template <class T>
void Graph<T> :: increasingTimeOrder(Vertex<T> *vertex, stack<Vertex<T> *> &stackVertex){
    vertex->setVisited(true);
    for(Edge<T> v: vertex->adj){
       if( v.dest->getVisited() == false)
           increasingTimeOrder(v.dest, stackVertex);
    }

    stackVertex.push(vertex);
}

/**Funções para obter todas as componentes fortemente conexas de um grafo
 * Algortimo Kosaraju
 */

/**
 *
 * @tparam T
 * @return
 */
template <class T>
Graph<T> Graph<T> :: getInverseEdgesGraph(){
    Graph<T> inverseEdgesGraph;
    for(auto v: vertexSet){

        inverseEdgesGraph.addVertex(v->getInfo());

    }


    for(Vertex<T> *v: vertexSet){

        for(Edge<T>  w: v->adj){
            inverseEdgesGraph.addEdge(w.getDest()->info,v->info,w.getWeight());
        }

    }
    return inverseEdgesGraph;
}
/**
 *
 * @tparam T
 * @return
 */
template <class T>
vector<vector<T>> Graph<T> :: KosarajuMainAlgo(){

    vector<vector<T> > saveAllSCC;
    stack<Vertex<T> *> stackVertex;

    //meter todos os veŕtices como não visitados
    for(auto v: vertexSet){
            v->setVisited(false);
    }


    for(auto v: vertexSet){
        if(v->getVisited() == false)
        increasingTimeOrder(v, stackVertex);
    }

    Graph<T> transpGraph = getInverseEdgesGraph();
    // todos os vértices como não visitados para segunda pesquisa em profundidade
    for(auto v: transpGraph.vertexSet){
        v->setVisited(false);
    }
    for(auto v: vertexSet){
        v->setVisited(false);
    }
    while(!stackVertex.empty()){
        vector<T> singleSCC;


        Vertex<T> *v = transpGraph.findVertex(stackVertex.top()->info);
        stackVertex.pop();
       // auto w = findVertex(v->getInfo());
        if(v->getVisited() == false) {
            transpGraph.saveStrongCC(v, singleSCC);


            saveAllSCC.push_back(singleSCC);
           // singleSCC.clear();
        }
    }

    return saveAllSCC;

}

template<class T>
vector<T> Graph<T>:: KisorajuGetMaxSizeStrongCC(Graph<T> graph){
    vector<T> res;
    vector<vector<T>> auxRes = graph.KosarajuMainAlgo();
    for(auto v: auxRes) {
        if (v.size() > res.size())
            res = v;
    }
    return res;
}
#endif /* GRAPH_H_ */
