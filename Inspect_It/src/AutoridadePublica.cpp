#include "AutoridadePublica.h"

/****************************************************************************************************************
                            IMPLEMENTAÇÃO DAS FUNÇÕES RELACIONADAS COM Data todo data??????
****************************************************************************************************************/

AutoridadePublica::AutoridadePublica() {
    this->agentes = processarFicheiroAgentes();
    this->brigadas = processarFicheiroBrigadas();

}

/***************************************************************************************************************/

unordered_map<unsigned int, AgenteEconomico *> AutoridadePublica::processarFicheiroAgentes() {

    string input;
    unsigned int id, pos, num_graves, num_total, num_aprovadas, num_reprovadas;
    AtividadeEconomica atividade;
    float area;
    pair<unsigned int, unsigned int> horario_funcionamento;
    unordered_map<unsigned int, AgenteEconomico *> result;

    ifstream ficheiro("src/text/agentes.txt");

    if (!ficheiro.fail()) {
        while (!ficheiro.eof()) {
            //separador
            getline(ficheiro, input);

            //identificacao do agente
            getline(ficheiro, input);
            id = stoi(input);

            //atividade económica
            getline(ficheiro, input);
            if (input == "Todas")
                atividade = Todas;
            else if (input == "Obras")
                atividade = Obras;
            else if (input == "Comercial")
                atividade = Comercial;
            else if (input == "Ambiental")
                atividade = Ambiental;
            else if (input == "IntervencaoViaPublica")
                atividade = IntervencaoViaPublica;
            else if (input == "SegurancaSalubridadeEdificacoes")
                atividade = SegurancaSalubridadeEdificacoes;
            else if (input == "GenerosAlimenticios")
                atividade = GenerosAlimenticios;

            //area
            getline(ficheiro, input);
            area = stof(input);

            //horário funcionamento
            getline(ficheiro, input);
            pos = input.find('-');
            horario_funcionamento.first = stoi(input.substr(0, pos));
            input = input.substr(pos + 1, string::npos);
            horario_funcionamento.second = stoi(input);

            //número de denúncias graves
            getline(ficheiro, input);
            num_graves = stoi(input);

            //número de denúncias total
            getline(ficheiro, input);
            num_total = stoi(input);

            //número de denúncias aprovadas
            getline(ficheiro, input);
            num_aprovadas = stoi(input);

            //número de denúncias total
            getline(ficheiro, input);
            num_reprovadas = stoi(input);

            //denuncias
            Denuncias *denuncias = new Denuncias(num_graves, num_total);

            //inspeções
            Inspecoes *inspecoes = new Inspecoes(num_aprovadas, num_reprovadas);

            //Data última inspeção
            getline(ficheiro, input);
            Data *data = new Data(input);

            //Agente económico
            auto *agente = new AgenteEconomico(id, atividade, area, horario_funcionamento, denuncias, inspecoes, data);
            result[id] = agente;

        }
    } else {cout << "Erro na abertura do ficheiro agentes.txt " << endl;}
    return result;
}

/***************************************************************************************************************/

void AutoridadePublica::imprimirAgentesEconomicos() const {
    cout << "ID | ATIVIDADE ECONOMICA | AREA | HORARIO FUNCIONAMENTO | NUM GRAVES | NUM TOTAL | APROVADAS | REPROVADAS"
         << endl;

    for (auto itr = agentes.begin(); itr != agentes.end(); ++itr) {
        cout << (*itr).second->get_id() << " | "
             << (*itr).second->getAtividadeString() << " | "
             << (*itr).second->get_area() << " | "
             << (*itr).second->get_horario_funcionamento().first << "-"
             << (*itr).second->get_horario_funcionamento().second << " | "
             << (*itr).second->getDenuncias()->get_num_graves() << " | "
             << (*itr).second->getDenuncias()->get_num_total() << " | "
             << (*itr).second->getInspecoes()->get_num_aprovadas() << " | "
             << (*itr).second->getInspecoes()->get_num_reprovadas() << endl;

    }

}

/***************************************************************************************************************/

unordered_map<unsigned int, Brigada *> AutoridadePublica::processarFicheiroBrigadas() {
    ifstream ficheiro;
    string input;
    unsigned int id, horas_trabalho, hora_inicio;
    AtividadeEconomica atividade;
    unordered_map<unsigned int, Brigada *> result;

    ficheiro.open("src/text/brigadas.txt");
    if (!ficheiro.fail()) {

        while (!ficheiro.eof()) {
            //separador
            getline(ficheiro, input);

            //identificacao da brigada
            getline(ficheiro, input);
            id = stoi(input);

            //atividade económica
            getline(ficheiro, input);
            if (input == "Todas")
                atividade = Todas;
            else if (input == "Obras")
                atividade = Obras;
            else if (input == "Comercial")
                atividade = Comercial;
            else if (input == "Ambiental")
                atividade = Ambiental;
            else if (input == "IntervencaoViaPublica")
                atividade = IntervencaoViaPublica;
            else if (input == "SegurancaSalubridadeEdificacoes")
                atividade = SegurancaSalubridadeEdificacoes;
            else if (input == "GenerosAlimenticios")
                atividade = GenerosAlimenticios;

            //horas de trabalho
            getline(ficheiro, input);
            horas_trabalho = stoi(input);

            //hora inicio
            getline(ficheiro, input);
            hora_inicio = stoi(input);

            //Brigada
            auto *brigada = new Brigada(id, atividade, horas_trabalho, hora_inicio);
            result[id] = brigada;

        }
    } else { cout << "Erro na abertura do ficheiro brigadas.txt " << endl; }
    return result;
}

/***************************************************************************************************************/

void AutoridadePublica::imprimirBrigadas() const {
    cout << "ID | ATIVIDADE ECONOMICA | NUMERO HORAS TRABALHO | HORA INICIO" << endl;

    for (auto itr = brigadas.begin(); itr != brigadas.end(); ++itr) {
        cout << (*itr).second->get_id() << " | "
             << (*itr).second->getAtividadeString_() << " | "
             << (*itr).second->get_horas_trabalho() << " | "
             << (*itr).second->get_hora_inicio() << endl;

    }


}

/***************************************************************************************************************/

void AutoridadePublica::adicionarAgenteEconomico() {
    cout << "=====================================================================================" << endl
         << "                                NOVO AGENTE ECONOMICO                                " << endl
         << "=====================================================================================" << endl;


}

/***************************************************************************************************************/

void AutoridadePublica::removerAgente() {

}

/***************************************************************************************************************/

void AutoridadePublica::inserirDenuncia() {

    /*

    cout << "Digite o nome agente economico [EXIT 0]: " << endl;

    getline(cin, nome);

    //(!autoridadePublica.check_Agente_Economico_Existe_por_nome(nome)){}//todo conferir se ao agente economico existe?
    if (nome == "0") { return; }


    //cin gravidade d a denuncia
    int gravidade;

    cout << "Digite a Gravidade [EXIT 0]: " << endl;
    cout << "(Leve - 1, Moderada - 2, Grave - 3, Muito Grave - 4)" << endl;
    gravidade = checkOption(0, 4);
    if (gravidade == 0) return;   //abort option



    //cin especialidade
    string especialidade;

    cout << "Digite a especialidade [EXIT 0]: " << endl;
    getline(cin, especialidade); //todo checar se essa especialide existe no agenteEconomico
    if (especialidade == "0") { return; }


//    Denuncia *denuncia =new Denuncia(especialidade
//    autoridadePublica.add_denucia(denuncia);
     */

}

/***************************************************************************************************************/

void AutoridadePublica::adicionarBrigada() {
    cout << "=====================================================================================" << endl
         << "                                 NOVA BRIGADA                                        " << endl
         << "=====================================================================================" << endl;
    unsigned int id, horas_trabalho, hora_inicio;


    //Brigada(unsigned  int identificacao, AtividadeEconomica atividades_economicas, unsigned int horas_trabalho, unsigned int hora_inicio);

}

/***************************************************************************************************************/

void AutoridadePublica::removerBrigada() {

}

/***************************************************************************************************************/
