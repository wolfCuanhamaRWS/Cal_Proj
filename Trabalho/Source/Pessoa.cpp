#include "Pessoa.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

/****************************************************************************************************************
                            IMPLEMENTAÇÃO DAS FUNÇÕES RELACIONADAS COM Pessoa
****************************************************************************************************************/
Pessoa::Pessoa(string n, int ni, int tel, string mor)
{
	nome = n;
	nif = ni;
	telefone = tel;
	morada = mor;
}

/***************************************************************************************************************/

string Pessoa::getNome() const
{
    return nome;
}

/***************************************************************************************************************/

int Pessoa::getNif() const
{
    return nif;
}

/***************************************************************************************************************/

int Pessoa::getTelefone() const
{
    return telefone;
}

/***************************************************************************************************************/

string Pessoa::getMorada() const
{
    return morada;
}

/***************************************************************************************************************/

void Pessoa::setNome(string nome)
{
    this->nome = nome;
}

/***************************************************************************************************************/

void Pessoa::setNif(int nif)
{
    this->nif = nif;
}

/***************************************************************************************************************/

void Pessoa::setTelefone(int telefone)
{
    this->telefone = telefone;
}

/***************************************************************************************************************/

void Pessoa::setMorada(string morada)
{
    this->morada = morada;
}

/***************************************************************************************************************/

bool operator<(const Pessoa& left, const Pessoa& right)
{
	return left.getNif() < right.getNif();
}

/***************************************************************************************************************/

bool operator==(const Pessoa& left, const Pessoa& right)
{
	return left.getNif() == right.getNif();
}

/***************************************************************************************************************/

Cliente::Cliente(string n, int ni, int tel, string mor, vector<int> servs) : Pessoa(n,ni,tel,mor)
{
	servicosRequisitados = servs;
}

/***************************************************************************************************************/

vector<int> Cliente::getServicosRequisitados() const
{
	return servicosRequisitados;
}

/***************************************************************************************************************/

void Cliente::setServicosRequisitados(vector<int> servs)
{
	servicosRequisitados = servs;
}

/***************************************************************************************************************/

Funcionario::Funcionario(string n, int ni, int tel, string mor, float sal, string carg) : Pessoa(n,ni,tel,mor)
{
	salario = sal;
	cargo = carg;
}

/***************************************************************************************************************/

float Funcionario::getSalario() const
{
    return salario;
}

/***************************************************************************************************************/

string Funcionario::getCargo() const
{
    return cargo;
}

/***************************************************************************************************************/

void Funcionario::setSalario(float salario)
{
    this->salario = salario;
}

/***************************************************************************************************************/

void Funcionario::setCargo(string cargo)
{
    this->cargo =cargo;
}

/***************************************************************************************************************/

void Pessoa::imprimir(ostream& out) const
{
    out << nome << setw(10)
        << nif << setw(10)
        << telefone << setw(10)
        << morada << setw(10);
}

/***************************************************************************************************************/

void Pessoa::imprimirFicheiro(ostream& out) const
{
    out<<nome<<endl;
    out<<nif<<endl;
    out<<telefone<<endl;
    out<<morada<<endl;
}

/***************************************************************************************************************/

void Cliente::imprimir(ostream& out) const
{
    int tamanho_nome = nome.size();
    out << nome << setw(40-tamanho_nome)
        << nif << setw(18)
        << telefone << setw(13)
        << morada << setw(15);
    if (servicosRequisitados.size()==0) out << setw(24) << "Nao existe"<<endl;
    else
    {
        for (int i = 0; i < servicosRequisitados.size(); i++)
        {
            out << servicosRequisitados.at(i);
            if (i != (servicosRequisitados.size() - 1)) out << ", ";
        }
        out<<endl;
    }

}

/***************************************************************************************************************/

void Cliente::imprimirFicheiro(ostream& out) const
{
    out<<nome<<endl;
    out<<nif<<endl;
    out<<telefone<<endl;
    out<<morada<<endl;
    if (servicosRequisitados.size()==0) out<<endl;
    else
    {
        for (int i = 0; i < servicosRequisitados.size(); i++)
        {
            out << servicosRequisitados.at(i);
            if (i != (servicosRequisitados.size() - 1)) out << ", ";
        }
        out<<endl;
    }

}

/***************************************************************************************************************/

void Funcionario::imprimir(ostream& out) const
{

    int tamanho_nome = nome.size();
    int tamanho_morada = morada.size();
    out << nome << setw(25-tamanho_nome)
        << nif << setw(15)
        << telefone << setw(15)
        << morada << setw(15)
        << cargo << setw(10)
        << salario << setw(12)
        << "-" << setw(15)
        << "-" << endl;
}

/***************************************************************************************************************/

void Funcionario::imprimirFicheiro(ostream& out) const
{
    out<<nome<<endl;
    out<<nif<<endl;
    out<<telefone<<endl;
    out<<morada<<endl;
    out<<cargo<<endl;
    out<<'-'<<endl;
    out<<salario<<endl;
}

/***************************************************************************************************************/

void Condutor::imprimir(ostream& out) const
{
    int tamanho_nome = nome.size();
    int tamanho_morada = morada.size();
    out << nome << setw(25-tamanho_nome)
        << nif << setw(15)
        << telefone << setw(15)
        << morada << setw(15)
        << cargo << setw(10)
        << salario << setw(12)
        << horas << setw(15);
    if(servicos.size()==0) out << setw(20) << "Nao existe";
    else
    {
        for (int i = 0; i < servicos.size(); i++) {
            out << servicos.at(i);
            if (i != (servicos.size() - 1)) out << ", ";
        }

    }
    out << endl;
}

/***************************************************************************************************************/

void Condutor::imprimirFicheiro(ostream& out) const
{
    out<<nome<<endl;
    out<<nif<<endl;
    out<<telefone<<endl;
    out<<morada<<endl;
    out<<cargo<<endl;
    if(servicos.size()==0) out<<endl;
    else
    {
        for(int i=0;i<servicos.size();i++)
        {
            out << servicos.at(i);
            if (i != (servicos.size() - 1)) out << ", ";
        }
        out<<endl;
    }
    out<<salario<<endl;
}


Condutor::Condutor() : Funcionario ("", 0, 0, "", 0, "condutor")
{
    servicos = {};
    horas = 0;
}


/***************************************************************************************************************/

Condutor::Condutor(string n,int ni,int tel,string mor,float sal,string carg,vector<int> servs, double hor)
                : Funcionario(n,ni,tel,mor,sal,carg)
{
    servicos=servs;
    horas=hor;
}

/***************************************************************************************************************/

vector<int> Condutor::getServicos() const
{
    return servicos;
}

double Condutor::getHoras() const
{
    return horas;
}
/***************************************************************************************************************/

void Condutor::setServicos(vector<int> servs)
{
    servicos=servs;
}

/***************************************************************************************************************/

void Condutor::setHoras(double hor)
{
    horas=hor;
}

/***************************************************************************************************************/

bool operator<(const Condutor& left,const Condutor& right)
{
    if(left.getHoras() == right.getHoras())
    {
        return left.getNif() < right.getNif();
    }
    return left.getHoras() < right.getHoras();
}

