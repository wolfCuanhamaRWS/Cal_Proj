#include <iostream>
#include <vector>
#include <string>

#include "menus.h"

void mainMenu(AutoridadePublica &autoridade)
{
    cout << "=====================================================================================" << endl
         << "                       InspectIT: Rotas de Inspecao                                  " << endl
         << "=====================================================================================" << endl
         << "           AGENTES ECONOMICOS            |                 BRIGADAS                  " << endl
         << "=========================================|===========================================" << endl
         << "Visualizar informacao dos agentes  [1]   |   Visualizar informacao das brigadas  [5] " << endl
         << "Adicionar agente economico         [2]   |   Adicionar brigada                   [6] " << endl
         << "Inserir denuncia                   [3]   |   Remover brigada                     [7] " << endl
         << "Remover agente economico           [4]   |   Visualizar rota diaria              [8] " << endl
         << "Exit                               [0]   |                                            " << endl;

    int option;
    option = checkOption(0, 8);

    switch (option)
    {
        case 0: //Sair
            break;

        case 1: //Visualizar agentes económicos
            cout << endl << "Lista de todos os agentes economicos:" << endl;
            autoridade.imprimirAgentesEconomicos();
            break;

        case 2: //Adicionar agente económico
            autoridade.adicionarAgenteEconomico();
            break;

        case 3: //Inserir denuncia
            autoridade.inserirDenuncia();
            break;

        case 4: //Remover agente economico
            autoridade.removerAgente();
            break;

        case 5: //Visualizar brigadas
            cout << endl << "Lista de todos as brigadas:" << endl;
            autoridade.imprimirBrigadas();
            break;

        case 6: //Adicionar brigada
            autoridade.adicionarBrigada();
            break;

        case 7: //Remover brigada
            autoridade.removerBrigada();
            break;

        case 8: //Visualizar rota diária
            break;

    }
}

