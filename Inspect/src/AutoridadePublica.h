//
// Created by Amanda  on 05/06/20.
//

#pragma once

#include <cstddef>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>


#include "Brigada.h"
#include "utils.h"

using namespace std;

/** Autoridade:
	num_brigadas: Nº total de brigadas (actualizar quando se insere ou apaga)
	num_agentes: Nº total de agentes económicos (actualizar quando se insere ou apaga)

     id_control_briagada: variável estática que é incrementada sempre que se adiciona uma brigada ou se está a meter no map as brigadas)

     id_control_agente_economico: variável estática que é incrementada sempre que se adiciona um agente económico ou se está a meter no map os agentes económicos.

    Mapas com as brigadas e agentes económicos que autoridade pública tem ao seu encargo
	  brigadas:  unordered_map com ID de cada brigada e a brigada respectiva com brigadas
	    brigadas: unordered_map com ID de cada agente económico e o agente económico respectivo

 */
class AutoridadePublica {
private:
    unsigned int idNo;
    size_t num_brigadas;
    size_t num_agentes;

    size_t id_control_briagada = 0;
    size_t id_control_agente_economico = 0;
    unordered_map<unsigned int, Brigada *> brigadas;
    unordered_map<unsigned int, AgenteEconomico *> agentes;



public:
        AutoridadePublica();
        AutoridadePublica(size_t  num_brigadas, size_t num_agentes): num_brigadas(num_brigadas), num_agentes(num_agentes){};

        unsigned int getIdNo() const { return idNo;}
        bool setIdNo(unsigned int idNo){ this->idNo = idNo;}


    /**
 * "Destructor" da autoridade pública que escreve a informação toda em ficheiros e depois liberta a memória alocada.
 */
    void destrutor();

    /**
     * Função que lê a informação do ficheiro agentes.txt e processa essa informação
     * @return mapa desordenado com os agentes
     */
    unordered_map<unsigned int, AgenteEconomico *> processarFicheiroAgentes();

    /**
     * Função que lê a informação do ficheiro brigadas.txt e processa essa informação
     * @return mapa desordenado com as brigadas
     */
    unordered_map<unsigned int, Brigada *> processarFicheiroBrigadas();

    /**Função que retorna mapa com as brigadas sinalizadas pelo seu id
     *
     * @return mapa desordenado com as brigadas
     */
    unordered_map<unsigned int, Brigada *> get_brigadas() const { return brigadas; };

    /**Função para substituir mapa com brigadas da autoridade pública
     *
     * @param  novo mapa com brigadas a ser introduzido
     */
    void set_brigadas(unordered_map<unsigned int, Brigada *> brigadas) { this->brigadas = brigadas; };

    /**Função com mapa que tem agentes económicos sinalizados com o id de cada Agente económico
     *
     * @return mapa com agentes económicos
     */
    unordered_map<unsigned int, AgenteEconomico *> get_agentes() const { return agentes; };

    /**Função para substituir mapa da autoridade pública
     *
     * @param  novo mapa com agentes a ser introduzido
     */
    void set_agentes(unordered_map<unsigned int, AgenteEconomico *> agentes) { this->agentes = agentes; };

    /**
     *  Função que imprime na consola informação em relação aos agentes económicas
     */
    void imprimirAgentesEconomicos() const;

    /**
     *  Função que imprime na consola informação em relação às brigadas
     */
    void imprimirBrigadas() const;

    /**
     * Adiciona agente economico ao map agentes
     */
    void adicionarAgenteEconomico();

    /**
     * @param id do agente a ser removido
     */
    void removerAgente(unsigned int id);

    /**
     * Inserir denuncia
     * @param id do agente economico a receber uma denuncia
     */
    void inserirDenuncia(unsigned int id);

    /**
     * Adiciona Brigada ao map brigadas
     */
    void adicionarBrigada();

    /**
    * @param id da brigada a ser removida
    */
    void removerBrigada(unsigned int id);


    //atividade economica

    AtividadeEconomica stringToAE(string atividades_economicas) {
        if (atividades_economicas == "Todas")
            return Todas;
        else if (atividades_economicas == "Obras")
            return Obras;
        else if (atividades_economicas == "Comercial")
            return Comercial;
        else if (atividades_economicas == "Ambiental")
            return Ambiental;
        else if (atividades_economicas == "IntervencaoViaPublica")
            return IntervencaoViaPublica;
        else if (atividades_economicas == "SegurancaSalubridadeEdificacoes")
            return SegurancaSalubridadeEdificacoes;
        else if (atividades_economicas == "GenerosAlimenticios")
            return GenerosAlimenticios;
    }




    void addBrigada(Brigada *brig);
    void addAgenteEcon(AgenteEconomico *AgEcon);

};