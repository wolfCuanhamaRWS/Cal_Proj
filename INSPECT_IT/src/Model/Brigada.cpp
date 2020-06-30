
#include "Brigada.h"


Brigada::Brigada(unsigned int id,    unsigned int horas_trabalho,unsigned int hora_inicio, AtividadeEconomica atividades_economicas): id(id), horas_trabalho(horas_trabalho), hora_inicio(hora_inicio),atividades_economicas(atividades_economicas){};
Brigada::Brigada(){};

void Brigada:: imprimirFicheiro(ostream &out) const
{
    out << "::::::::::::::::::::::::::" << endl
        << get_id() << endl
        << getAtividadeString_() << endl
        << get_horas_trabalho() << endl
        << get_hora_inicio();

}
