//
// Created by Amanda  on 05/06/20.
//


#pragma once
#include <string>
#include <vector>
#include "Data.h"

/*
 * Classes que são atributos e são passados no construtor:
Denuncia:
QG : Número de queixas muito graves.
TQ : Número total de queixas.

 */


class Denuncias{

    unsigned int num_graves;
    unsigned  int num_total;

public:
    Denuncias(){};
    Denuncias(unsigned int num_graves, unsigned  int num_total){
        this->num_graves = num_graves;
        this->num_total = num_total;
    }
    unsigned int get_num_graves()const {
        return this->num_graves;
    }
    void set_num_graves(unsigned  int  num_graves) {
        this->num_graves = num_graves;
    }


    unsigned  int get_num_total() const {
        return this->num_total;
    }
    void set_num_total(unsigned  int num_total) {
        this->num_total = num_total;
    }

};

/** Inspeção
       num_corretas : Número de  inspeções correctas.
       num_falhas:Número de  inspeções falhadas.
       Temos tambmé funções get e set para os atributos referidos em cima.
 */

class Inspecoes{


    unsigned  int num_corretas;
    unsigned  int num_falhas;

public:
    Inspecoes(){};
    Inspecoes(unsigned int num_corretas, unsigned  int num_falhas){
        this->num_corretas = num_corretas;
        this->num_corretas = num_corretas;
    }
    unsigned  int get_num_corretas() const {
        return this->num_corretas;
    }

    void set_num_corretas(unsigned  int num_corretas) {
        this->num_corretas = num_corretas;
    }


    unsigned int get_num_falhas() const {
        return this->num_falhas;
    }

    void set_num_falhas(unsigned  int num_falhas) {
        this->num_falhas = num_falhas;
    }


};




/**
 * Atributos da Classe AgenteEconomico
 *
    ID : um valor único e identificativo para cada agente económico.
    atividades_economicas : conjunto de atividades económicas de um agente económico, sendo i o i-ésimo elemento.

    area : Área em metros quadrados (servirá para calcular TI)
    horario_funcionamento : horário de funcionamento do agente económico início e fim
    tmpInspecao : Tempo de Inspeção (usaremos uma função para determinar este parâmetro).Não precisa de ser passado como parâmetro no construtor, eu farei uma função.

    Classes que são atributos e são passados no construtor:
        Denuncia
        Inspeção


    dataUI : Data da última inspeção
    Temos também funções get e set referentes aos atributos referidos em cima.
*/



using namespace std;

enum AtividadeEconomica {Todas, Obras, Comercial,Ambiental, IntervencaoViaPublica, SegurancaSalubridadeEdificacoes,GenerosAlimenticios };

class AgenteEconomico {




    unsigned  int id;
    AtividadeEconomica atividades_economicas;
    float area;
    pair<unsigned int  ,unsigned int > horario_funcionamento;
    float tmpInspecao ;
    Denuncias denuncias;
    Inspecoes inspecoes;
    Data dataUI;




public:

    AgenteEconomico();
    AgenteEconomico(const unsigned int id , const AtividadeEconomica &atividadesEconomicas, float area, pair<unsigned int ,unsigned int > &horario_funcionamento,Denuncias &denuncias,Inspecoes &inspecoes,Data dataUI);

    AtividadeEconomica getAtividadeEconomica() const{return this->atividades_economicas;};
    void set_atividades(AtividadeEconomica atividades_economicas){this->atividades_economicas = atividades_economicas;};

    unsigned int get_id() const {return this->id;};
    void set_id(unsigned  int id){this-> id = id;};

    float get_area()const{return this-> area;};
    void set_area(float area){this->area = area;};

    pair<unsigned  int ,unsigned int> get_horario_funcionamento() const{return this-> horario_funcionamento;};
    void set_horario_funcionamento(unsigned int abertura, unsigned int fecho){this->horario_funcionamento.first = abertura; this->horario_funcionamento.second = fecho;};

    Data getDataUi() const{ return dataUI;};
    void setDataUi(Data dataUI){ this->dataUI = dataUI;}

    /**Função que calcula tempo de inspeção de cada agenteEconómico usando area dos mesmos
     *
     * @return valor do tempo de inspeção calculado
     */
    float gerarTmpInspecao();


};


