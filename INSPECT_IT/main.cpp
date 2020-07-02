
#include "Model/AutoridadePublica.h"
#include "View/menus.h"
#include "Algorithms/AlgorithmPerformanceTest.h"




int main() {
    //evitar problemas ao fechar grapView
    signal(SIGINT, SIG_IGN);

    //semente aleatória para ser usada nos testes de performance
    srand(time(NULL));
    AutoridadePublica AtPub ("../src/agentes.txt","../src/brigadas.txt");
    mainMenu(AtPub);
    AtPub.destrutor();
    return 0;
}

