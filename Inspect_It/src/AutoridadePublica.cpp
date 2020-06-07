#include <iomanip>
#include <algorithm>
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

            //id do agente
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
    } else { cout << "Erro na abertura do ficheiro agentes.txt " << endl; }
    return result;
}

/***************************************************************************************************************/

void AutoridadePublica::imprimirAgentesEconomicos() const {
    cout << "ID | ATIVIDADE ECONOMICA | AREA | HORARIO FUNCIONAMENTO | NUM GRAVES | NUM TOTAL | APROVADAS | REPROVADAS"
         << endl;

    for (auto itr = agentes.begin(); itr != agentes.end(); ++itr) {
        cout << setw(2) << (*itr).second->get_id() << " | "
             << setw(5) << (*itr).second->getAtividadeString() << " | "
             << setw(4) << (*itr).second->get_area() << " | "
             << setw(4) << (*itr).second->get_horario_funcionamento().first << "-"
             << setw(2) << (*itr).second->get_horario_funcionamento().second << " | "
             << setw(2) << (*itr).second->getDenuncias()->get_num_graves() << " | "
             << setw(2) << (*itr).second->getDenuncias()->get_num_total() << " | "
             << setw(2) << (*itr).second->getInspecoes()->get_num_aprovadas() << " | "
             << setw(2) << (*itr).second->getInspecoes()->get_num_reprovadas() << endl;

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

            //id da brigada
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
            this->id_control_briagada = id;
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

    //cin atividade economica
    string atividadeEconomica;
    cout << "Escreva a atividade economica do agente que deseja adicionar" << endl;
    cout << "OPCOES:" << endl;
    cout << " - Todas" << endl
         << " - Obras" << endl
         << " - Comercial" << endl
         << " - Ambiental" << endl
         << " - IntervencaoViaPublica" << endl
         << " - SegurancaSalubridadeEdificacoes" << endl
         << " - GenerosAlimenticios" << endl;
    cin >> atividadeEconomica;

    //cin area
    float area;
    cout << "Escreva a area do estabelecimento" << endl;
    cin >> area;

    //cin horario de funcionamento
    unsigned int inicio, fim;
    cout << "Escreva o horario de funcionamentp:" << endl;
    cout << "Hora de inicio:" << endl;
    cin >> inicio;
    cout << "Hora de encerramento:";
    cin >> fim;
    pair<unsigned int, unsigned int> horario_funcionamento(inicio, fim);


    //Denuncias
    unsigned int graves, total;
    cout << "Escreva informacoes sobre as denuncias desse agente economico" << endl;
    cout << "Numero total de denuncias do estabelecimento:" << endl;
    cin >> total;
    cout << "Destas denuncias quantas sao graves?" << endl;
    cin >> graves;
    auto *denuncias = new Denuncias(graves, total);


    //inpecoes
    unsigned int aprovadas, falhas;
    cout << "Escreva informacoes sobre as Inspecoes" << endl;
    cout << "Numero de inspecoes aprovadas:" << endl;
    cin >> aprovadas;
    cout << "Numero de inpecoes reprovadas" << endl;
    cin >> falhas;
    auto *inpecoes = new Inspecoes(aprovadas, falhas);

    //Data da ultima inspecao
    string data;
    cout << "Qual foi a data da ultima inspecao? formato[yyyy/mm/dd]" << endl;
    cin >> data;
    auto *dataUI = new Data(data);
    this->id_control_agente_economico++;

    auto *agente = new AgenteEconomico(id_control_agente_economico, stringToAE(atividadeEconomica), area,
                                       horario_funcionamento, denuncias, inpecoes, dataUI);
    this->agentes[id_control_agente_economico] = agente;

    cout<<"Agente economico adicionado com sucesso!"<<endl;

    //reescreverAgentes();


}

/***************************************************************************************************************/

void AutoridadePublica::removerAgente(unsigned int id) {
    this->agentes.erase(id);
    cout<<"Agente economico removido com sucesso!"<<endl;
    //reescreverAgentes();
}

/***************************************************************************************************************/

void AutoridadePublica::inserirDenuncia(unsigned int id) {
    unsigned int gravidade;
    cout << "Escolha o grau da denuncia: " << endl
         << "Leve ou Comum[0]" << endl
         << "Grave ou de Urgencia[1]" << endl;
    gravidade = checkOption(0, 1);
    if (gravidade == 0) {
        this->agentes[id]->getDenuncias()->adicionar_uma_normal();


    } else {
        this->agentes[id]->getDenuncias()->adicionar_uma_grave();

    }
    cout<<"Denuncia inserida com sucesso!"<<endl;
    //reescreverAgentes();
}

/***************************************************************************************************************/

void AutoridadePublica::adicionarBrigada() {
    cout << "=====================================================================================" << endl
         << "                                 NOVA BRIGADA                                        " << endl
         << "=====================================================================================" << endl;


    //cin atividade economica
    string atividadeEconomica;
    cout << "Escreva a tividade economica da brigada" << endl;
    cout << "OPCOES:" << endl;
    cout << " - Todas" << endl
         << " - Obras" << endl
         << " - Comercial" << endl
         << " - Ambiental" << endl
         << " - IntervencaoViaPublica" << endl
         << " - SegurancaSalubridadeEdificacoes" << endl
         << " - GenerosAlimenticios" << endl;
    cin >> atividadeEconomica;

    //cin horas de trabalho
    cout << "Escreva quantas horas o comercio permanece aberto" << endl;
    cout << "(obs. n a possibilidade de colocar minutos, caso seja necessrio aredonde para cima)" << endl;
    unsigned int horas_trabalho = checkOption(1, 24);

    //cin horario de inicio
    cout << "Escreva o horario de abertura do comercio" << endl;
    cout << "(obs. n a possibilidade de colocar minutos, caso seja necessrio aredonde para cima)" << endl;
    unsigned int hora_inico = checkOption(0, 24);//todo problema horario de abertura n n aceita

    this->id_control_briagada++;
    auto *brigada = new Brigada(id_control_briagada, stringToAE(atividadeEconomica), horas_trabalho, hora_inico);
    this->brigadas[id_control_briagada] = brigada;
    cout<<"Brigada inserida com sucesso!"<<endl;
    reescreverBrigadas();
}

/***************************************************************************************************************/

void AutoridadePublica::removerBrigada(unsigned int id) {
    this->brigadas.erase(id);
    cout<<"Brigada removida com sucesso!"<<endl;
    reescreverBrigadas();
}

/***************************************************************************************************************/

void AutoridadePublica::reescreverBrigadas() {
    //criandp a vector de keys(ids) ordenadas
    vector<unsigned  int > keys;

    keys.reserve (this->brigadas.size());
    for (auto& it : this->brigadas) {
        keys.push_back(it.first);
    }
    sort (keys.begin(), keys.end());


    ofstream  file("src/text/brigadas.txt");

    for(auto  it : keys) {
        auto *brigada =  brigadas[it];
        file<<"::::::::::::::::::::::::::"<<endl
           << brigada->get_id()<<endl
           <<brigada->getAtividadeString_()<<endl
           <<brigada->get_horas_trabalho()<<endl
           <<brigada->get_hora_inicio()<<endl;

    }
    file.close();




}

/***************************************************************************************************************/

void AutoridadePublica::reescreverAgentes() {
    //criandp a vector de keys(ids) ordenadas
    vector<unsigned  int > keys;

    keys.reserve (this->agentes.size());
    for (auto& it : this->agentes) {
        keys.push_back(it.first);
    }
    sort (keys.begin(), keys.end());

    ofstream file;
    file.open("src/text/agentes.txt");

    for(auto  it : keys) {
        auto *agente =  agentes[it];

        file<<"::::::::::::::::::::::::::"<<endl
            << to_string( agente->get_id() )<<endl
            <<agente->get_area()<<endl
            <<agente->get_horario_funcionamento().first<<"-"<< agente->get_horario_funcionamento().second<<endl
            <<agente->getDenuncias()->get_num_graves()<<endl
            <<agente->getDenuncias()->get_num_total()<<endl
            <<agente->getInspecoes()->get_num_aprovadas()<<endl
            <<agente->getInspecoes()->get_num_reprovadas()<<endl
            <<agente->getDataUi()->getData()<<endl;
    }
    file.close();



}


/***************************************************************************************************************/


