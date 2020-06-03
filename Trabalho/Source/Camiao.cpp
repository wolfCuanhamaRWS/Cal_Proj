#include "Camiao.h"


using namespace std;

/****************************************************************************************************************
                            IMPLEMENTAÇÃO DAS FUNÇÕES RELACIONADAS COM Camiao
****************************************************************************************************************/

Camiao::Camiao(float cap, string mat, string marc, string mod, int a, string tipo_mercadoria)
{
	capacidade = cap;
	matricula = mat;
	marca = marc;
	modelo = mod;
	ano = a;
    tipoMercadoria = tipo_mercadoria;
}

/***************************************************************************************************************/

float Camiao::getCapacidade() const
{
    return capacidade;
}

/***************************************************************************************************************/

string Camiao::getMatricula() const
{
    return matricula;
}

/***************************************************************************************************************/

string Camiao::getMarca() const
{
    return marca;
}

/***************************************************************************************************************/

string Camiao::getModelo() const
{
    return modelo;
}

/***************************************************************************************************************/

int Camiao::getAno() const
{
    return ano;
}

/***************************************************************************************************************/

string Camiao::getTipoMercadoria() const
{
    return tipoMercadoria;
}

/***************************************************************************************************************/

void Camiao::setCapacidade(float capacidade)
{
    this->capacidade = capacidade;
}

/***************************************************************************************************************/

void Camiao::setMatricula(string matricula)
{
    this->matricula = matricula;
}

/***************************************************************************************************************/

void Camiao::setMarca(string marca)
{
    this->marca = marca;
}

/***************************************************************************************************************/

void Camiao::setModelo(string modelo)
{
    this->modelo = modelo;
}

/***************************************************************************************************************/

void Camiao::setAno(int ano)
{
    this->ano = ano;
}

/***************************************************************************************************************/

float Camiao::custo(float temp, float quant) const
{
    return 80* temp * 0.385 * quant; // 0.385*quant = preço a pagar por kilometro para uma carga de quant toneladas
                                     // 80 * temp = distancia (arredondado) (em km)
}

/***************************************************************************************************************/

Camiao_congelados::Camiao_congelados(float cap, string mat, string marc, string mod, int a, string tipo_mercadoria, float temp) : Camiao(cap,mat,marc,mod,a, tipo_mercadoria)
{
	temperatura = temp;
}

/***************************************************************************************************************/

float Camiao_congelados::getTemperatura() const
{
	return temperatura;
}

/***************************************************************************************************************/

void Camiao_congelados::setTemperatura(float temp)
{
	this->temperatura = temp;
}

/***************************************************************************************************************/

float Camiao_congelados::custo(float temp, float quant) const
{
    if(temperatura >= 0)
        return Camiao::custo(temp, quant);
    else
        return Camiao::custo(temp, quant) * (1 - 0.04 * temperatura);
}

/***************************************************************************************************************/

Camiao_perigo::Camiao_perigo(float cap, string mat, string marc, string mod, int a, string tipo_mercadoria, string niv) : Camiao(cap, mat, marc, mod, a, tipo_mercadoria)
{
	nivel = niv;
}

/***************************************************************************************************************/

string Camiao_perigo::getNivel() const
{
    return nivel;
}

/***************************************************************************************************************/

void Camiao_perigo::setNivel(string niv)
{
	this->nivel = niv;
}

/***************************************************************************************************************/

float Camiao_perigo::custo(float temp, float quant) const
{
	if (nivel == "explosivos")
        return 2*Camiao::custo(temp, quant);
	else if (nivel == "inflamaveis")
	    return 1.5*Camiao::custo(temp, quant);
	else if (nivel == "radioativo")
	    return 2.5*Camiao::custo(temp, quant);
	else
	    return 1.75*Camiao::custo(temp, quant);
}

/***************************************************************************************************************/

Camiao_animal::Camiao_animal(float cap, string mat, string marc, string mod, int a, string tipo_mercadoria, string esp) : Camiao(cap, mat, marc, mod, a, tipo_mercadoria)
{
	especie = esp;

}

/***************************************************************************************************************/

string Camiao_animal::getEspecie() const
{
    return especie;
}

/***************************************************************************************************************/

void Camiao_animal::setEspecie(string esp)
{
	this->especie = esp;
}

/***************************************************************************************************************/

float Camiao_animal::custo(float temp, float quant) const
{
    return 1.2*Camiao::custo(temp, quant);
}

/***************************************************************************************************************/

void Camiao::imprimir(ostream& out) const
{
    out << matricula << setw(12)
        << marca << setw(10)
        << modelo << setw(10)
        << ano << setw(10)
        << capacidade << setw(25)
        << tipoMercadoria << endl;

}

/***************************************************************************************************************/

void Camiao::imprimirFicheiro(ostream& out) const
{
    out << matricula<<endl;
    out<<marca<<endl;
    out<<modelo<<endl;
    out<<ano<<endl;
    out<<capacidade<<endl;
    out<<"outros"<<endl;
    out<<'-'<<endl;
}

/***************************************************************************************************************/

void Camiao_congelados::imprimir(ostream& out) const
{
    out << matricula << setw(12)
        << marca << setw(10)
        << modelo << setw(10)
        << ano << setw(10)
        << capacidade << setw(25)
        << tipoMercadoria << ": "
        << temperatura << " graus" << endl;

}

/***************************************************************************************************************/

void Camiao_congelados::imprimirFicheiro(ostream& out) const
{
    out << matricula<<endl;
    out<<marca<<endl;
    out<<modelo<<endl;
    out<<ano<<endl;
    out<<capacidade<<endl;
    out<<"congelados"<<endl;
    out<<temperatura<<endl;
}

/***************************************************************************************************************/

void Camiao_perigo::imprimir(ostream &out) const
{
    out << matricula << setw(12)
        << marca << setw(10)
        << modelo << setw(10)
        << ano << setw(10)
        << capacidade << setw(25)
        << tipoMercadoria << ": "
        << nivel << endl;

}

/***************************************************************************************************************/

void Camiao_perigo::imprimirFicheiro(ostream& out) const
{
    out << matricula<<endl;
    out<<marca<<endl;
    out<<modelo<<endl;
    out<<ano<<endl;
    out<<capacidade<<endl;
    out<<"perigosas"<<endl;
    out<<nivel<<endl;
}

/***************************************************************************************************************/

void Camiao_animal::imprimir(ostream& out) const
{
    out << matricula << setw(12)
        << marca << setw(10)
        << modelo << setw(10)
        << ano << setw(10)
        << capacidade << setw(25)
        << tipoMercadoria << ": "
        << especie << endl;

}

/***************************************************************************************************************/

void Camiao_animal::imprimirFicheiro(ostream& out) const
{
    out << matricula<<endl;
    out<<marca<<endl;
    out<<modelo<<endl;
    out<<ano<<endl;
    out<<capacidade<<endl;
    out<<"animais"<<endl;
    out<<especie<<endl;
}

/***************************************************************************************************************/

string Camiao::getSegundoCampo()
{
    return "";
}

/***************************************************************************************************************/

string Camiao_congelados::getSegundoCampo()
{
    return to_string(temperatura);
}

/***************************************************************************************************************/

string Camiao_perigo::getSegundoCampo()
{
    return nivel;
}

/***************************************************************************************************************/

string Camiao_animal::getSegundoCampo()
{
    return especie;
}

/***************************************************************************************************************/
