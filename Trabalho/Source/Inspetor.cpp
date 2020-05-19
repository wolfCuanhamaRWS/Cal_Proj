//
// Created by Amanda  on 12/05/20.
//

#include "../Header/inspetor.h"

using namespace std;

Inspetor::Inspetor() {
}

Inspetor::Inspetor(const int &id, const string &especialidade) {
    this->id = id,
            this->especiadidade = especialidade;
}
Inspetor::Inspetor(string especialidade) {
    this->especiadidade = especialidade;
}

string Inspetor::get_especialidade() {
    return especiadidade;
}

void Inspetor::set_especialidade(string especialidade) {
    this->especiadidade = especialidade;
}