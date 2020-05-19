//
// Created by Amanda  on 12/05/20.
//

#include "AgenteEconomico.h"

AgenteEconomico::AgenteEconomico(vector<string> especialidades) {
    this->especialidade = especialidades;
}

void AgenteEconomico::add_inspecao(Denuncia &denuncia, bool &resultado) {
    inspecoes.push(pair<Denuncia, bool>(denuncia, resultado));

}
int AgenteEconomico::get_horario_abertura() {
    return intervalo_funcionamento.first;
}
int AgenteEconomico::get_horario_fechamento() {
    return intervalo_funcionamento.second;
}
bool  AgenteEconomico::get_resultado_ultima_visita() {
    return  inspecoes.top().second;
}

stack<pair<Denuncia, bool>> AgenteEconomico::get_inspecoes() {
    return inspecoes;
}

int AgenteEconomico::get_numero_visitas() {
    return  numero_de_visitas;
}

int AgenteEconomico::set_horario_funcionamento(int &abertura, int &fechado) {
    intervalo_funcionamento.first = abertura;
    intervalo_funcionamento.second =  fechado;
}
