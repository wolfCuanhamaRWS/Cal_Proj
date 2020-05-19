//
// Created by Amanda  on 12/05/20.
//

#ifndef PROJ_GRAFOS_DENUNCIA_H
#define PROJ_GRAFOS_DENUNCIA_H

#include <string>

class Denuncia {

private:
    int gravidade; // Podedendo variariar de 1 a 5 (leve, muito grave)
    string especialidade;  //

public:
    Denuncia();
    Denuncia( string &esecialidade , int &gravidade);

    int get_gravidade();
};


#endif //PROJ_GRAFOS_DENUNCIA_H
