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
