#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>

#include "src/menus.h"

using namespace std;

int main(int argc, char* argv[])
{
    AutoridadePublica autoridade;

    cout << "Bem vindo!" << endl;

    mainMenu(autoridade);

    testing::InitGoogleTest(&argc, argv);
    std::cout << "CAL Lab Class 05" << std::endl;
    return RUN_ALL_TESTS();
}