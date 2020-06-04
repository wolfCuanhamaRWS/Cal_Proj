#ifndef PROJ_GRAFOS_DENUNCIA_H
#define PROJ_GRAFOS_DENUNCIA_H
#include <string>

using namespace std;

class Denuncia
{

private:
    int id; //id da denúncia
    int id_agente; //id do agente económico denunciado
    int gravidade; // Podedendo variariar de 1 a 5 (de muito leve a muito grave)
    string especialidade;  //onde a denúncia se enquadra

public:
    Denuncia(int id, int id_agente, int gravidade, string especialidade);

    //id
    int get_id() const;
    void set_id(int id);

    //id_agente
    int get_id_agente() const;
    void set_id_agente(int id_agente);

    //gravidade
    int get_gravidade() const;
    string get_gravidade_string() const;
    void set_gravidade(int gravidade);

    //especialidade
    string get_especialidade() const;
    void set_especialidade(string especialidade);

};


#endif //PROJ_GRAFOS_DENUNCIA_H
