#ifndef PROJ_GRAFOS_BRIGADA_H
#define PROJ_GRAFOS_BRIGADA_H

#include <string>

using namespace std;

class Brigada
{
private:
    int ID;
    string especialidade; //ou se forem várias especialidades: vector<string> atividades_economicas;
                            //Obras, Atividade Comercial, Ambiental e Intervenção na Via Pública
                            //Segurança e Salubridade de Edificações, Géneros Alimentícios (e.g. talhos, restauração...)
    int hora_comeco; //hora do dia em que a brigada começa a sua atividade
    int numero_horas_diario; //número de horas diário total para as inspeções mais as viagens

public:
    Brigada(string especialidade, int ID, int hora_comeco, int numero_horas_diario);

    //ID
    int get_ID() const;
    void set_ID(int ID);

    //especialidade
    string get_especialidade() const;
    void set_especialidade(string especialidade);

    //Hora começo
    int get_hora_comeco() const;
    void set_hora_comeco(int hora_comeco);

    //Número horas diário
    int get_num_horas() const;
    void set_num_horas(int numero_horas_diario);


};


#endif //PROJ_GRAFOS_INSPETOR_H
