#include "../Header/Brigada.h"

Brigada::Brigada(string especialidade, int ID, int hora_comeco, int numero_horas_diario)
{
    this->especialidade = especialidade;
    this->ID = ID;
    this->hora_comeco = hora_comeco;
    this->numero_horas_diario = numero_horas_diario;

}

string Brigada::get_especialidade() const
{
    return this->especialidade;
}

void Brigada::set_especialidade(string especialidade)
{
    this->especialidade = especialidade;
}

int Brigada::get_ID() const
{
    return this->ID;
}

void Brigada::set_ID(int ID)
{
    this->ID = ID;
}

int Brigada::get_hora_comeco() const
{
    return this->hora_comeco;
}

void Brigada::set_hora_comeco(int hora_comeco)
{
    this->hora_comeco = hora_comeco;
}

int Brigada::get_num_horas() const
{
    return numero_horas_diario;
}

void Brigada::set_num_horas(int numero_horas_diario)
{
    this->numero_horas_diario = numero_horas_diario;
}
