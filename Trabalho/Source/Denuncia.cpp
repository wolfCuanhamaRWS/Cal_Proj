#include "../Header/Denuncia.h"

Denuncia::Denuncia(int id, int id_agente, int gravidade, string especialidade)
{
    this->id = id;
    this->id_agente = id_agente;
    this->gravidade = gravidade;
    this->especialidade = especialidade;
}

int Denuncia::get_id() const
{
    return this->id;
}

void Denuncia::set_id(int id)
{
    this->id = id;

}

int Denuncia::get_id_agente() const
{
    return this->id_agente;
}

void Denuncia::set_id_agente(int id_agente)
{
    this->id_agente = id_agente;
}

int Denuncia::get_gravidade() const
{
    return gravidade;
}

string Denuncia::get_gravidade_string() const
{
    switch(gravidade)
    {
        case 1:
            return "muito leve";
        case 2:
            return "leve";
        case 3:
            return "normal";
        case 4:
            return "grave";
        case 5:
            return "muito grave";
    }
}

void Denuncia::set_gravidade(int gravidade)
{
    this->gravidade = gravidade;
}

string Denuncia::get_especialidade() const
{
    return especialidade;
}

void Denuncia::set_especialidade(string especialidade)
{
    this->especialidade = especialidade;
}
