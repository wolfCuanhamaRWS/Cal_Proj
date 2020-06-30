#pragma once

#include <string>
#include <vector>
#include "Data.h"
#include <iostream>
using namespace std;


/** Classes que são atributos e são passados no construtor:
Denuncias:
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

    void adicionar_uma_grave() {
        this->num_graves = this->num_graves + 1;
        this->num_total = this->num_total + 1;
    }

    void adicionar_uma_normal() {
        this->num_total = num_total + 1;
    }



};

/** Inspeção
       num_corretas : Número de  inspeções correctas.
       num_falhas:Número de  inspeções falhadas.
       Temos tambmé funções get e set para os atributos referidos em cima.
 */

class Inspecoes{


    unsigned int num_aprovadas;
    unsigned int num_reprovadas;

public:
    Inspecoes(){};
    Inspecoes(unsigned int num_aprovadas, unsigned int num_reprovadas) {
        this->num_aprovadas = num_aprovadas;
        this->num_reprovadas = num_reprovadas;
    }

    unsigned int get_num_aprovadas() const {
        return this->num_aprovadas;
    }

    void set_num_aprovadas(unsigned int num_aprovadas) {
        this->num_aprovadas = num_aprovadas;
    }


    unsigned int get_num_reprovadas() const
    {
        return this->num_reprovadas;
    }

    void set_num_reprovadas(unsigned int num_reprovadas) {
        this->num_reprovadas = num_reprovadas;
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
    int idNo = -1;
    AtividadeEconomica atividades_economicas;
    float area;
    pair<unsigned int, unsigned int> horario_funcionamento;
    float tmpInspecao;
    Denuncias *denuncias;
    Inspecoes *inspecoes;
    Data *dataUI;
    double urgencyPontuation = 0.0;




public:

    AgenteEconomico();
    AgenteEconomico(const unsigned int id , const AtividadeEconomica &atividadesEconomicas, float area, const pair<unsigned int, unsigned int> &horario_funcionamento, Denuncias *denuncias,Inspecoes *inspecoes, Data *dataUI,int idNo );

    AgenteEconomico(unsigned int id, const AtividadeEconomica &atividadesEconomicas, float area,
                    const pair<unsigned int, unsigned int> &horario_funcionamento, Denuncias *denuncias,
                    Inspecoes *inspecoes, Data *dataUI);

    //manipular atividades economicas
    AtividadeEconomica getAtividadeEconomica() const{return this->atividades_economicas;};
    void set_atividades(AtividadeEconomica atividades_economicas){this->atividades_economicas = atividades_economicas;};
    string  getAtividadeString() const;

    //idNo set ,get func
    int get_idNo() const {return idNo;};
    void set_idNo(int idNo )  { this->idNo = idNo;}

    //id
    unsigned int get_id() const {return this->id;};
    void set_id(unsigned  int id){this-> id = id;};
    //area
    float get_area()const{return this-> area;};
    void set_area(float area){this->area = area;};

    //horario funcionamento
    pair<unsigned  int ,unsigned int> get_horario_funcionamento() const{return this-> horario_funcionamento;};
    void set_horario_funcionamento(unsigned int abertura, unsigned int fecho){this->horario_funcionamento.first = abertura; this->horario_funcionamento.second = fecho;};


    //Denúncias
    Denuncias *getDenuncias() const { return this->denuncias; };

    void setDenuncias(Denuncias *denuncias_) { this->denuncias = denuncias_; }

    //Inspecoes
    Inspecoes *getInspecoes() const { return this->inspecoes; };

    void setInspecoes(Inspecoes *inspecoes_) { this->inspecoes = inspecoes_; }



    //Data última inspeção
    Data *getDataUi() const { return this->dataUI; };

    void setDataUi(Data *dataUI) { this->dataUI = dataUI; }
    /**Função que calcula tempo de inspeção de cada agenteEconómico usando area dos mesmos
     *
     * @return valor do tempo de inspeção calculado
     */
    float gerarTmpInspecao() {
        if (area <= 50.0)
            return 0.5;
        else if(area <= 200)
            return 1.0;
        else if( area <= 500)
            return 2;
        else if(area <= 1000)
            return 3;
        else
            return  5;
    }
    float getTmpInpec() const { return tmpInspecao;}
    void  imprimirFicheiro(ostream &out) const;
    bool operator==(const AgenteEconomico &agEcono){


        return this->get_id() == agEcono.get_id();
    }

    //cálcula da urgència de visita tendo em conta vários paràmetros dos Ag Económicos
    double getUrgInspec(){ return urgencyPontuation;}
    double calcUrgenciaInspec() const;

};


