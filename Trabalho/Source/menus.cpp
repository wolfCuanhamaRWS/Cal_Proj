#include <winsock2.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
//#include <term.h>

#include "../Header/menus.h"
#include "../Header/Autoridade_Publica.h"
#include "../Header/utils.h"


//Autoridade_Publica autoridadePublica ;// todo outra solucao inves de criar uma variavel global aqui, talvez colocar o mainMenu na main

void AutoridadePublicaMenu();

void printAutoridadePublicaMenu() {


    cout << "=====================================================================================" << endl
         << "                       InspectIT: Rotas de Inspecao                                  " << endl
         << "=====================================================================================" << endl
         << "           AGENTES ECONOMICOS            |               INSPETORES                  " << endl
         << "=========================================|===========================================" << endl
         << "Adicionar Agente economico         [1]   |   Adicionar inspetor                  [6] " << endl
         << "Remover especialidade              [2]   |   Mudar Id                            [7] " << endl
         << "Mudar horario de funcionamento     [3]   |   Mudar especialiade                  [8] " << endl
         << "Adicionar especialidade            [4]   |   Remover inspetor                    [9] " << endl
         << "Remover agente economico           [5]   |   Visualizar rota diaria             [10] " << endl
         << "Exit                               [0]   |                                           " << endl;

}


void autoridadePublicaMenu() {
    while (true) {
        printAutoridadePublicaMenu();
        int option;
        option = checkOption(0, 10);
        //screenClear();

        if (option == 0)                                            //exit option
            break;
        switch (option) {
            case 6:
                //nspetor *inspetor;
                vector<string *> vector_buffer;
                long int nif;
                cout << "digite o nif do inspector a ser adicionado" << endl;
                cin >> nif;//todo verificar nif
                string especialidade;
                while (especialidade != "0") {
                    cout << "digite uma especialidade do inspector [EXIT 0]" << endl;
                    cin >> especialidade;
                    vector_buffer.insert(vector_buffer.begin(), &especialidade);
                    especialidade = "";
                    //screenClear();
                }
                //nspetor = new Inspetor(nif, vector_buffer);
                break;
        }
    }
}


void printDenuciasMenu() {
    cout << "=====================================================================================" << endl
         << "                                PAGINA DE DENUCIAS                                   " << endl
         << "=====================================================================================" << endl;

}


void denunciasMenu() {

    printDenuciasMenu();

    //screenClear();

    //cin nome no agente economico
    string nome;

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


    //screenClear();

}


void printMainMenu() {

    cout << "=====================================================================================" << endl
         << "                       InspectIT: Rotas de Inspecao                                  " << endl
         << "=====================================================================================" << endl
         << "           DENUNCIAS                     |          AUTORIDADE PUBLICA               " << endl
         << "=========================================|========================================== " << endl
         << "Fazer denuncica                    [1]   |   gerenciar autoridade publica        [2] " << endl
         << "Exit                               [0]   |                                           " << endl;

}

void mainMenu() {
    while (true) {
        printMainMenu();
        int option;
        option = checkOption(0, 2);
        //screenClear(); // n funciona

        if (option == 0)                                            //exit option
            break;
        switch (option) {
            case 1:
                denunciasMenu();

                break;

            case 2:
                autoridadePublicaMenu();
                break;


        }

        //screenClear();
    }
}
