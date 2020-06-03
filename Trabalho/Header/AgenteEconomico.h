#ifndef PROJ_GRAFOS_AGENTEECONOMICO_H
#define PROJ_GRAFOS_AGENTEECONOMICO_H
/*
 * Estrutura do ficheiro agente_economico:
 * separador (::::::::::::::::::::::::::)
 * ID
 * nome do agente económico
 * área em metros quadrados
 * intervalo funcionamento (<hora abertura>-<hora de fecho>)
 * id's das denúncias separados por vírgula
 * atividades económicas em que o agente se escontra, separados por vírgula
 * localização
 * tuplos de inspeções separados por "|" (<id da denúncia>, <true/false>)
 */
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include <stack>
#include <set>
#include <iostream>

#include "Data.h"
#include "Local.h"

using namespace std;

class AgenteEconomico
{
private:

    int ID;
    string nome;
    float area; //área em metros quadrados
    pair<int, int> horario_funcionamento;
    set<int> ids_denuncias; //set que guarda os id's das denúncias (não pode haver id's repetidos daí ser um set)
    vector<string> atividades_economicas; //Obras, Atividade Comercial, Ambiental e Intervenção na Via Pública
                                          //Segurança e Salubridade de Edificações, Géneros Alimentícios (e.g. talhos, restauração...)
    set<pair<int, string>> inspecoes;// Vetor de inspeções já efetuadas; Dicionario com a denuncia e o seu resultado ("aprovado", "reprovado", "desconhecido")
    Local morada;

public:
    AgenteEconomico();

    AgenteEconomico(int ID, string nome, float area, pair<int, int> horario_funcionamento, set<int> ids_denuncias, vector<string> atividades_economicas, set<pair<int, string>>inspecoes,long double latitude,long double longuitude);

    //ID
    int get_ID() const;
    void set_ID(int ID);

    //nome
    string get_nome() const;
    void set_nome(string nome);

    //área
    float get_area() const;
    void set_area(float area);

    //horario funcionamento
    int get_abertura() const;
    int get_fecho() const;
    pair<int, int>  get_horario() const;
    void set_horario_funcionamento(int abertura, int fecho);

    //id's das denúncias
    set<int> get_denuncias() const;
    void set_denuncias(set<int> ids_denuncias);

    //atividades económicas
    vector<string> get_atividades() const;
    void set_atividades(vector<string> atividades_economicas);

    //inspeções
    set<pair<int, string>> get_inspecoes() const;
    void set_inspecoes(set<pair<int, string>> inspecoes);

    /*morada
    Local get_morada() const;
    void set_morada(Local inspecoes);*/


    void add_inspecao(int &denuncia, bool &resultado);
    bool get_resultado_ultima_visita();

    //Outras funções (Flávio quer fazer esta parte?)
    int tempo_inspecao();
    int get_numero_queixas_muito_graves();
    int get_numero_total_queixas();
    int get_numero_inspecoes_aprovadas();
    int get_numero_inspecoes_reprovadas();
    Data get_data_ultima_inspecao();

    /**
     * Escreve para uma ostream out o valor de todos os membros-dado de forma formatada.
     * @param out A stream de output para onde serão escritos os valores dos membros-dado
     */
    void imprimir(ostream& out) const;

};

#endif //PROJ_GRAFOS_AGENTEECONOMICO_H

