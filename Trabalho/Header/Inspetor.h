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

    Inspetor(const int &id, const string &especialidade);

    string get_especialidade();

    void set_especialidade(const string &especialidade);

    int get_id();

    void set_id(const int &id);


};


#endif //PROJ_GRAFOS_INSPETOR_H
