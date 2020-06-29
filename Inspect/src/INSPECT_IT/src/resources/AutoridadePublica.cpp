

#include <iomanip>
#include <algorithm>
#include "AutoridadePublica.h"
#include <fstream>

/****************************************************************************************************************
                            IMPLEMENTAÇÃO DAS FUNÇÕES RELACIONADAS COM AutoridadePublica
****************************************************************************************************************/


AutoridadePublica::AutoridadePublica(string ficheiroAgEcono,string ficheiroBrig)
{
    this->agentes = processarFicheiroAgentes(ficheiroAgEcono);
    this->brigadas = processarFicheiroBrigadas(ficheiroBrig);

}

/***************************************************************************************************************/

unordered_map<unsigned int, AgenteEconomico *> AutoridadePublica::processarFicheiroAgentes(string fich) {

    string input;
    unsigned int id, pos, num_graves, num_total, num_aprovadas, num_reprovadas;
    AtividadeEconomica atividade;
    float area;
    pair<unsigned int, unsigned int> horario_funcionamento;
    unordered_map<unsigned int, AgenteEconomico *> result;
    int idNo;

    ifstream ficheiro(fich);

    if (ficheiro.fail())
    {
        cout << "Erro na abertura do ficheiro agentes.txt " << endl;
    }

    while (!ficheiro.eof())
    {
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

        //número de denúncias reprovadas
        getline(ficheiro, input);
        num_reprovadas = stoi(input);

        //denuncias
        Denuncias *denuncias = new Denuncias(num_graves, num_total);

        //inspeções
        Inspecoes *inspecoes = new Inspecoes(num_aprovadas, num_reprovadas);

        //Data última inspeção
        getline(ficheiro, input);
        Data *data = new Data(input);
        getline(ficheiro,input);
        idNo = stoi(input);

        //Agente económico
        auto *agente = new AgenteEconomico(id, atividade, area, horario_funcionamento, denuncias, inspecoes, data,idNo);
        result[id] = agente;

        this->id_control_agente_economico = id;

    }

    return result;
}

/***************************************************************************************************************/
void AutoridadePublica::imprimirAgentesEconomicos() const
{
    cout << "ID            |ATIVIDADE ECONOMICA               |AREA         |HORARIO FUNCIONAMENTO |Nº DENÚNCIAS GRAVES |Nº TOTAL DENÚNCIAS|APROVADAS      |REPROVADAS      |URGÊNCIA DE INSPEÇÃO|ID NÓ      "
         << endl;

    int area_size;
    for (auto itr = agentes.begin(); itr != agentes.end(); ++itr)
    {
        area_size = count_digits((*itr).second->get_area());

        cout << left << setw (14) << (*itr).second->get_id() << "|"
             << left << setw(34) << (*itr).second->getAtividadeString() << "|"
             << left << setw(12) << (*itr).second->get_area()  << " |"
             << left << setw(21) << to_string ((*itr).second->get_horario_funcionamento().first) +
             "-" + to_string((*itr).second->get_horario_funcionamento().second) << " |"
             << left <<setw(20) << (*itr).second->getDenuncias()->get_num_graves() << "|"
             << left << setw(18) <<(*itr).second->getDenuncias()->get_num_total() << "|"
             << left << setw(14) <<(*itr).second->getInspecoes()->get_num_aprovadas() << " | "
             << left << setw(14) <<(*itr).second->getInspecoes()->get_num_reprovadas() <<" | "
             <<left << setw(19) <<(*itr).second->getUrgInspec() << "|"
             << left << setw(12) << (*itr).second->get_idNo() << endl;




    }

}

/***************************************************************************************************************/

unordered_map<unsigned int, Brigada *> AutoridadePublica::processarFicheiroBrigadas(string fich) {
    ifstream ficheiro;
    string input;
    unsigned int id, horas_trabalho, hora_inicio;
    AtividadeEconomica atividade;
    unordered_map<unsigned int, Brigada *> result;

    ficheiro.open(fich);

    if (ficheiro.fail())
    {
        cout << "Erro na abertura do ficheiro brigadas.txt " << endl;
    }

    while (!ficheiro.eof())
    {
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
        auto *brigada = new Brigada(id, horas_trabalho, hora_inicio,atividade);
        result[id] = brigada;
        this->id_control_briagada = id;
    }
    return result;
}

/***************************************************************************************************************/

void AutoridadePublica::imprimirBrigadas() const
{
    cout << "ID            |ATIVIDADE ECONOMICA              |NUMERO HORAS TRABALHO|HORA INICIO" << endl;

    for (auto itr = brigadas.begin(); itr != brigadas.end(); ++itr) {
        cout << left << setw (14) << (*itr).second->get_id() << "|"
             << left << setw(33) << (*itr).second->getAtividadeString_() << "|"
             << left << setw(21) <<  (*itr).second->get_horas_trabalho() << "| "
             <<left << setw(12) << (*itr).second->get_hora_inicio() << endl;

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
    int auxIdNo = -1;
    cout << "Qual é o nó correspondente no mapa (tem coincidir com valores do mapa que vai usar ): " << endl;
    cin >> auxIdNo;

    auto *agente = new AgenteEconomico(id_control_agente_economico, stringToAE(atividadeEconomica), area,horario_funcionamento, denuncias, inpecoes, dataUI,auxIdNo);
    cout << endl;
    cout << "Tem a certeza que quer adicionar? (Sim: 1 Não: 2):" << endl;
    int exitOpt = checkOption(1,2);
    if(exitOpt == 2)
        return;

    this->agentes[id_control_agente_economico] = agente;

    cout<<"Agente economico adicionado com sucesso!"<<endl;

}

/***************************************************************************************************************/

void AutoridadePublica::removerAgente(unsigned int id) {
    this->agentes.erase(id);
    cout<<"Agente economico removido com sucesso!"<<endl;

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
}

/***************************************************************************************************************/

void AutoridadePublica::adicionarBrigada() {
    cout << "=====================================================================================" << endl
         << "                                 NOVA BRIGADA                                        " << endl
         << "=====================================================================================" << endl;


    //cin atividade economica
    string atividadeEconomica;
    cout << "Escreva a atividade economica da brigada" << endl;
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
    cout << "Escreva quantas horas por dia trabalha a Brigada" << endl;
    cout << "(em formato decimal (exemplo: 1 ou 8)" << endl;
    unsigned int horas_trabalho = checkOption(1, 24);

    //cin horario de inicio
    cout << "Escreva a hora inicial de trabalho da Brigada: " << endl;
    cout << "(obs. n a possibilidade de colocar minutos, caso seja necessrio arredonde para cima)" << endl;
    unsigned int hora_inico = checkOption(0, 24);//todo problema horario de abertura n n aceita
    cout << endl;
    this->id_control_briagada++;
    auto *brigada = new Brigada(id_control_briagada, horas_trabalho, hora_inico,stringToAE(atividadeEconomica));
    cout << "Tem a certeza que quer adicionar? (Sim: 1 Não: 2):" << endl;
    int exitOpt = checkOption(1,2);
    if(exitOpt == 2)
        return;

    this->brigadas[id_control_briagada] = brigada;
    cout<<"Brigada inserida com sucesso!"<<endl;
}

/***************************************************************************************************************/

void AutoridadePublica::removerBrigada(unsigned int id) {
    this->brigadas.erase(id);
    cout<<"Brigada removida com sucesso!"<<endl;
}

/***************************************************************************************************************/

void AutoridadePublica::destrutor()
{
    /*
     * Escreve nos ficheiros
     */
    fstream ficheiro;
    ficheiro.open("../resources/agentes.txt");

    //criando o vector de keys(ids) ordenadas
    vector<unsigned  int > keys_agentes;

    keys_agentes.reserve (this->agentes.size());
    for (auto& it : this->agentes) {
        keys_agentes.push_back(it.first);
    }
    sort (keys_agentes.begin(), keys_agentes.end());
    bool control = false;
    for(auto  it : keys_agentes)
    {
       if(control)
           ficheiro << endl;
        auto agente = agentes[it];
        agente->imprimirFicheiro(ficheiro);
        control = true;
    }
    ficheiro.close();




    ficheiro.open("../resources/brigadas.txt");

    //criando o vector de keys(ids) ordenadas
    vector<unsigned int> keys_brigadas;

    keys_brigadas.reserve(this->brigadas.size());
    for (auto &it : this->brigadas) {
        keys_brigadas.push_back(it.first);
    }
    sort(keys_brigadas.begin(), keys_brigadas.end());

    control = false;
    for (auto it : keys_brigadas)
    {    if(control)
            ficheiro << endl;
        auto brigada = brigadas[it];
        brigada->imprimirFicheiro(ficheiro);
        control = true;
    }
    ficheiro.close();
    ficheiro.open("../resources/brigadas.txt");

    /*
     * Apaga os objectos
     */

    for (auto it = agentes.begin(); it != agentes.end(); it++)
    {
        delete (*it).second;
    }
    agentes.clear();

    for (auto it = brigadas.begin(); it != brigadas.end(); it++)
    {
        delete (*it).second;
    }
    brigadas.clear();

}




void AutoridadePublica:: addBrigada(Brigada *brig){
    brigadas[brig->get_id()] = brig;

}
void AutoridadePublica:: addAgenteEcon(AgenteEconomico *AgEcon){
    agentes[AgEcon->get_idNo()]= AgEcon;

}






