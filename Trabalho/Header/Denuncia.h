#ifndef PROJ_GRAFOS_DENUNCIA_H
#define PROJ_GRAFOS_DENUNCIA_H

#include <string>

using namespace std;

class Denuncia {

private:
    int id; //id da denúncia
    int gravidade; // Podedendo variariar de 1 a 5 (leve, muito grave)
    string especialidade;  //

public:
    Denuncia();

    Denuncia(const string &esecialidade, const int &gravidade);

    void set_gravidade(const int gravidade);

    int get_gravidade();

    void set_especialidade(const string especialidade);

    string get_especialidade();
};


#endif //PROJ_GRAFOS_DENUNCIA_H
