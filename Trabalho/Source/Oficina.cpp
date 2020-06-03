#include "Oficina.h"

Servico_Oficina::Servico_Oficina(int id,bool esp,Camiao* cam,int dur)
{
    this->id=id;
    especifico=esp;
    camiao=cam;
    duracao=dur;
}

/***************************************************************************************************************/

Oficina::Oficina(int id,string denom,vector<string> marcas,int dias,vector<Servico_Oficina*> servicos)
{
    this->id=id;
    this->denom=denom;
    this->marcas=marcas;
    diasAteDisponivel=dias;
    this->servicos=servicos;
}

/***************************************************************************************************************/

string Oficina::getDenom() const
{
    return denom;
}

/***************************************************************************************************************/

vector<string> Oficina::getMarcas() const
{
    return marcas;
}

/***************************************************************************************************************/

int Oficina::getDiasAteDisponivel() const
{
    return diasAteDisponivel;
}

/***************************************************************************************************************/

vector<Servico_Oficina*> Oficina::getServicos() const
{
    return servicos;
}

/***************************************************************************************************************/

void Oficina::setDenom(string denom)
{
    this->denom=denom;
}

/***************************************************************************************************************/

void Oficina::setMarcas(vector<string> marcas)
{
    this->marcas=marcas;
}

/***************************************************************************************************************/

void Oficina::setDiasAteDisponivel(int dias)
{
    diasAteDisponivel=dias;
}

/***************************************************************************************************************/

void Oficina::setServicos(vector<Servico_Oficina*> servicos)
{
    this->servicos=servicos;
}

/***************************************************************************************************************/

void Oficina::imprimir(ostream& out) const
{
    int tamanho_nome = denom.size();
    int count = 0; //conta o numero de caracteres que ocupa o nome das marcas
    out << " " << id << setw(tamanho_nome + 5)
        << denom << setw(40 - tamanho_nome)
        << diasAteDisponivel << "                       ";

    if(marcas.size()==0);
    else
    {
        for (int i = 0; i < marcas.size(); i++)
        {
            count = count + marcas.at(i).size();
            out << marcas.at(i);
            if (i != (marcas.size() - 1)) out << ", ";
        }

    }


    if(servicos.size()==0);
    else
    {
        out << setw(30 - count);
        for (int i = 0; i < servicos.size(); i++) {
            out << servicos.at(i)->getId();
            if (i != (servicos.size() - 1)) out << ", ";
        }

    }
    out << endl;
}

/***************************************************************************************************************/

void Oficina::imprimirFicheiro(ostream & out) const
{
    out<<id<<endl;
    out<<denom<<endl;
    if (marcas.size()==0) out<<endl;
    else
    {for (auto i  : marcas)
    {
      if (i==marcas.back()) out<<i<<endl;
      else out<<i<<", ";
    }}
    if (servicos.size()==0) out<<endl;
    else
    for (auto i:servicos)
    {{
        if (i==servicos.back()) out<<i->id<<endl;
        else out<<i->id<<", ";
    }}
}

/***************************************************************************************************************/

void Oficina::adicionarServico(Servico_Oficina* serv)
{
    servicos.push_back(serv);
    diasAteDisponivel+=serv->duracao;
}

/***************************************************************************************************************/

void Oficina::removerServico(Servico_Oficina* serv)
{
    for ( auto it = servicos.begin(); it != servicos.end(); it++) {
    if ((**it)==(*serv))
    {
        diasAteDisponivel-=(**it).duracao;
        it = servicos.erase(it);
        it--;
    }
}

}

/***************************************************************************************************************/

bool operator <(const Oficina& left,const Oficina& right)
{
    if (left.getDiasAteDisponivel()>right.getDiasAteDisponivel()) return true;
    else if(left.getDenom()>right.getDenom() && left.getDiasAteDisponivel()==right.getDiasAteDisponivel()) return true;
    else return false;
}

/***************************************************************************************************************/

bool operator ==(const Oficina& left,const Oficina& right)
{
    return (left.getDenom()==right.getDenom() && left.getMarcas()==right.getMarcas() && left.getDiasAteDisponivel()==right.getDiasAteDisponivel() && left.getServicos()==right.getServicos());
}

/***************************************************************************************************************/

bool operator==(const Servico_Oficina& left, Servico_Oficina& right)
{
    return left.especifico==right.especifico && left.camiao==right.camiao && left.duracao==right.duracao && right.id==left.id;
}

/***************************************************************************************************************/

void Oficina::setId(int id)
{
    this->id=id;
}

/***************************************************************************************************************/

int Oficina::getId() const
{
    return id;
}

/***************************************************************************************************************/

void Servico_Oficina::imprimirFicheiro(ostream & out) const
{
    out<<id<<endl;
    if (especifico) out<<1;
    else out<<0;
    out<<endl;
    out<<camiao->getMatricula()<<endl;
    out<<duracao<<endl;
}

/***************************************************************************************************************/

int Servico_Oficina::getId() const
{
    return id;
}

/***************************************************************************************************************/

int Servico_Oficina::getDuracao() const
{
    return duracao;
}

/***************************************************************************************************************/

Camiao* Servico_Oficina::getCamiao() const
{
    return camiao;
}

/***************************************************************************************************************/
