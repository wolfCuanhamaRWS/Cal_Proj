#ifndef CAL_PROJ_BRIGADA_H
#define CAL_PROJ_BRIGADA_H

#pragma once


#include <vector>
#include "AgenteEconomico.h"

using namespace std;
/** Brigada

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
    double velocidadeMedia = 0;
public:
    Brigada();
    Brigada(unsigned int id,    unsigned int horas_trabalho,unsigned int hora_inicio, AtividadeEconomica atividades_economicas);

    AtividadeEconomica get_atividades_economicas() const{return atividades_economicas;}
    void set_atividades_economicas(AtividadeEconomica atividades_economicas){ this->atividades_economicas = atividades_economicas;};

    //id
   unsigned int get_id()const{return id;};
   void set_id(unsigned int  id){this->id = id;};


    string getAtividadeString_() const
    {   if(atividades_economicas == Todas)
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
        else //if(atividades_economicas == GenerosAlimenticios)
            return "GenerosAlimenticios";
/*
        else
            return "";
            */


    }

    //horas de trabalho
    unsigned int get_horas_trabalho() const {return horas_trabalho;};
    void set_horas_trabalho(unsigned  int horas_trabalho){this->horas_trabalho = horas_trabalho;};

    unsigned  int get_hora_inicio() const{return hora_inicio;};
    void set_hora_inicio(unsigned  int hora_inicio){this->hora_inicio = hora_inicio;}

    /**
     * Escreve para uma ostream out (neste caso, o ficheiro brigadas.txt) o valor dos atributos com a formatação necessária em ficheiros
     * @param out A stream de output para onde serão escritos os valores dos atributos
     */
    void imprimirFicheiro(ostream & out) const;


    double getVelocidadeMedia() const{
        return this->velocidadeMedia;
   }

   void setVelocidadeMedia(double velMedia){ this->velocidadeMedia = velMedia;};

};

#endif //CAL_PROJ_BRIGADA_H