
#ifndef CAL_PROJ_AGENTEECONOMICO_H
#define CAL_PROJ_AGENTEECONOMICO_H

#pragma once


#include <string>
#include <vector>
#include <iostream>
#include "Data.h"

using namespace std;

enum AtividadeEconomica {Todas, Obras, Comercial,Ambiental, IntervencaoViaPublica, SegurancaSalubridadeEdificacoes,GenerosAlimenticios };

/**
 * Classes que são atributos e são passados no construtor:
    Denuncia:
    QG : Número de queixas muito graves.
    TQ : Número total de queixas.

 */
class Denuncias{

    unsigned int num_graves;
    unsigned  int num_total;

public:
    Denuncias(unsigned int num_graves, unsigned  int num_total)
    {
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
       num_corretas : Número de  inspeções aprovadas.
       num_falhas:Número de  inspeções reprovadas.
       Temos tambmé funções get e set para os atributos referidos em cima.
 */

class Inspecoes
{


    unsigned  int num_aprovadas;
    unsigned  int num_reprovadas;

public:
    Inspecoes(unsigned int num_aprovadas, unsigned  int num_falhas){
        this->num_aprovadas = num_aprovadas;
        this->num_aprovadas = num_aprovadas;
    }
    unsigned  int get_num_aprovadas() const {
        return this->num_aprovadas;
    }

    void set_num_aprovadas(unsigned  int num_aprovadas) {
        this->num_aprovadas = num_aprovadas;
    }


    unsigned int get_num_reprovadas() const {
        return this->num_reprovadas;
    }

    void set_num_reprovadas(unsigned  int num_reprovadas) {
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

    Estrutura do ficheiro:
     - separador (::::::::::::::::::::::::::)
     - id do agente
     - atividade económica em que se enquadra
     - area
     - horario de funcionamento (<hora de abertura>-<hora de fecho>)
     - número de denúncias graves
     - número de denúncias total
     - número de denúncias aprovadas
     - número de denúncias reprovadas
     - Data da última inspeção no seguinte formato (aaaa/mm/dd)
*/

class AgenteEconomico
{
private:
    unsigned int id;
    AtividadeEconomica atividades_economicas;
    float area;
    pair<unsigned int, unsigned int> horario_funcionamento;
    float tmpInspecao ;
    Denuncias *denuncias;
    Inspecoes* inspecoes;
    Data* dataUI;

public:

    AgenteEconomico(unsigned int id,const AtividadeEconomica &atividadesEconomicas, float area, const pair<unsigned int ,unsigned int > &horario_funcionamento, Denuncias* denuncias, Inspecoes* inspecoes, Data* dataUI)
    {
        this-> atividades_economicas = atividadesEconomicas;
        this-> area = area;
        this-> horario_funcionamento = horario_funcionamento;
        this->denuncias = denuncias;
        this->inspecoes = inspecoes;
        this->tmpInspecao = gerarTmpInspecao();
        this-> dataUI = dataUI;
        this->id = id;
    }
    //Atividades económicas
    AtividadeEconomica getAtividadeEconomica() const{return this->atividades_economicas;};
    void set_atividades(AtividadeEconomica atividades_economicas){this->atividades_economicas = atividades_economicas;};
    string getAtividadeString() const
    {
        if(atividades_economicas == Todas)
            return "Todas";
        else if(atividades_economicas == Obras)
            return "Obras";
        else if(atividades_economicas == Comercial)
            return "Comercial";
        else if(atividades_economicas == Ambiental)
            return "Ambiental";
        else if(atividades_economicas == IntervencaoViaPublica)
            return "IntervencaoViaPublica";
        else if(atividades_economicas == SegurancaSalubridadeEdificacoes)
            return "SegurancaSalubridadeEdificacoes";
        else if(atividades_economicas == GenerosAlimenticios)
            return "GenerosAlimenticios";
        else
            return "";
    }



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
    Denuncias* getDenuncias() const{ return this->denuncias;};
    void setDenuncias(Denuncias* denuncias_){ this->denuncias = denuncias_;}

    //Inspecoes
    Inspecoes* getInspecoes() const{ return this->inspecoes;};
    void setInspecoes(Inspecoes* inspecoes_){ this->inspecoes = inspecoes_;}

    //Data última inspeção
    Data* getDataUi() const{ return this->dataUI;};
    void setDataUi(Data* dataUI){ this->dataUI = dataUI;}

    /**
     * Função que calcula tempo de inspeção em horas do agente usando a area
     * @return tempo de inspeção em horas
     */
    float gerarTmpInspecao()
    {
        if (area <= 50.0)
            return 0.5;
        else
            return area/100;
    }

    /**
     * Escreve para uma ostream out (neste caso, o ficheiro agentes.txt) o valor dos atributos com a formatação necessária em ficheiros
     * @param out A stream de output para onde serão escritos os valores dos atributos
     */
    void imprimirFicheiro(ostream & out) const
    {
        out << "::::::::::::::::::::::::::" << endl
            << get_id() << endl
            << getAtividadeString() << endl
            << get_area() << endl
            << get_horario_funcionamento().first << "-" << get_horario_funcionamento().second << endl
            << getDenuncias()->get_num_graves() << endl
            << getDenuncias()->get_num_total() << endl
            << getInspecoes()->get_num_aprovadas() << endl
            << getInspecoes()->get_num_reprovadas() << endl
            << getDataUi() << endl;
    }


};

#endif //CAL_PROJ_AGENTEECONOMICO_H


