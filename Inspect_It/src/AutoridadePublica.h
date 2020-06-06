//
// Created by Amanda  on 05/06/20.
//

#pragma once

#include <cstddef>
#include <unordered_map>
#include "Brigada.h"
#include "AgenteEconomico.h"
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
    size_t num_brigadas;
    size_t num_agentes;

    static size_t id_control_briagada;
    static size_t id_control_agente_economico;
    unordered_map<unsigned int, Brigada> brigadas;
    unordered_map<unsigned int, AgenteEconomico> agentes;


public:


    /**Função que retorna mapa com as brigadas sinalizadaas pelo seu id
     *
     * @return mapa desordenado com as brigadas
     */
    unordered_map<unsigned int, Brigada> get_brigadas() const{return brigadas;};
    /**Função para substituir mapa com brigadas da autoridade pública
     *
     * @param  novo mapa com brigadas a ser introduzido
     */
    void set_brigadas(unordered_map<unsigned int, Brigada> brigadas){this->brigadas = brigadas;};

    /**Função com mapa que tem agentes económicos sinalizados com o id de cada Agente económico
     *
     * @return mapa com agentes económicos
     */
    unordered_map<unsigned int, AgenteEconomico> get_agentes() const{return agentes;};

    /**Função para substituir mapa da autoridade pública
     *
     * @param  novo mapa com agentes a ser introduzido
     */
    void set_agentes(unordered_map<unsigned int, AgenteEconomico> agentes){ this->agentes = agentes;};

};