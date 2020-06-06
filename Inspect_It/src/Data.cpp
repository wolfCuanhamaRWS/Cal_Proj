


#include "Data.h"
#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

/****************************************************************************************************************
                            IMPLEMENTAÇÃO DAS FUNÇÕES RELACIONADAS COM Data
****************************************************************************************************************/
Data::Data(int ano, int mes, int dia)
{
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

/***************************************************************************************************************/

Data::Data(string ano_mes_dia)
{
    vector<string> componentesData = string_split(ano_mes_dia,'/');
    this -> ano = stoi(componentesData.at(0));
    this -> mes = stoi(componentesData.at(1));
    this -> dia = stoi(componentesData.at(2));
}

/***************************************************************************************************************/

int Data::getAno() const
{
    return ano;
}

/***************************************************************************************************************/

int Data::getMes() const
{
    return mes;
}

/***************************************************************************************************************/

int Data::getDia() const
{
    return dia;
}

/***************************************************************************************************************/

string Data::getData() const
{
    string m = to_string(mes);
    if (m.size() == 1)
        m = "0" + m;
    string d = to_string(dia);
    if (d.size() == 1)
        d = "0" + d;
    return (to_string(ano) + '/' + m + '/' + d);
}

/***************************************************************************************************************/

void Data::setAno(int ano)
{
    this -> ano = ano;
}

/***************************************************************************************************************/

void Data::setMes(int mes)
{
    this -> mes = mes;
}

/***************************************************************************************************************/

void Data::setDia(int dia)
{
    this -> dia = dia;

}

/***************************************************************************************************************/

void Data::setData(int ano, int mes, int dia)
{
    this -> ano = ano;
    this -> mes = mes;
    this -> dia = dia;
}

/***************************************************************************************************************/

void Data::imprime() const
{
    if (validade())
    {
        cout << getData();
    }
}

/***************************************************************************************************************/

unsigned int Data::numDias (unsigned int mes) const
{
    bool leap;

    if (ano % 400 == 0) leap = true;
    else
    {
        if (ano % 4 == 0 && ano % 100 != 0) leap = true;
        else leap = false;
    }

    switch (mes)
    {
        case 1: {return 31; }
        case 2:
        {
            if (leap) return 29;
            else return 28;
        }
        case 3: {return 31; }
        case 4: {return 30; }
        case 5: {return 31; }
        case 6: {return 30; }
        case 7: {return 31; }
        case 8: {return 31; }
        case 9: {return 30; }
        case 10: {return 31; }
        case 11: {return 30; }
        case 12: {return 31; }
        default:cout << "ERRO!" << endl;
    }
    //ZEZE tive que meter isto aqui
    return 0;
}

/***************************************************************************************************************/

bool Data::validade() const
{
    if (mes < 1 || mes > 12)
    {
        cout << "Mes invalido!" << endl;
        return false;
    }
    if (dia < 1 || dia > Data::numDias(mes))
    {
        cout <<  "Dia invalido!" << endl;
        return false;
    }
    if (ano < 0)
        return false;

    return true;

}

/***************************************************************************************************************/

bool Data::isEqualTo(const Data &date)
{
    return date.ano == this->ano && date.mes == this->mes && date.dia == this->dia;
}

/***************************************************************************************************************/

bool estaDepois(Data* data1, Data* data2)
{
    if (data1->getAno() > data2->getAno())
    {
        return true;
    }
    else if (data1->getAno() < data2->getAno())
    {
        return false;
    }
    else // (this-> ano == date.ano)
    {
        if (data1->getMes() > data2->getMes())
        {
            return true;
        }
        else if(data1->getMes() < data2->getMes())
        {
            return false;
        }
        else // (this->mes == date.mes)
        {
            if (data1->getDia() > data2->getDia())
            {
                return true;
            }
            else if (data1->getDia() < data2->getDia())
            {
                return false;
            }
            else
            {
                return false;
            }
        }
    }

}

/***************************************************************************************************************/

unsigned long int Data::numDiasDesdeCristo()const
{
    long int result = 0;
    long int leapanoNum = 0;

    leapanoNum += (int)ano / 4;
    leapanoNum -= (int)ano / 10;
    leapanoNum += (int)ano / 400;

    result += leapanoNum * 366;
    result += (ano - leapanoNum) * 365;

    bool leap;

    if (ano % 400 == 0) leap = true;
    else
    {
        if (ano % 4 == 0 && ano % 100 != 0) leap = true;
        else leap = false;
    }

    for (int i = 1; i < mes; i++)
    {
        switch (i)
        {
            case 1: {result += 31; break; }
            case 2:
            {
                if (leap) result += 29;
                else result += 28;
                break;
            }
            case 3: {result += 31; break; }
            case 4: {result += 30; break; }
            case 5: {result += 31; break; }
            case 6: {result += 30; break; }
            case 7: {result += 31; break; }
            case 8: {result += 31; break; }
            case 9: {result += 30; break; }
            case 10: {result += 31; break; }
            case 11: {result += 30; break; }
            case 12: {result += 31; break; }
            default:cout << "ERRO! Valor invalido.\n";
        }
    }

    result += dia;

    return result;
}

/***************************************************************************************************************/

Data& Data::operator++()
{
    //Data tmp = Data(ano, mes, dia);
    if (dia == numDias(mes))
    {
        dia = 1;
        if (mes == 12)
        {
            mes = 1;
            ano = ano + 1;
        }
        else
        {
            mes = mes + 1;
        }
    }
    else
    {
        dia = dia + 1;
    }
    //return tmp;
    return *this;
}

/***************************************************************************************************************/

bool operator==(const Data& lhs, const Data& rhs)
{
    return lhs.dia == rhs.dia && lhs.mes == rhs.mes && lhs.ano == rhs.ano;
}

/***************************************************************************************************************/

bool operator!=(const Data& lhs, const Data& rhs)
{
    return lhs.dia != rhs.dia || lhs.mes != rhs.mes || lhs.ano != rhs.ano;
}

/***************************************************************************************************************/

bool operator<(const Data& lhs, const Data& rhs)
{
    return lhs.ano < rhs.ano ||
           (lhs.ano == rhs.ano && lhs.mes < rhs.mes) ||
           (lhs.ano == rhs.ano && lhs.mes == rhs.mes && lhs.dia < rhs.dia);
}

/***************************************************************************************************************/

bool operator>(const Data& lhs, const Data& rhs)
{
    return lhs.ano > rhs.ano ||
           (lhs.ano == rhs.ano && lhs.mes > rhs.mes) ||
           (lhs.ano == rhs.ano && lhs.mes == rhs.mes && lhs.dia > rhs.dia);
}

/***************************************************************************************************************/

bool operator<=(const Data& lhs, const Data& rhs)
{
    return lhs.ano < rhs.ano ||
           (lhs.ano == rhs.ano && lhs.mes < rhs.mes) ||
           (lhs.ano == rhs.ano && lhs.mes == rhs.mes && lhs.dia <= rhs.dia);
}

/***************************************************************************************************************/

bool operator>=(const Data& lhs, const Data& rhs)
{
    return lhs.ano > rhs.ano ||
           (lhs.ano == rhs.ano && lhs.mes > rhs.mes) ||
           (lhs.ano == rhs.ano && lhs.mes == rhs.mes && lhs.dia >= rhs.dia);
}



/***************************************************************************************************************/