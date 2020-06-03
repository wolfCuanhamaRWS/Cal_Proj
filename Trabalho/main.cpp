#include <iostream>

#include "../Trabalho/Header/menus.h"
#include "../Trabalho/Header/FileUtils.h"
using namespace std;









int main()
{
    FileUtils fileUtils;// construtor para leitura dos ficheiros
    Autoridade_Publica autoridade;

    fileUtils.read_agente(autoridade);//leitura agentes_ecoomicos
    fileUtils.read_brigada(autoridade);
    fileUtils.read_denuncias(autoridade);

    cout << "Bem vindo!" << endl;



    mainMenu(autoridade);

    return 0;
}
