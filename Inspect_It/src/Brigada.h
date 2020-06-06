//
// Created by Amanda  on 05/06/20.
//

#pragma once

/*

Brigada:

	AEi :  conjunto de atividades económicas que são especialidade de uma brigada (poderá ser uma ou várias como será explicado nos casos a serem explorados) sendo i o i-ésimo elemento.

	HI : Número de horas diário total de trabalho para efetuar inspeções e viagens inerentes às mesmas.
	ID : um valor único e identificativo para cada brigada.
	HIB : hora do dia em que brigada começa a sua atividade.


 */

#include <vector>
#include "AgenteEconomico.h"
using namespace std;


class Brigada {

private:
    AtividadeEconomica atividades_economicas;
    unsigned int horas_trabalho;
    unsigned  int id;
    unsigned int hora_inicio;
public:

    AtividadeEconomica get_atividades_economicas() const{return atividades_economicas;}
    void set_atividades_economicas(AtividadeEconomica atividades_economicas){ this->atividades_economicas = atividades_economicas;};

    unsigned int get_horas_trabalho() const {return horas_trabalho;};
   void set_horas_trabalho(unsigned  int horas_trabalho){this->horas_trabalho = horas_trabalho;};

   unsigned int get_id()const{return id;};
   void set_id(unsigned int  id){this->id = id;};


   unsigned  int get_hora_inicio() const{return hora_inicio;};
   void set_hora_inicio(unsigned  int hora_inicio){this->hora_inicio = hora_inicio;}


};