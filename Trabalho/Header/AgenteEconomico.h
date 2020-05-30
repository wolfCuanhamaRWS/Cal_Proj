#ifndef PROJ_GRAFOS_AGENTEECONOMICO_H
#define PROJ_GRAFOS_AGENTEECONOMICO_H
/*
 * Estrutura do ficheiro agente_economico:
 * nome do agente económico
 * intervalo funcionamento (<hora abertura>(espaço)<hora de fecho>)
 * id's das denúncias separados por vírgula
 * atividades económicas em que o agente se escontra, separados por vírgula
 * localização
 * tuplos de inspeções separados por vírgula (<id da denúncia>, <true/false>)
 */
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <stack>

#include "Denuncia.h"

using namespace std;

class AgenteEconomico
{
private:

    string nome;
    pair<int, int> intervalo_funcionamento;
    vector<Denuncia> denuncias;
    vector<string> atividades_economicas; //Obras, Atividade Comercial, Ambiental e Intervenção na Via Pública
                                          //Segurança e Salubridade de Edificações, Géneros Alimentícios (e.g. talhos, restauração...)
    //todo localizacao
    stack<pair<Denuncia, bool>>inspecoes;// Vector de inspeções já efetuadas; Dicionario com a denuncia e o seu resultado (true se passou, false se chumbou)

public:
    /*
     * Constructor
     * Lê e processa as informações do ficheiro agente_economico.txt
     */
    AgenteEconomico(string nome, pair<int, int> intervalo_funcionamento, vector<Denuncia> denuncias, vector<string> atividades_economicas, vector< pair<Denuncia, bool> >inspecoes);

    void set_horario_funcionamento(int &abertura, int &fechado);

    int get_horario_abertura();

    int get_horario_fechamento();

    //string get_especialidade();

    stack<pair<Denuncia, bool>> get_inspecoes();

    void add_inspecao(Denuncia &denuncia, bool &resultado);

    bool get_resultado_ultima_visita();

};

#endif //PROJ_GRAFOS_AGENTEECONOMICO_H

