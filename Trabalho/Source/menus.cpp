
#include <iostream>
#include <vector>
#include <string>


#include "../Header/menus.h"


void printAutoridadePublicaMenu() {


    cout << "=====================================================================================" << endl
         << "                       InspectIT: Rotas de Inspecao                                  " << endl
         << "=====================================================================================" << endl
         << "           AGENTES ECONOMICOS            |                 BRIGADAS                  " << endl
         << "=========================================|===========================================" << endl
         << "Visualizar Agentes economicos      [1]   |   Visualizar brigadas                 [7] " << endl
         << "Adicionar Agente economico         [2]   |   Adicionar brigada                   [8] " << endl
         << "Remover especialidade              [3]   | " << endl
         << "Mudar horario de funcionamento     [4]   |   Remover brigada                    [10] " << endl
         << "Adicionar especialidade            [5]   |   Visualizar rota diaria             [11] " << endl
         << "Remover agente economico           [6]   |                                           " << endl
         << "Exit                               [0]   |                                           " << endl;

}

void autoridadePublicaMenu(Autoridade_Publica &autoridade) {
    while (true) {
        printAutoridadePublicaMenu();
        int option;
        option = checkOption(0, 10);
        //screenClear();
        string esp, id;
        bool achou = false;
        if (option == 0)                                            //exit option
            break;
        switch (option) {
            case 1:
                cout << endl << "Lista de todos os agentes economicos:" << endl;
                autoridade.imprimirAgentesEconomicos();
                break;

            case 7:
                cout << endl << "Lista de todos as brigadas:" << endl;
                autoridade.imprimirBrigadas();
                break;
            case 3: {
                achou = false;
                while (!achou) {

                    cout << "Digite o id do agente economico que deseja modificar:" << endl;
                    cin >> id;
                    cout << "Digite a especialidade que deseja remover:" << endl;
                    cin >> esp;
                    vector<string> atividades = autoridade.get_agentes().at(stoi(id) - 1)->get_atividades();
                    vector<string>::iterator pos_atividade = find(atividades.begin(), atividades.end(), esp);
                    if (pos_atividade != atividades.end()) {
                        atividades.erase(pos_atividade);
                        autoridade.get_agentes().at(stoi(id) - 1)->set_atividades(
                                atividades);// id depende do index, n pode
                        cout << "Especialidade removida com sucesso" << endl; // todo remover do ficheiro
                        achou = true;
                    } else { cout << "Este agente economico nao possue essa especialidade, tente novamente" << endl; }

                }
                break;

            }
            case 6: {
                achou = false;
                while (!achou) {
                    cout << "Digite o id do agente economico que deseja remover:"
                         << endl;// ao remover mudar os ids de todos os agentes? n serao mais por index
                    cin >> id;
                    vector<AgenteEconomico *> agts = autoridade.get_agentes();
                    if (stoi(id) < agts.size()) {
                        agts.erase(agts.begin() + stoi(id) - 1);
                        cout << "removido com sucesso" << endl;
                    } else {
                        cout << " nao existe um agente com esse id" << endl;
                    }
                }
                case 5: {
                    cout << "Digite o id do agente economico que deseja modificar:" << endl;
                    cin >> id;
                    cout << "Digite a especialidade que deseja remover:" << endl;
                    cin >> esp;
                    vector<string> atividades = autoridade.get_agentes().at(stoi(id) - 1)->get_atividades();
                    atividades.push_back(esp);
                    cout << "Especialidade adicionada com sucesso" << endl;
                    break;
                }
                case 8: {
                    int ID, hora_comeco, numero_horas_diario;
                    string especialidade;
                    cout << "Digite o ID da brigada a ser adicionada" << endl;
                    cin >> ID;
                    if (ID == 0) { return; }
                    wait();
                    cout << "Caso a brigada tenha somente uma especialidade a di digite, caso controtrio aperte 1"
                         << endl;
                    getline(cin, especialidade);
                    if (especialidade == "0") { return; }
                    wait();
                    cout << "Digite o horario de inicio do comercio:" << endl;
                    cin >> hora_comeco;
                    if (hora_comeco == 0) { return; }
                    wait();
                    cout << "Digite o numero de horas que o comercio permanece aberto:" << endl;
                    cin >> numero_horas_diario;
                    if (numero_horas_diario == 0) { return; }
                    wait();
                    autoridade.add_brigada(ID, especialidade, hora_comeco, numero_horas_diario);
                    cout << "Brigada adicionada com sucesso" << endl;
                    break;
                }

            }
        }

    }
}

void printDenuciasMenu() {
    cout << "=====================================================================================" << endl
         << "                                PAGINA DE DENUCIAS                                   " << endl
         << "=====================================================================================" << endl;

}


void denunciasMenu(Autoridade_Publica autoridade) {

    printDenuciasMenu();
    //cin id_denuncia
    int id_denuncia;
    bool id_valido = false;
    while (!id_valido) {
        cout << "Atribua um interiro pra id da denucia [EXIT 0]: " << endl;
        id_denuncia = checkOption(0, 100000000);
        if (id_denuncia == 0) { return; }
        id_valido = autoridade.id_valido(id_denuncia);

    }

    //cin nome no agente economico
    int id_agente;
    cout << "Digite o id agente economico [EXIT 0]: " << endl;
    id_agente = checkOption(0, 100000000);
    if (id_agente == 0) { return; }

    //cin gravidade d a denuncia
    int gravidade;
    cout << "Digite a Gravidade [EXIT 0]: " << endl;
    cout << "(Leve - 1, Moderada - 2, Grave - 3, Muito Grave - 4)" << endl;
    gravidade = checkOption(0, 4);
    wait();
    if (gravidade == 0) return;   //abort option

    //cin especialidade
    string especialidade;
    cout << "Digite a especialidade [EXIT 0]: " << endl;
    getline(cin, especialidade);
    if (especialidade == "0") { return; }
    autoridade.add_denuncia(id_denuncia, id_agente, gravidade, especialidade);
    autoridade.write_denuncia();


}


void printMainMenu() {

    cout << "=====================================================================================" << endl
         << "                       InspectIT: Rotas de Inspecao                                  " << endl
         << "=====================================================================================" << endl
         << "           DENUNCIAS                     |          AUTORIDADE PUBLICA               " << endl
         << "=========================================|========================================== " << endl
         << "Fazer denuncica                    [1]   |   Gerenciar autoridade publica        [2] " << endl
         << "Exit                               [0]   |                                           " << endl;

}

void mainMenu(Autoridade_Publica &autoridade) {
    while (true) {
        printMainMenu();
        int option;
        option = checkOption(0, 2);
        //screenClear(); // n funciona

        if (option == 0) //exit option
            break;
        switch (option) {
            case 1:
                denunciasMenu(autoridade);

                break;

            case 2:
                autoridadePublicaMenu(autoridade);
                break;


        }

        //screenClear();
    }
}
