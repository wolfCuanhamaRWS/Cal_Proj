//
// Created by Amanda  on 05/06/20.
//

#include "AgenteEconomico.h"


/**
 * Definir tempo de inspeção do agente económico usando a área do mesmo como parâmetro decisor
 *
 * @return te
 */
float AgenteEconomico :: gerarTmpInspecao() {/*Definir tempo de inspeção do agente económico usando a área do mesmo como parâmetro decisor
     *
     */
    if (area <= 50.0) {
        return 0.5;
    } else if (area < 100.0) {
        return 1;
    } else if (area <= 150.0) {
        return 1.5;
    } else {
        return 2.0;

    }
}

AgenteEconomico:: AgenteEconomico() {};
AgenteEconomico::AgenteEconomico(const unsigned int id , const AtividadeEconomica &atividadesEconomicas, float area, pair<unsigned int ,unsigned int > &horario_funcionamento, Denuncias &denuncias, Inspecoes &inspecoes, Data dataUI){

    this-> id = id;
    this-> atividades_economicas = atividadesEconomicas;
    this-> area = area;
    this-> horario_funcionamento = horario_funcionamento;

    this->denuncias = denuncias;
    this -> inspecoes = inspecoes;
    tmpInspecao = gerarTmpInspecao();
    this-> dataUI = dataUI;
}









