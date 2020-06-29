
#include "AutoridadePublica.h"
#include "menus.h"




int main() {

    AutoridadePublica AtPub ("../resources/agentes.txt","../resources/brigadas.txt");
    mainMenu(AtPub);
    AtPub.destrutor();
    return 0;
}

