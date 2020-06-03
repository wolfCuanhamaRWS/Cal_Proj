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


Autoridade_Publica::Autoridade_Publica(){}


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

void Autoridade_Publica::add_agente_economico(int ID, string nome, float area, pair<int, int> horario_funcionamento, set<int> ids_denuncias, vector<string> atividades_economicas, set<pair<int, string>>inspecoes,long double latitude,long double longuitude)
{
    auto agente = new AgenteEconomico( ID,  nome,  area, horario_funcionamento,  ids_denuncias,  atividades_economicas,inspecoes, latitude, longuitude);
    this->agentes_economicos.push_back(agente);
}

vector<Denuncia *> Autoridade_Publica::get_denuncias() const
{
    return this->denuncias;
}

void Autoridade_Publica::set_denuncias(vector<Denuncia *> &denuncias)
{
    this->denuncias = denuncias;
}

void Autoridade_Publica::add_denuncia(int id, int id_agente, int gravidade, string especialidade)
{
auto denuncia = new Denuncia(id, id_agente, gravidade, especialidade);
this->denuncias.push_back(denuncia);
}

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
    this->brigadas.push_back(b);
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
