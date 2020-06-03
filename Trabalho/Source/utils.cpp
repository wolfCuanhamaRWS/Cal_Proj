#include "utils.h"
#include "Excecoes.h"


using namespace std;

/****************************************************************************************************************
                             IMPLEMENTAÇÃO DAS FUNÇÕES RELACIONADAS COM UTILS
****************************************************************************************************************/
string elem_two_spaces(string str)
{
    while (str.find("  ") != string::npos)
    {
        str.erase(str.find("  "), 1);
    }
    return str;
}

/***************************************************************************************************************/

vector<string> string_split(string str, char sep)
{
    vector<string> result;
    string component = "";

    for (int i = 0; i < str.size(); i++)
    {
        char ch = str.at(i);
        if (ch != sep)
        {
            component.append(1, ch);
        }
        else
        {
            component = elem_two_spaces(component);
            if (component.at(component.size() - 1) == ' ') component.pop_back();
            if (component.at(0) == ' ') component.erase(0, 1);
            result.push_back(component);
            component = "";
        }
        if (i == (str.size() - 1))
        {
            component = elem_two_spaces(component);
            if (component.at(component.size() - 1) == ' ') component.pop_back();
            if (component.at(0) == ' ') component.erase(0, 1);
            result.push_back(component);
        }
    }
    return result;
}

/***************************************************************************************************************/

int ZeroPositiveNumber(string str)
{
	if (str.empty() || str.size() > 9)
		throw numInvalido(str);
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			throw numInvalido(str);
	}
	return stoi(str);
}

/***************************************************************************************************************/

int PositiveNumber(string str)
{
	if (str.empty() || str.size() > 9)
		throw numInvalido(str);
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			throw numInvalido(str);
	}
    if (stoi(str) == 0)
        throw numInvalido(str);
	return stoi(str);
}

/***************************************************************************************************************/

int NegativeZeroPositiveNumber(string str)
{
    if(str[0] == '-')
        return -PositiveNumber(str.substr(1, str.size() - 1));
    else
        return ZeroPositiveNumber(str);
}

/***************************************************************************************************************/
bool validadeNIFEmCongurencias(int nif)
{
    int a9 = nif % 10;
    nif = int(nif / 10);
    int a8 = nif % 10;
    nif = int(nif / 10);
    int a7 = nif % 10;
    nif = int(nif / 10);
    int a6 = nif % 10;
    nif = int(nif / 10);
    int a5 = nif % 10;
    nif = int(nif / 10);
    int a4 = nif % 10;
    nif = int(nif / 10);
    int a3 = nif % 10;
    nif = int(nif / 10);
    int a2 = nif % 10;
    nif = int(nif / 10);
    int a1 = nif % 10;

    int soma = (9 * a1) + (8 * a2) + (7 * a3) + (6 * a4) + (5 * a5) + (4 * a6) + (3 * a7) + (2 * a8) + (a9);

    if((soma % 11) == 0)
        return true;
    else
        return false;

}

/***************************************************************************************************************/

int validadeNIF(string pedido, Empresa &empresa, bool adicionar)
{
    int counter;
	int nif;
	string str;
	do
	{
        counter = 0;
		cout << pedido;
		getline(cin, str);
		if (str.empty())
			return 0;
		if (str.size() == 9)
		{
			nif = PositiveNumber(str);
			if (nif != -1)
			{
			    try
			    {
                    empresa.procuraNifClientes(nif);
			    }
			    catch (clienteInexistente &e)
			    {
                    counter++;
			    }
			    try
			    {
                    empresa.procuraNifFuncionarios(nif);
			    }
			    catch(funcionarioInexistente &e)
                {
			        counter++;
                }
			    if((adicionar && counter == 2) || (!adicionar && counter == 1))
			        if(validadeNIFEmCongurencias(nif))
                        return nif;
			}
		}
		cout << "\nIntroduza um NIF valido.\n";
	} while (true);
}

/***************************************************************************************************************/

string validadeMatricula(string pedido, Empresa &empresa, bool adicionar)
{
	string str;
	int counter;
	do
	{
	    counter = 0;
		cout << pedido;
		getline(cin, str);
		if (str.empty())
			return "";
		if (str.size() == 8 && isdigit(str[0]) && isdigit(str[1]) && str[2] == '-' && isdigit(str[3]) && isdigit(str[4]) && str[5] == '-'  && isalpha(str[6]) && isalpha(str[7]))
        {
            try {
                empresa.procuraMatriculaCamiao(str);
            }
            catch (camiaoInexistente &e) {
                counter++;
            }
		    if ((adicionar && counter == 1) || (!adicionar && counter == 0))
		        return str;
        } // NN-NN-LL
		cout << "\nIntroduza uma matricula valida.\n";
	} while (true);
}

/***************************************************************************************************************/


float validadeSalario(string input)
{
    int dot_counter=0;
    for (int i=0;i<input.size();i++)
    {
        if (input[i]== '.') dot_counter++;
        if (!isdigit(input[i]) && input[i]!= '.') throw numInvalido(input);
    }
    if (dot_counter != 1) throw numInvalido(input);
    return stof(input);
}

/***************************************************************************************************************/


string calculaHoraFinal(string inicio, string duracao)
{
    string fim;
    vector<string> hora_inicio_sep = string_split(inicio, ':'), duracao_sep = string_split(duracao, ':');
    vector<int> hora_final_sep = {stoi(hora_inicio_sep[0]) + stoi(duracao_sep[0]), stoi(hora_inicio_sep[1]) + stoi(duracao_sep[1])};
    if (hora_final_sep[1] >= 60)
    {
        hora_final_sep[1] -= 60;
        hora_final_sep[0]++;
        if (hora_final_sep[0] == 24)
            hora_final_sep[0] = 0;
    }
    fim = to_string(hora_final_sep[0]) + ":";
    if(hora_final_sep[1] < 10)
        fim += "0";
    fim += to_string(hora_final_sep[1]);
    return fim;
}