//
// Created by Amanda  on 12/05/20.
//

#include "../Header/Autoridade_Publica.h"

vector<Inspetor *> Autoridade_Publica::get_inspetores() {
    return inspetores;
}

vector<Denuncia *> Autoridade_Publica::get_denuncias() {
    return denuncias;
}

vector<AgenteEconomico *> Autoridade_Publica::get_agente_economicos() {
    return agentes_economicos;
}

void Autoridade_Publica::set_agentes_economicos(vector<AgenteEconomico *> agentes_economico) {
    this->agentes_economicos = agenteEconomico;
}

void Autoridade_Publica::set_denuncias(vector<Denuncia *> &denuncias) {
    this->denuncias = denuncias;
}

void Autoridade_Publica::set_inspetores(vector<Inspetor *> inspetores) {
    this->inspetores == inspetores;
}

void Autoridade_Publica::set_inspetores(vector<Inspetor *> inspetores) {
    this->inspetores = inspetores;
}

void Autoridade_Publica::add_agente_economico(const AgenteEconomico &agenteEconomico) {
    agentes_economicos.insert(agenteEconomico);
}

void Autoridade_Publica::add_denucia(const Denuncia &denuncia) {
    denuncias.insert(denuncia);
}

void Autoridade_Publica::add_inspetor(const Inspetor &inspetor) {
    inspetores.insert(inspetor);
}