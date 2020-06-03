#include "Excecoes.h"
#include <iostream>

using namespace std;

/****************************************************************************************************************
                          IMPLEMENTAÇÃO DOS MÉTODOS DAS CLASSES RELACIONADAS COM EXCEÇÕES
****************************************************************************************************************/
funcionarioInexistente::funcionarioInexistente(int nif)
{
    this->nif=nif;
}

/***************************************************************************************************************/

int funcionarioInexistente::getNif() const
{
    return nif;
}

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const funcionarioInexistente& funcin)
{
    out<<"\nNao existe um funcionario com o NIF "<<funcin.getNif()<<endl;
    return out;
}

/***************************************************************************************************************/

numInvalido::numInvalido(string num){
    this->num=num;
}

/***************************************************************************************************************/

string numInvalido::getNum() const {
    return num;
}

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const numInvalido& num)
{
    out<<"\nO valor "<<num.getNum()<<" nao e valido.\n";
    return out;
}

/***************************************************************************************************************/

matriculaInvalida::matriculaInvalida(string numl){
    this->matricula=matricula;
}

/***************************************************************************************************************/

string matriculaInvalida::getMatricula() const {
    return matricula;
}

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const matriculaInvalida& matr)
{
    out<<"\nO valor "<<matr.getMatricula()<<"nao e valido.\n";
    return out;
}

/***************************************************************************************************************/

camiaoInexistente::camiaoInexistente(string mat)
{
    matricula = mat;
}

/***************************************************************************************************************/

string camiaoInexistente::getMatricula() const
{
    return matricula;
}

/***************************************************************************************************************/

ostream& operator<<(ostream& out,const camiaoInexistente& camin)
{
    out<<"\nNao exite nenhum camiao com a matricula "<<camin.getMatricula()<< endl;
    return out;
}

/***************************************************************************************************************/

clienteInexistente::clienteInexistente(int n)
{
    nif=n;
}

/***************************************************************************************************************/

int clienteInexistente::getNif() const
{
    return nif;
}

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const clienteInexistente& cliin)
{
    out<<"\nNao existe nenhum cliente com o NIF "<<cliin.getNif()<<endl;
    return out;
}

/***************************************************************************************************************/

funcionarioCargoInexistente::funcionarioCargoInexistente(string cargo)
{
    this->cargo=cargo;
}

/***************************************************************************************************************/

string funcionarioCargoInexistente::getCargo() const
{
    return cargo;
}

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const funcionarioCargoInexistente& func)
{
    out<<"\nNao existe nenhum funcionario com o cargo "<<func.getCargo()<<endl;
    return out;
}

/***************************************************************************************************************/

servicoTipoMercadoriaInexistente::servicoTipoMercadoriaInexistente(string tipo_mercadoria)
{
    this->tipo_mercadoria=tipo_mercadoria;
}

/***************************************************************************************************************/

string servicoTipoMercadoriaInexistente::getTipoMercadoria() const
{
    return tipo_mercadoria;
}

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const servicoTipoMercadoriaInexistente& func)
{
    out<<"\nNao existe nenhum servico com o tipo de mercadoria "<<func.getTipoMercadoria()<<endl;
    return out;
}
/***************************************************************************************************************/

servicoPeriodicidadeInexistente::servicoPeriodicidadeInexistente(string periodicidade)
{
    this->periodicidade=periodicidade;
}

/***************************************************************************************************************/

string servicoPeriodicidadeInexistente::getPeriodicidade() const
{
    return periodicidade;
}

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const servicoPeriodicidadeInexistente& func)
{
    out<<"\nNao existe nenhum servico com a periodicidade "<<func.getPeriodicidade()<<endl;
    return out;
}

/***************************************************************************************************************/

oficinaInexistente::oficinaInexistente(){};

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const oficinaInexistente& oi)
{
    out<<"\nNao existe uma oficina com os parametros fornecidos\n"<<endl;
    return out;
}

/***************************************************************************************************************/

servicoOficinaInexistente::servicoOficinaInexistente(){};

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const servicoOficinaInexistente& soi)
{
    out<<"\nNao existe um servico de oficina com os parametros fornecidos\n"<<endl;
    return out;
}

/***************************************************************************************************************/

camiaoEmReparacao::camiaoEmReparacao(){};

/***************************************************************************************************************/

ostream& operator<<(ostream& out, const camiaoEmReparacao& cer)
{
    out<<"\nO camiao indicado ja esta a ser reparado\n"<<endl;
    return out;
}
