//
// Created by Amanda  on 12/05/20.
//

#include "../headers/inspetor.h"

using namespace std;
string Inspetor::get_especialidade() {
    return especiadidade;
}
Inspetor::Inspetor(string especialidade) {
    this->especiadidade = especialidade;
}
void Inspetor::set_especialidade(string especialidade) {
    this->especiadidade = especialidade;
}