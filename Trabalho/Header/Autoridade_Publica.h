//
// Created by Amanda  on 12/05/20.
//

#ifndef PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
#define PROJ_GRAFOS_AUTORIDADE_PUBLICA_H


#include "Denuncia.h"
#include "AgenteEconomico.h"
#include "Inspetor.h"

class Autoridade_Publica {

private:
    vector<AgenteEconomico> agentes_economicos;
    vector<Denuncia> denuncias; //todo trocar por um melhor estrutura de dados
    vector<Inspetor> inspetores;


public:
    void get_agentes_economicos();

    vector<AgenteEconomico> set_agente_economico();

    void add_agente_economico();

    vector<Denuncia> get_denuncias();

    vector<Denuncia> set_agente_economico();

    void add_denucia();

    void get_inspetores();

    vector<Inspetor> set_inspetores();

    void add_inspetor();

};


#endif //PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
