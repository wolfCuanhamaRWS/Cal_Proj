//
// Created by Amanda  on 05/06/20.
//

#include "AgenteEconomico.h"



AgenteEconomico:: AgenteEconomico(){};
AgenteEconomico::AgenteEconomico(const unsigned int id , const AtividadeEconomica &atividadesEconomicas, float area, const pair<unsigned int, unsigned int> &horario_funcionamento, Denuncias *denuncias,Inspecoes *inspecoes, Data *dataUI,int idNo ){

    this-> id = id;
    this->idNo = idNo;
    this-> atividades_economicas = atividadesEconomicas;
    this-> area = area;
    this-> horario_funcionamento = horario_funcionamento;

    this->denuncias = denuncias;
    this-> inspecoes = inspecoes;
    tmpInspecao = gerarTmpInspecao();
    this->dataUI = dataUI;
}


AgenteEconomico::AgenteEconomico(unsigned int id, const AtividadeEconomica &atividadesEconomicas, float area,
                const pair<unsigned int, unsigned int> &horario_funcionamento, Denuncias *denuncias,
                Inspecoes *inspecoes, Data *dataUI) {

    this->atividades_economicas = atividadesEconomicas;
    this->area = area;
    this->horario_funcionamento = horario_funcionamento;
    this->denuncias = denuncias;
    this->inspecoes = inspecoes;
    this->tmpInspecao = gerarTmpInspecao();
    this->dataUI = dataUI;
    this->id = id;
}


string AgenteEconomico :: getAtividadeString() const {
    if (atividades_economicas == Todas)
        return "Todas";
    else if (atividades_economicas == Obras)
        return "Obras";
    else if (atividades_economicas == Comercial)
        return "Comercial";
    else if (atividades_economicas == Ambiental)
        return "Ambiental";
    else if (atividades_economicas == IntervencaoViaPublica)
        return "IntervencaoViaPublica";
    else if (atividades_economicas == SegurancaSalubridadeEdificacoes)
        return "SegurancaSalubridadeEdificacoes";
    else if (atividades_economicas == GenerosAlimenticios)
        return "GenerosAlimenticios";
    else
        return "";
}


/**
     * Escreve para uma ostream out (neste caso, o ficheiro agentes.txt) o valor dos atributos com a formatação necessária em ficheiros
     * @param out A stream de output para onde serão escritos os valores dos atributos
     */
void AgenteEconomico :: imprimirFicheiro(ostream &out) const {
    out <<"::::::::::::::::::::::::::" << endl
        << get_id() << endl
        << getAtividadeString() << endl
        << get_area() << endl
        << get_horario_funcionamento().first << "-" << get_horario_funcionamento().second << endl
        << getDenuncias()->get_num_graves() << endl
        << getDenuncias()->get_num_total() << endl
        << getInspecoes()->get_num_aprovadas() << endl
        << getInspecoes()->get_num_reprovadas() << endl
        << getDataUi()->getData() << endl
        << get_idNo() << endl;
}




