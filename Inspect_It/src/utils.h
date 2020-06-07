#ifndef CAL_UTILS_H
#define CAL_UTILS_H

#include <iostream>
#include <vector>

#include "Erro.h"

using namespace std;

int checkOption(int min, int max);
vector<string> string_split(string str, char sep);
string elem_two_spaces(string str);
int count_digits(float num);
void wait();

#endif //CAL_UTILS_H