#include "gtest/gtest.h"
#include "gmock/gmock.h"



#include "AutoridadePublica.h"
#include "menus.h"





int main(int argc, char* argv[]) {

    testing::InitGoogleTest(&argc, argv);
    std::cout << "Inspect Test" << std::endl;
    return RUN_ALL_TESTS();



}

/*

int main(){


    AutoridadePublica autoridade;

    cout << "Bem vindo!" << endl;

    mainMenu(autoridade);

    return 0;


}
 */