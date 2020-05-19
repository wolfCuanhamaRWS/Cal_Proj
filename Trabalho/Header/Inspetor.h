//
// Created by Amanda  on 12/05/20.
//

#ifndef PROJ_GRAFOS_INSPETOR_H
#define PROJ_GRAFOS_INSPETOR_H

using namespace std;
class Inspetor {
private:
    string especiadidade;
    int id; //todo tb pode ser substituida pelo nome

    //Hash_INPECOES//todo criar uma hash table com as inspecoes já feitas???

public:
    Inspetor();
    Inspetor(string especialidade);
    string get_especialidade();


    void set_especialidade(string especialidade);


};


#endif //PROJ_GRAFOS_INSPETOR_H
