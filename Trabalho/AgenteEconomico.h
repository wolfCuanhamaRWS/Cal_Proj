//
// Created by Amanda  on 12/05/20.
//
#include <vector>
#include <map>
#include <stack>
#include "Denuncia.cpp"
#include "Denuncia.h"

#define PROJ_GRAFOS_AGENTEECONOMICO_H

using namespace std;

class AgenteEconomico {
private:

    pair<int, int> intervalo_funcionamento;
    vector<Denuncia> denuncias;
    vector<string> especialidade;// trocar por uma hash table para
    //todo localizacao
    stack<pair<Denuncia, bool>>inspecoes;// Dicionario com a denuncia e o seu resultado de A-F
    int numero_de_visitas;

public:
    AgenteEconomico(vector<string> especialidades);//

    int set_horario_funcionamento(int &abertura, int &fechado);

    int get_horario_abertura();

    int get_horario_fechamento();

    //string get_especialidade();

    stack<pair<Denuncia, bool>> get_inspecoes();

    void add_inspecao(Denuncia &denuncia, bool &resultado);

    bool get_resultado_ultima_visita();

    void set_numero_visitas(int &n);

    int get_numero_visitas();


};



