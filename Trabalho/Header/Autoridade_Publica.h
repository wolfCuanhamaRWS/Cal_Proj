#ifndef PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
#define PROJ_GRAFOS_AUTORIDADE_PUBLICA_H

#include <utility>
#include <iostream>
#include <algorithm>
#include <stack>

#include "Denuncia.h"
#include "Brigada.h"
#include "utils.h"
#include "AgenteEconomico.h"

using namespace std;

class Autoridade_Publica {

private:
    vector<AgenteEconomico *> agentes_economicos;
    vector<Denuncia *> denuncias;
    vector<Brigada *> brigadas;


public:
    /*
     * Constructor
     * Lê e processa as informações dos ficheiros agente_economico.txt, ...
     * informacoes do ficheiro sao processadas em funcoes separadas
     */
    Autoridade_Publica();


    //Funções relacionadas com os agentes económicos
    vector<AgenteEconomico *> get_agentes() const;

    void set_agentes(vector<AgenteEconomico *> agentes_economicos);

    void imprimirAgentesEconomicos() const;

    void read_agente();

    void
    add_agente_economico(int ID, string nome, float area, pair<int, int> horario_funcionamento, set<int> ids_denuncias,
                         vector<string> atividades_economicas, set<pair<int, string>> inspecoes, long double latitude,
                         long double longuitude);


    //Funções relacionadas com as denúncias
    vector<Denuncia *> get_denuncias() const;

    void set_denuncias(vector<Denuncia *> &denuncias);

    void read_denuncias();

    void write_denuncia();

    void add_denuncia(int id, int id_agente, int gravidade, string especialidade);

    bool id_valido(int id);


    //Funções relacionadas com as brigadas
    vector<Brigada *> get_brigadas() const;

    void set_brigadas(vector<Brigada *> brigadas);

    void read_brigada();

    void add_brigada(int ID, string especialidade, int hora_comeco, int numero_horas_diario);

    void imprimirBrigadas() const;


};


#endif //PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
