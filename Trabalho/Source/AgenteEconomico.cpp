#include "../Header/AgenteEconomico.h"

AgenteEconomico::AgenteEconomico(string nome, pair<int, int> intervalo_funcionamento, vector<Denuncia> denuncias,
                                 vector<string> atividades_economicas, vector<pair<Denuncia, bool>> inspecoes)
{
    //Processamento das informações do ficheiro agente_economico.txt



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

void AgenteEconomico::set_horario_funcionamento(int &abertura, int &fechado) {
    intervalo_funcionamento.first = abertura;
    intervalo_funcionamento.second =  fechado;
}


