#include "../Header/menus.h"

/****************************************************************************************************************
                                            MAIN MENU
****************************************************************************************************************/
void mainMenu()
{

    int option;

    cout << endl << "**** MAIN MENU ****" << endl
                 << "[1] " << endl
                 << "[2] " << endl
                 << "[3] " << endl
                 << "[4] " << endl
                 << "[5] " << endl
                 << "[6] " << endl
                 << "[7] Exit " << endl;

    option = verifyOption(1, 7);

    switch (option)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 7:
            exit(0);

    }


}