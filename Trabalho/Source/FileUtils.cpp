//
// Created by amanda on 03/06/2020.
//

#include "FileUtils.h"


FileUtils::FileUtils() {

}


void FileUtils::read_agente(Autoridade_Publica autoridadePublica) {
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

//
//        AgenteEconomico *agente = new AgenteEconomico(ID1, nome, area, intervalo_funcionamento, ids_denuncias,
//                                                      atividades_economicas, inspecoes, stold(latitude),
//                                                      stold(longitude));
        autoridadePublica.add_agente_economico(ID1, nome, area, intervalo_funcionamento, ids_denuncias,
                                               atividades_economicas, inspecoes, stold(latitude),
                                               stold(longitude));
        //        vector<AgenteEconomico*> agente_buffer = autoridadePublica.get_agentes();
//        agente_buffer.push_back(agente);
//        autoridadePublica.set_agentes(agente_buffer);

        ids_denuncias.clear();
        atividades_economicas.clear();
        inspecoes.clear();

    }
}

void FileUtils::read_brigada(Autoridade_Publica autoridadePublica) {
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
        autoridadePublica.add_brigada(ID2, especialidade, hora_comeco, numero_horas_diario);

    }
}

void FileUtils::read_denuncias(Autoridade_Publica autoridadePublica) {


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
    autoridadePublica.add_denuncia(stoi(id), stoi(id_agente), stoi(gravidade), especialidade);
}
