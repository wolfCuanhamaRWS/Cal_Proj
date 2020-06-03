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

class Autoridade_Publica
{

private:
    vector<AgenteEconomico *> agentes_economicos;
    vector<Denuncia *> denuncias;
    vector<Brigada *> brigadas;


public:
    /*
     * Constructor
     * Lê e processa as informações dos ficheiros agente_economico.txt, ...
     */
    Autoridade_Publica();


    //Funções relacionadas com os agentes económicos
    vector<AgenteEconomico *> get_agentes() const;
    void set_agentes(vector<AgenteEconomico *> agentes_economicos);
    void imprimirAgentesEconomicos() const;
    void add_agente_economico(const AgenteEconomico& agente_economico);

    //Funções relacionadas com as denúncias
    vector<Denuncia *> get_denuncias() const;
    void set_denuncias(vector<Denuncia *> &denuncias);
    void add_denuncia(const Denuncia denuncia);

    //Funções relacionadas com as brigadas
    vector<Brigada *> get_brigadas() const;
    void set_brigadas(vector<Brigada *> brigadas);
    void add_brigada(int ID, string especialidade, int hora_comeco, int numero_horas_diario);
    void imprimirBrigadas() const;

};


#endif //PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
