
#include "AutoridadePublica.h"
#include "menus.h"
#include "AlgorithmPerformanceTest.h"




int main() {
    //evitar problemas ao fechar grapView
    signal(SIGINT, SIG_IGN);

    //semente aleatória para ser usada nos testes de performance
    srand(time(NULL));
    AutoridadePublica AtPub ("../resources/agentes.txt","../resources/brigadas.txt");
    mainMenu(AtPub);
    AtPub.destrutor();
    return 0;
}

