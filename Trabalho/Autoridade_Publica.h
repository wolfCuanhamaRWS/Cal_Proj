//
// Created by Amanda  on 12/05/20.
//

#ifndef PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
#define PROJ_GRAFOS_AUTORIDADE_PUBLICA_H


class Autoridade_Publica {
public:
    vector< umAgenteEconomico> agentes_economicos;
    vector<Denuncia> denuncias; //todo trocar por um melhor estrutura de dados
    vector<Inspetor> inspectores;

};


#endif //PROJ_GRAFOS_AUTORIDADE_PUBLICA_H
