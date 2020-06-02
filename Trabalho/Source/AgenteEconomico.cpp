#include "../Header/AgenteEconomico.h"

AgenteEconomico::AgenteEconomico(int ID, string nome, float area, pair<int, int> horario_funcionamento, set<int> ids_denuncias,
                                 vector<string> atividades_economicas, set<pair<int, string>> inspecoes)
{
    this->ID = ID;
    this->nome = nome;
    this->area = area;
    this->horario_funcionamento = horario_funcionamento;
    this->ids_denuncias = ids_denuncias;
    this->atividades_economicas = atividades_economicas;
    this->inspecoes = inspecoes;

}

int AgenteEconomico::get_ID() const
{
    return this->ID;
}

void AgenteEconomico::set_ID(int ID)
{
    this->ID = ID;
}

string AgenteEconomico::get_nome() const
{
    return this->nome;
}

void AgenteEconomico::set_nome(string nome)
{
   this->nome = nome;
}

float AgenteEconomico::get_area() const
{
    return this->area;
}

void AgenteEconomico::set_area(float area)
{
    this->area = area;
}

int AgenteEconomico::get_abertura() const
{
    return this->horario_funcionamento.first;
}

int AgenteEconomico::get_fecho() const
{
    return this->horario_funcionamento.second;
}

pair<int, int> AgenteEconomico::get_horario() const
{
    return this->horario_funcionamento;
}


void AgenteEconomico::set_horario_funcionamento(int abertura, int fecho)
{
    pair<int, int> intervalo = make_pair(abertura, fecho);
    this->horario_funcionamento = intervalo;
}

set<int> AgenteEconomico::get_denuncias() const
{
    return this->ids_denuncias;
}

void AgenteEconomico::set_denuncias(set<int> ids_denuncias)
{
    this->ids_denuncias = ids_denuncias;
}

vector<string> AgenteEconomico::get_atividades() const
{
    return this->atividades_economicas;
}

void AgenteEconomico::set_atividades(vector<string> atividades_economicas)
{
    this->atividades_economicas = atividades_economicas;
}

set<pair<int, string>> AgenteEconomico::get_inspecoes() const
{
    return this->inspecoes;
}

void AgenteEconomico::set_inspecoes(set<pair<int, string>> inspecoes)
{
    this->inspecoes = inspecoes;
}



