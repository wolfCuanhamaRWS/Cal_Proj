#ifndef CAL_DATA_H
#define CAL_DATA_H

#include <string>

using namespace std;

class Data
{
private:
    ///Dia
    int dia;
    ///Mês
    int mes;
    ///Ano
    int ano;

public:
    /**
     * Constructor de data que recebe uma string do utilizador, divide-a e coloca-a os respetivos valores nas variáveis.
     * @param string ano_mes_dia Data em formato aaaa/mm/dd
    **/
    Data(string ano_mes_dia);

    /**
     * Constructor de data com um parâmetro por cada componente de uma data.
     * @param ano Ano
     * @param mes Mês
     * @param dia Dia
     **/
    Data(int ano, int mes, int dia);

    // Metodos GET
    /**
     * Devolve o dia.
     * @return Dia
     **/
    int getDia() const;

    /**
     * Devolve o mês.
     * @return Mês
     **/
    int getMes() const;
    /**
     * Devolve o ano.
     * @return Ano
     **/
    int getAno() const;
    /**
     * Devolve uma data.
     * @return Data no formato AAAA/MM/DD
     **/
    string getData() const;

    // Metodos SET
    /**
     * Altera o valor do dia.
     * @param dia Dia
     **/
    void setDia(int dia);
    /**
     * Altera o valor do mês.
     * @param mes Mês
     **/
    void setMes(int mes);
    /**
     * Altera o valor do ano.
     * @param ano Ano
     **/
    void setAno(int ano);
    /**
     * Altera os valores de todos os componentes da data.
     * @param ano Ano
     * @param mes Mês
     * @param dia Dia
     **/
    void setData(int ano, int mes, int dia);
    // Outros metodos
    /**
     * Mostra a data na consola no formato AAAA/MM/DD.
     **/
    void imprime() const;
    /**
     * Verifica se uma dada data é válida.
     * @return Verdadeiro se a data for válida ou falso caso não seja
     **/
    bool validade() const;
    /**
     * Retorna o número de dias de um determinado mês dado.
     * @param mes Mês a avaliar
     * @return Número de dias que o mês dado contém
     **/
    unsigned int numDias(unsigned int mes) const;
    /**
     * Verifica se duas datas são iguais.
     * @param date Data a comparar
     * @return Verdadeiro se as datas forem iguais, falso caso isto não se verifique
     */
    bool isEqualTo(const Data &date);

    /**
     * Função que conta o número de dias numa data desde o nascimento de Cristo.
     * @return Número de dias desde o nascimento de Cristo
     */
    unsigned long int numDiasDesdeCristo()const;

    /**
     * Incrementa o objecto Data, incrementando o dia, o mês e o ano.
	 * @return Data incrementada
	*/
    Data& operator++();

    /**
     * Overload do operador == para comparar datas.
     * @param lhs Elemento à esquerda do operador
     * @param rhs Elemento à direita do operador
     * @return Booleano que indica o valor da comparação
     */
    friend bool operator==(const Data& lhs, const Data& rhs);
    /**
     * Overload do operador != para comparar datas.
     * @param lhs Elemento à esquerda do operador
     * @param rhs Elemento à direita do operador
     * @return Booleano que indica o valor da comparação
     */
    friend bool operator!=(const Data& lhs, const Data& rhs);
    /**
     * Overload do operador < para comparar datas.
     * @param lhs Elemento à esquerda do operador
     * @param rhs Elemento à direita do operador
     * @return Booleano que indica o valor da comparação
     */
    friend bool operator<(const Data& lhs, const Data& rhs);
    /**
     * Overload do operador > para comparar datas.
     * @param lhs Elemento à esquerda do operador
     * @param rhs Elemento à direita do operador
     * @return Booleano que indica o valor da comparação
     */
    friend bool operator>(const Data& lhs, const Data& rhs);
    /**
     * Overload do operador <= para comparar datas.
     * @param lhs Elemento à esquerda do operador
     * @param rhs Elemento à direita do operador
     * @return Booleano que indica o valor da comparação
     */
    friend bool operator<=(const Data& lhs, const Data& rhs);
    /**
     * Overload do operador >= para comparar datas.
     * @param lhs Elemento à esquerda do operador
     * @param rhs Elemento à direita do operador
     * @return Booleano que indica o valor da comparação
     */
    friend bool operator>=(const Data& lhs, const Data& rhs);

};

//retorna true se data1 estiver depois de data2
//retorna falso caso contrário
bool estaDepois (Data* data1, Data* data2);


#endif //CAL_DATA_H

