#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

#include "src/menus.h"
#include "src/AutoridadePublica.h"
using namespace std;



int main() {

    AutoridadePublica autoridade;

    cout << "Bem vindo!" << endl;

    mainMenu(autoridade);

    return 0;



 }

/*
   testing::InitGoogleTest(&argc, argv);
   std::cout << "CAL Lab Class 05" << std::endl;
   return RUN_ALL_TESTS();
*/