//
// Created by Amanda  on 12/05/20.
//
#include "../Header/Denuncia.h"

Denuncia::Denuncia(const string &especialidade, const int &gravidade) {
    this->especialidade = especialidade;
    this->gravidade = gravidade;
}

Denuncia::Denuncia() {}

int Denuncia::get_gravidade() {
    return gravidade;
}

void Denuncia::set_gravidade(const int gravidade) {}

{
this->
gravidade = gravidade;

}

void Denuncia::set_especialidade(const string especialidade) {
    this->especialidade = especialidade;
}
