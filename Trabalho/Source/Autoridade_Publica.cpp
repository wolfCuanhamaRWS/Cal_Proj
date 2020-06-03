#include "../Header/Autoridade_Publica.h"

#include <utility>

Autoridade_Publica::Autoridade_Publica()
{

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
    //long double latitude, longitude;
    vector<string> atividades_economicas;

    file1.open("../Trabalho/TextFiles/agente_economico.txt");
    if(file1.fail())
    {
        cout << "Erro na abertura do ficheiro agente_economico.txt "  << endl;
    }

    while(!file1.eof())
    {
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
        for(int i = 0; i < numDenuncias; i++)
        {
            pos = input.find(',');
            id1 = stoi(input.substr(0, pos));
            input = input.substr(pos + 1, string::npos);
            ids[i] = id1;
        }
        ids_denuncias.insert(ids, ids + numDenuncias);

        //atividades económicas
        getline(file1, input);
        size_t numAtividades = count(input.begin(), input.end(), ',') + 1;
        for(int i = 0; i < numAtividades; i++)
        {
            pos = input.find(',');
            atividade = input.substr(0, pos);
            input = input.substr(pos + 1, string::npos);
            atividades_economicas.push_back(atividade);

        }

        //inspeções
        getline(file1, input);
        vector<string> pairs = string_split(input, '|');
        for(int i = 0; i < pairs.size(); i++)
        {
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
        getline(file1,latitude);
        getline(file1,longitude);


        AgenteEconomico* agente = new AgenteEconomico(ID1, nome, area, intervalo_funcionamento, ids_denuncias, atividades_economicas, inspecoes, stold(latitude),stold(longitude));
        agentes_economicos.push_back(agente);

        ids_denuncias.clear();
        atividades_economicas.clear();
        inspecoes.clear();

    }

    //Processamento das informações do ficheiro brigadas.txt
    ifstream file2;
    int ID2, hora_comeco, numero_horas_diario;
    string especialidade;

    file2.open("../Trabalho/TextFiles/brigadas.txt");
    if(file2.fail())
    {
        cout << "Erro na abertura do ficheiro brigadas.txt "  << endl;
    }

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

    }

    //Processamento das informações do ficheiro denuncias.txt
    ifstream file3;
    int id, id_agente, gravidade;

    file3.open("../Trabalho/TextFiles/denuncias.txt");
    if(file3.fail())
    {
        cout << "Erro na abertura do ficheiro denuncias.txt "  << endl;
    }

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

}

vector<AgenteEconomico *> Autoridade_Publica::get_agentes() const
{
    return this->agentes_economicos;
}

void Autoridade_Publica::set_agentes(vector<AgenteEconomico *> agentes_economicos)
{
    this->agentes_economicos = std::move(agentes_economicos);
}

void Autoridade_Publica::imprimirAgentesEconomicos() const
{
    vector <AgenteEconomico *> copia_agentes = agentes_economicos;
    for (unsigned i = 0; i < copia_agentes.size(); i++)
    {
        cout << "Nome: " << copia_agentes.at(i)->get_nome() << " (ID = " << copia_agentes.at(i)->get_ID() << ")" << endl
             << "Area: " << copia_agentes.at(i)->get_area() << endl
             << "Horario funcionamento: " << copia_agentes.at(i)->get_abertura() << " - " << copia_agentes.at(i)->get_fecho() << endl
             << "Denuncias: " << copia_agentes.at(i)->get_denuncias().size() << endl;
        if(copia_agentes.at(i)->get_denuncias().empty())
            cout << "Nao tem denuncias associadas" << endl;
        else
        {
            //problema aqui
            int i = 0;
            for (set<int>::iterator it = copia_agentes.at(i)->get_denuncias().begin(); it != copia_agentes.at(i)->get_denuncias().end(); ++it)
            {
                cout << (*it);
                if (i != (copia_agentes.at(i)->get_denuncias().size() - 1)) cout << ", ";
                i++;
            }
            cout<<endl;
        }
        cout << "Atividades economicas: ";
        for(int i = 0; i < copia_agentes.at(i)->get_atividades().size(); i++)
        {
            cout << copia_agentes.at(i)->get_atividades().at(i);
            if (i != (copia_agentes.at(i)->get_atividades().size() - 1)) cout << ", ";
        }
        cout<<endl;
        cout << "Inspecoes: ";
        if(copia_agentes.at(i)->get_inspecoes().empty())
            cout << "Nao tem inspecoes associadas" << endl;
        else
        {
            vector <pair<int, string>> inspecoes_copia;
            for (set<pair<int, string>>::iterator it = copia_agentes.at(i)->get_inspecoes().begin(); it != copia_agentes.at(i)->get_inspecoes().end(); ++it)
            {
                inspecoes_copia.push_back(*it);
            }
            for(int i = 0; i < inspecoes_copia.size(); i++)
            {
                cout << inspecoes_copia.at(i).first << "(" << inspecoes_copia.at(i).second << ")";
                if (i != (copia_agentes.at(i)->get_inspecoes().size() - 1)) cout << ", ";
            }
            cout<<endl;
        }
    }
}
/*
void Autoridade_Publica::add_agente_economico(const AgenteEconomico& agente_economico)
{
    agentes_economicos.insert(agente_economico);
}*/

vector<Denuncia *> Autoridade_Publica::get_denuncias() const
{
    return this->denuncias;
}

void Autoridade_Publica::set_denuncias(vector<Denuncia *> &denuncias)
{
    this->denuncias = denuncias;
}
/*
void Autoridade_Publica::add_denuncia(const Denuncia denuncia)
{

}*/

vector<Brigada *> Autoridade_Publica::get_brigadas() const
{
    return this->brigadas;
}

void Autoridade_Publica::set_brigadas(vector<Brigada *> inspetores)
{
    this->brigadas = brigadas;
}


void Autoridade_Publica::add_brigada(int ID, string especialidade, int hora_comeco, int numero_horas_diario)
{
    auto b = new Brigada(ID,especialidade, hora_comeco, numero_horas_diario);
    this->brigadas.insert(brigadas.end()--,b);
}

void Autoridade_Publica::imprimirBrigadas() const
{
    vector <Brigada *> copia_brigadas = brigadas;
    for (unsigned i = 0; i < copia_brigadas.size(); i++)
    {
        cout << "ID: " << copia_brigadas.at(i)->get_ID() << " | "
             << "Hora comeco: " << copia_brigadas.at(i)->get_hora_comeco() << " | "
             << "Numero horas diario: " << copia_brigadas.at(i)->get_num_horas() << " | "
             << "Especialidade: " << copia_brigadas.at(i)->get_especialidade() << endl;

    }

}
