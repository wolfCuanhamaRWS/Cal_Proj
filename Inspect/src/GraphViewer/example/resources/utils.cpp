#include"utils.h"

double checkOption(double min, double  max) {
    double input;

    while (true) {
        try {
            cout << endl << "Escolha uma opcao (" << min << "-" << max << "): ";
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw WrongInput_option("Input invalido. Escreva um inteiro");

            }
                //recusado se nao esta no intervalo
            else if (input > max || input < min) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw WrongInput_option("Input invalido. Escreva um valor valido");
            } else
                return input;
        }
        catch (WrongInput_option &error) {
            cout << error.getInfo() << endl;
            continue;
        }
    }

}


int checkOption(int min, int max) {
    double input;

    while (true) {
        try {
            cout << endl << "Escolha uma opcao (" << min << "-" << max << "): ";
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw WrongInput_option("Input invalido. Escreva um inteiro");

            }
                //recusado se nao esta no intervalo
            else if (input > max || input < min) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw WrongInput_option("Input invalido. Escreva um valor valido");
            } else
                return input;
        }
        catch (WrongInput_option &error) {
            cout << error.getInfo() << endl;
            continue;
        }
    }

}


string elem_two_spaces(string str) {
    while (str.find("  ") != string::npos) {
        str.erase(str.find("  "), 1);
    }
    return str;
}

/***************************************************************************************************************/

vector<string> string_split(string str, char sep) {
    vector<string> result;
    string component = "";

    for (int i = 0; i < str.size(); i++) {
        char ch = str.at(i);
        if (ch != sep) {
            component.append(1, ch);
        } else {
            component = elem_two_spaces(component);
            if (component.at(component.size() - 1) == ' ') component.pop_back();
            if (component.at(0) == ' ') component.erase(0, 1);
            result.push_back(component);
            component = "";
        }
        if (i == (str.size() - 1)) {
            component = elem_two_spaces(component);
            if (component.at(component.size() - 1) == ' ') component.pop_back();
            if (component.at(0) == ' ') component.erase(0, 1);
            result.push_back(component);
        }
    }
    return result;
}

int count_digits(float num)
{
    string n = to_string(num);
    int count = 0;
    for(int i = 0; i <= n.size(); i++)
    {
        if(n.at(i) == '.')
            break;
        count = count + 1;
    }

    for(int i = n.find('.'); i < n.size(); i++)
    {
        if(n.at(i) == '0')
            break;
        count = count + 1;
    }
    return count;
}

void screenClear() {
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif


}

bool wait() {
    cout << endl << "[PRESS ENTER TO CONTINUE]" << endl;
    cin.ignore();
    while (cin.get() != '\n') {};

    return true;
}