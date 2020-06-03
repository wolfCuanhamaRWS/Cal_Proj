#include "Servico.h"
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

/****************************************************************************************************************
                             IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE Servico
****************************************************************************************************************/
Servico::Servico(int id, string ori, string dest, string temp, Data* dat, string hora_in, string tipMerc, string tipServ, Cliente * cli, vector<Camiao*> cams)
{
	this->id = id;
	origem = ori;
	destino = dest;
	tempo = temp;
	data = dat;
	hora_inicio = hora_in;
	tipoMercadoria = tipMerc;
	tipoServico = tipServ;
	cliente = cli;
	camioes = cams;
}

/***************************************************************************************************************/

int Servico::getId() const
{
    return id;
}
/***************************************************************************************************************/

string Servico::getOrigem() const
{
    return origem;
}

/***************************************************************************************************************/

string Servico::getDestino() const
{
    return destino;
}

/***************************************************************************************************************/

string Servico::getTempo() const
{
    return tempo;
}

/***************************************************************************************************************/

string Servico::getData() const
{
    return data->getData();
}

/***************************************************************************************************************/

Data* Servico::getDataObjecto() const
{
    return data;
}

/***************************************************************************************************************/

string Servico::getHora_inicio() const
{
	return hora_inicio;
}

/***************************************************************************************************************/

string Servico::getTipoMercadoria() const
{
    return tipoMercadoria;
}

/***************************************************************************************************************/

string Servico::getTipoServico() const
{
    return tipoServico;
}

/***************************************************************************************************************/

Cliente* Servico::getCliente() const
{
    return cliente;
}

/***************************************************************************************************************/

vector<Camiao *> Servico::getCamioes() const
{
	return camioes;
}

/***************************************************************************************************************/

void Servico::setId(int id)
{
    this->id = id;
}

/***************************************************************************************************************/

void Servico::setOrigem(string origem)
{
    this->origem = origem;
}

/***************************************************************************************************************/

void Servico::setDestino(string destino)
{
    this->destino = destino;
}

/***************************************************************************************************************/

void Servico::setTempo(string tempo)
{
    this->tempo = tempo;
}

/***************************************************************************************************************/

void Servico::setData(int ano, int mes, int dia)
{
    this->data->setData(ano, mes, dia);
}

/***************************************************************************************************************/

void Servico::setHora_inicio(string hora_in)
{
	this->hora_inicio = hora_in;
}

/***************************************************************************************************************/

void Servico::setTipoMercadoria(string tipoMercadoria)
{
    this->tipoMercadoria = tipoMercadoria;
}

/***************************************************************************************************************/

void Servico::setTipoServico(string tipoServico)
{
    this->tipoServico = tipoServico;
}

/***************************************************************************************************************/

void Servico::setCliente(Cliente* cli)
{
    cliente=cli;
}

/***************************************************************************************************************/

void Servico::setCamioes(vector<Camiao *> cams)
{
	this->camioes = cams;
}

/***************************************************************************************************************/

void Servico::imprimirFicheiro(ostream & out) const
{
    out << this->id << endl;
    out << this->origem << endl;
    out << this->destino << endl;
    out << this->getData() << endl;
    out << this->hora_inicio << endl;
    out << this->tempo << endl;
    out << this->tipoMercadoria << endl;
    if(camioes.size() == 0) out<<endl;
    else
    {
        for (int i = 0; i < (camioes).size(); i++)
        {
            out<<(*(camioes.at(i))).getMatricula();
            if (i!=(camioes.size() - 1)) out<<", ";
        }
        out<<endl;
    }
    out << cliente->getNif() << endl;
    out << tipoServico << endl;
}

/***************************************************************************************************************/

void Servico::imprimir(ostream& out ) const
{
    out << id << setw(12)
        << origem << setw(15)
        << destino << setw(13)
        << data->getData() << setw(10)
        << tempo << setw(20)
        << cliente->getNif() << setw(18);
    if(camioes.size()==0) out << setw(20) << "Nao existe" << endl;
    else
    {
        for(int i=0;i<camioes.size();i++)
        {
            out << camioes.at(i)->getMatricula();
            if (i != (camioes.size() - 1)) out << ", ";
        }
        out<<endl;
    }



}

/****************************************************************************************************************
                            IMPLEMENTAÇÃO DAS FUNÇÕES RELACIONADAS COM Servico
****************************************************************************************************************/
ostream& operator<<(ostream& out,const Servico& serv)
{
    out<<"ID: "<<serv.getId()<<endl;
    out<<"Origem: "<<serv.getOrigem()<<endl;
    out<<"Destino: "<<serv.getDestino()<<endl;
    out<<"Data: "<<serv.getData()<<endl;
    out<<"Hora de inicio: "<<serv.getHora_inicio()<<endl;
    out<<"Tempo(duracao): "<<serv.getTempo()<<endl;
    out<<"Tipo de mercadoria: "<<serv.getTipoMercadoria()<<endl;
    out<<"Matriculas dos camioes associados: ";
    if((serv.getCamioes()).size() == 0) out<<"nao ha camioes associados"<<endl;
    else
    {
        for (int i = 0; i < (serv.getCamioes()).size(); i++)
        {
            out<<(*(serv.getCamioes().at(i))).getMatricula();
            if (i!=(serv.getCamioes().size() - 1)) out<<", ";
        }
        out<<endl;
    }
    out<<"NIF do cliente associado: "<<(serv.getCliente())->getNif()<<endl;
    out<<"Tipo de servico: "<<serv.getTipoServico()<<endl;
    return out;
}

/***************************************************************************************************************/


