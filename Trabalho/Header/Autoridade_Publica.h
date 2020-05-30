#ifndef PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
#define PROJ_GRAFOS_AUTORIDADE_PUBLICA_H


#include "Denuncia.h"
#include "AgenteEconomico.h"
#include "Inspetor.h"

using namespace std;

class Autoridade_Publica {

private:
    vector<AgenteEconomico *> agentes_economicos;
    vector<Denuncia *> denuncias; //todo trocar por um melhor estrutura de dados
    vector<Inspetor *> inspetores;


public:
    Autoridade_Publica(); //constructor

    void set_agentes_economicos(vector<AgenteEconomico *> agentes_Economicos);

    vector<AgenteEconomico *> get_agente_economicos();

    void add_agente_economico(const AgenteEconomico &agenteEconomico);

    vector<Denuncia *> get_denuncias();

    void set_denuncias(vector<Denuncia *> &denuncias);

    void add_denucia(const Denuncia denuncia);

    vector<Inspetor *> get_inspetores();

    void set_inspetores(vector<Inspetor *> inspetores);

    void add_inspetor(const Inspetor &inspetor);

};


#endif //PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
