#include "../Header/Autoridade_Publica.h"

#include <utility>




/*
while(!file2.eof())
{
    //separador
    getline(file2, input);

    //ID
    getline(file2, input);
    ID2 = stoi(input);

    //especialidade
    getline(file2, especialidade);

    //hora começo
    getline(file2, input);
    hora_comeco = stoi(input);

    //numero_horas_diario
    getline(file2, input);
    numero_horas_diario = stoi(input);

    Brigada* brigada = new Brigada(ID2, especialidade, hora_comeco, numero_horas_diario);
    brigadas.push_back(brigada);

}*/




Autoridade_Publica::Autoridade_Publica() {
read_denuncias();
read_brigada();
read_agente();

}

vector<AgenteEconomico *> Autoridade_Publica::get_agentes() const {
    return this->agentes_economicos;
}

void Autoridade_Publica::set_agentes(vector<AgenteEconomico *> agentes_economicos) {
    this->agentes_economicos = std::move(agentes_economicos);
}

void Autoridade_Publica::imprimirAgentesEconomicos() const {
    vector<AgenteEconomico *> copia_agentes = agentes_economicos;
    cout << "ID |  NOME | AREA | HORARIO FUNCIONAMENTO | ID'S DENUNCIAS | ATIVIDADES ECONOMICAS | INSPECOES" << endl;

    for (unsigned i = 0; i < copia_agentes.size(); i++) {
        copia_agentes[i]->imprimir(cout);
    }
}

void Autoridade_Publica::add_agente_economico(int ID, string nome, float area, pair<int, int> horario_funcionamento,
                                              set<int> ids_denuncias, vector<string> atividades_economicas,
                                              set<pair<int, string>> inspecoes, long double latitude,
                                              long double longuitude) {
    auto agente = new AgenteEconomico(ID, nome, area, horario_funcionamento, ids_denuncias, atividades_economicas,
                                      inspecoes, latitude, longuitude);
    this->agentes_economicos.push_back(agente);
}

vector<Denuncia *> Autoridade_Publica::get_denuncias() const {
    return this->denuncias;
}

void Autoridade_Publica::set_denuncias(vector<Denuncia *> &denuncias) {
    this->denuncias = denuncias;
}

void Autoridade_Publica::add_denuncia(int id, int id_agente, int gravidade, string especialidade) {
    auto denuncia = new Denuncia(id, id_agente, gravidade, especialidade);
    this->denuncias.push_back(denuncia);
}

vector<Brigada *> Autoridade_Publica::get_brigadas() const {
    return this->brigadas;
}

void Autoridade_Publica::set_brigadas(vector<Brigada *> inspetores) {
    this->brigadas = brigadas;
}


void Autoridade_Publica::add_brigada(int ID, string especialidade, int hora_comeco, int numero_horas_diario) {
    auto b = new Brigada(ID, especialidade, hora_comeco, numero_horas_diario);
    this->brigadas.push_back(b);
}

void Autoridade_Publica::imprimirBrigadas() const {
    vector<Brigada *> copia_brigadas = brigadas;
    for (unsigned i = 0; i < copia_brigadas.size(); i++) {
        cout << "ID: " << copia_brigadas.at(i)->get_ID() << " | "
             << "Hora comeco: " << copia_brigadas.at(i)->get_hora_comeco() << " | "
             << "Numero horas diario: " << copia_brigadas.at(i)->get_num_horas() << " | "
             << "Especialidade: " << copia_brigadas.at(i)->get_especialidade() << endl;

    }

}

bool Autoridade_Publica::id_valido(int id) {
    for (Denuncia *denuncia: denuncias) {
        if (denuncia->get_id() == id) {
            cout << "Id já usado para outra denucia" << endl;
            return false;
        }
    }
    return true;
}

void Autoridade_Publica::read_agente() {
//Processamento das informações do ficheiro agente_economico.txt
    ifstream file1;
    string input, tuplo;
    unsigned int pos, p;
    string nome, atividade;
    pair<int, int> intervalo_funcionamento;
    pair<int, string> inspecao;
    set<pair<int, string>> inspecoes;
    int ids[] = {};
    set<int> ids_denuncias;
    int id1, ID1;
    float area;
    bool resultado;
    vector<string> atividades_economicas;

    file1.open("../Trabalho/TextFiles/agente_economico.txt");
    if (file1.fail()) {
        cout << "Erro na abertura do ficheiro agente_economico.txt " << endl;
    }

    while (!file1.eof()) {
        //separador
        getline(file1, input);

        //ID
        getline(file1, input);
        ID1 = stoi(input);

        //nome
        getline(file1, nome);

        //area
        getline(file1, input);
        area = stof(input);

        //intervalo funcionamento
        getline(file1, input);
        pos = input.find('-');
        intervalo_funcionamento.first = stoi(input.substr(0, pos));
        input = input.substr(pos + 1, string::npos);
        intervalo_funcionamento.second = stoi(input);
        intervalo_funcionamento = make_pair(intervalo_funcionamento.first, intervalo_funcionamento.second);

        //id's das denuncias
        getline(file1, input);
        size_t numDenuncias = count(input.begin(), input.end(), ',') + 1;
        for (int i = 0; i < numDenuncias; i++) {
            pos = input.find(',');
            id1 = stoi(input.substr(0, pos));
            input = input.substr(pos + 1, string::npos);
            ids[i] = id1;
        }
        ids_denuncias.insert(ids, ids + numDenuncias);

        //atividades económicas
        getline(file1, input);
        size_t numAtividades = count(input.begin(), input.end(), ',') + 1;
        for (int i = 0; i < numAtividades; i++) {
            pos = input.find(',');
            atividade = input.substr(0, pos);
            input = input.substr(pos + 1, string::npos);
            atividades_economicas.push_back(atividade);

        }

        //inspeções
        getline(file1, input);
        vector<string> pairs = string_split(input, '|');
        for (int i = 0; i < pairs.size(); i++) {
            tuplo = pairs.at(i);
            pos = tuplo.find(',');
            inspecao.first = stoi(tuplo.substr(0, pos));
            inspecao.second = tuplo.substr(pos + 1, string::npos);
            inspecao = make_pair(inspecao.first, inspecao.second);
            //problema aqui
            inspecoes.insert(inspecao);
        }
        string latitude, longitude;
        //morada
        getline(file1, latitude);
        getline(file1, longitude);

        add_agente_economico(ID1, nome, area, intervalo_funcionamento, ids_denuncias,
                                   atividades_economicas, inspecoes, stold(latitude),
                                   stold(longitude));

        ids_denuncias.clear();
        atividades_economicas.clear();
        inspecoes.clear();
    }
}

void Autoridade_Publica::read_denuncias() {


    //Processamento das informações do ficheiro denuncias.txt
    ifstream file;
    string especialidade, buffer;
    string id, id_agente, gravidade;

    file.open("../Trabalho/TextFiles/denuncias.txt");
    if (file.fail()) {
        cout << "Erro na abertura do ficheiro denuncias.txt " << endl;
    }
    while (!file.eof()) {
        getline(file, buffer);
        getline(file, id);
        getline(file, id_agente);
        getline(file, gravidade);
        getline(file, especialidade);
    }
    //adiciona o agente para o vector de denucias na autoridade publica
    add_denuncia(stoi(id), stoi(id_agente), stoi(gravidade), especialidade);
}

void Autoridade_Publica::read_brigada() {
    //Processamento das informações do ficheiro brigadas.txt
    ifstream file2;
    int ID2, hora_comeco, numero_horas_diario;
    string especialidade, input;

    file2.open("../Trabalho/TextFiles/brigadas.txt");
    if (file2.fail()) {
        cout << "Erro na abertura do ficheiro brigadas.txt " << endl;
    }

    while (!file2.eof()) {
        //separador
        getline(file2, input);

        //ID
        getline(file2, input);
        ID2 = stoi(input);

        //especialidade
        getline(file2, especialidade);

        //hora começo
        getline(file2, input);
        hora_comeco = stoi(input);

        //numero_horas_diario
        getline(file2, input);
        numero_horas_diario = stoi(input);

        //Brigada *brigada = new Brigada(ID2, especialidade, hora_comeco, numero_horas_diario);
      add_brigada(ID2, especialidade, hora_comeco, numero_horas_diario);

    }
}


void Autoridade_Publica:: write_denuncia() {
    ofstream file;
    file.open("../Trabalho/TextFiles/denuncias.txt");
    for(auto it : denuncias){
        file << to_string(it->get_id())<< "\n"<< to_string(it->get_id_agente())<<"\n"
             << to_string(it->get_gravidade())<<"\n"<< it->get_especialidade()<<"\n";
    }
    file.close();

}

