#include "Empresa.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include "utils.h"
#include "Data.h"
#include "Excecoes.h"
#include <ctime>
using namespace std;

string data_atual, hora_atual;

int servico_oficina_id_atual=0;
Condutor notFound;

/****************************************************************************************************************
                             IMPLEMENTAÇÃO DOS MÉTODOS DA CLASSE Empresa
****************************************************************************************************************/
void Empresa::inativarCliente(Cliente* cliente)
{
    clientesInativos.insert(cliente);
}

/***************************************************************************************************************/

void Empresa::reativarCliente(Cliente* cliente)
{
    //verifica se cliente está na tabela de dispersão
    auto itr = clientesInativos.find(cliente);

    if (itr != clientesInativos.end())
        clientesInativos.erase(cliente);

}

/***************************************************************************************************************/

Empresa::Empresa() : condutores(&notFound)
{
    // current date/time based on current system
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // print various components of tm structure.

    data_atual = to_string(1900 + ltm->tm_year) + "/";
    if (to_string(1 + ltm->tm_mon).size() == 1)
        data_atual += "0";
    data_atual += to_string(1 + ltm->tm_mon) + "/";
    if(to_string(ltm->tm_mday).size() == 1)
        data_atual += "0";
    data_atual += to_string(ltm->tm_mday);

    hora_atual = to_string(ltm->tm_hour) +  ":";
    if(to_string(ltm->tm_min).size() == 1)
        hora_atual += "0";
    hora_atual += to_string(ltm->tm_min) + ":";
    if(to_string(ltm->tm_sec).size() == 1)
        hora_atual += "0";
    hora_atual += to_string(ltm->tm_sec);

    cout << endl << "Data: " << data_atual << endl;
    cout << "Hora: "<< hora_atual << endl;


    string sinput;
    int iinput;

    //Ínicio do tratamento do ficheiro da empresa
    ifstream empresa_file;

    empresa_file.open("empresa.txt");

    getline(empresa_file,sinput);

    nome = string_split(sinput,':').at(1);

    getline(empresa_file,sinput);

    telefone = stoi(string_split(sinput,':').at(1));

    getline(empresa_file,sinput);

    morada=string_split(sinput,':').at(1);

    getline(empresa_file,sinput);

    site=string_split(sinput,':').at(1);

    empresa_file.close();
    //Fim do tratamento do ficheiro da empresa

    //Ínicio do tratamento do ficheiro dos camiões
    ifstream camioes_file;
    camioes_file.open("camioes.txt");

    while(!camioes_file.eof())
    {
        string cam_matricula, cam_mod, cam_marc;
        int cam_an;
        float cam_cap;
        string tipo_mercadoria;

        getline(camioes_file, cam_matricula);
        getline(camioes_file, cam_marc);
        getline(camioes_file, cam_mod);
        camioes_file >> cam_an;
        camioes_file.ignore(1000, '\n');
        camioes_file >> cam_cap;
        camioes_file.ignore(1000, '\n');

        getline(camioes_file, sinput);
        tipo_mercadoria = sinput;

            if(sinput=="outros")
            {
                Camiao *cam_ptr = new Camiao(cam_cap, cam_matricula, cam_marc, cam_mod, cam_an, tipo_mercadoria);
                camioes.push_back(cam_ptr);
                getline(camioes_file, sinput);

            }
            else if(sinput== "congelados")
            {
                float cam_temp;
                camioes_file >> cam_temp;
                camioes_file.ignore(1000, '\n');
                Camiao_congelados *cam_ptr = new Camiao_congelados(cam_cap, cam_matricula, cam_marc, cam_mod, cam_an, tipo_mercadoria, cam_temp);
                camioes.push_back(cam_ptr);

            }
            else if(sinput== "perigosas")
            {
                string cam_niv;
                getline(camioes_file, cam_niv);
                Camiao_perigo *cam_ptr = new Camiao_perigo(cam_cap, cam_matricula, cam_marc, cam_mod, cam_an, tipo_mercadoria, cam_niv);
                camioes.push_back(cam_ptr);

            }
            else if(sinput== "animais") {
                string cam_esp;
                getline(camioes_file, cam_esp);
                Camiao_animal *cam_ptr = new Camiao_animal(cam_cap, cam_matricula, cam_marc, cam_mod, cam_an, tipo_mercadoria, cam_esp);
                camioes.push_back(cam_ptr);

            }
            else {
                cout << "ERRO!";

            }

        getline(camioes_file,sinput);
        if (camioes_file.fail()) break;
        if (sinput=="") break;
    }
    camioes_file.close();
    //Fim do tratamento do ficheiro dos camiões

    //Ínicio do tratamento do ficheiro dos clientes

    ifstream clientes_file;
    clientes_file.open("clientes.txt");

    while(!clientes_file.eof())
    {
        string cli_nom,cli_mor;
        int cli_nif,cli_tel;
        vector<int> cli_serv;
        cli_serv.clear();

        getline(clientes_file,cli_nom);
        clientes_file>>cli_nif;
        clientes_file.ignore(1000,'\n');

        clientes_file>>cli_tel;
        clientes_file.ignore(1000,'\n');

        getline(clientes_file,cli_mor);

        getline(clientes_file,sinput);


        if (sinput!="")
        {
            vector<string> string_cli_serv = string_split(sinput, ',');
            for (auto i:string_cli_serv) {
                cli_serv.push_back(stoi(i));
            }
        }

        Cliente* cli_ptr = new Cliente(cli_nom,cli_nif,cli_tel,cli_mor,cli_serv);
        clientes.push_back(cli_ptr);

        getline(clientes_file,sinput);
        if (clientes_file.fail()) break;
        if (sinput=="") break;
    }

    clientes_file.close();

    //Fim do tratamento do ficheiro dos clientes

    //Ínicio do tratamento do ficheiro dos funcionários
    ifstream funcs_file;
    funcs_file.open("funcionarios.txt");
    vector<Condutor*> cond;
    while (!funcs_file.eof())
    {
        string func_nome,func_mor,func_carg;
        int func_nif,func_tel;
        float func_sal;
        vector<int> func_serv;
        func_serv.clear();

        getline(funcs_file,func_nome);
        funcs_file>>func_nif;
        funcs_file.ignore(1000,'\n');

        funcs_file>>func_tel;
        funcs_file.ignore(1000,'\n');

        getline(funcs_file,func_mor);

        getline(funcs_file,func_carg);


            if(func_carg=="condutor")
            {
                getline(funcs_file,sinput);
                if (sinput!="") {
                    vector<string> string_func_serv = string_split(sinput, ',');

                    for (auto i:string_func_serv) {
                        func_serv.push_back(stoi(i));
                    }
                }
            }
            else
            {
                getline(funcs_file,sinput);

            }


        funcs_file>>func_sal;
        funcs_file.ignore(1000,'\n');


            if(func_carg=="condutor")
            {
                Condutor* func_ptr = new Condutor(func_nome,func_nif,func_tel,func_mor,func_sal,func_carg,func_serv, 0);
                cond.push_back(func_ptr);

            }
            else
            {
                Funcionario* func_ptr = new Funcionario(func_nome,func_nif,func_tel,func_mor,func_sal,func_carg);
                funcionarios.push_back(func_ptr);

            }

        getline(funcs_file,sinput);
        if (funcs_file.fail()) break;
        if (sinput=="") break;
    }
    funcs_file.close();
    //Fim do tratamento do ficheiro dos funcionários
    //ínicio do tratamento do ficheiro dos serviços
    ifstream servs_file;
    servs_file.open("servicos.txt");

    while(!servs_file.eof())
    {
        int serv_id,serv_num;
        string serv_origem,serv_dest;
        string serv_hora,serv_temp,serv_merc,serv_tip;
        Data* serv_data = nullptr;
        Cliente* serv_cli = nullptr;
        vector<Camiao *> serv_cams;

        servs_file>>serv_id;
        servs_file.ignore(1000,'\n');

        getline(servs_file,serv_origem);
        getline(servs_file,serv_dest);

        getline(servs_file,sinput);
        serv_data = new Data(sinput);

        getline(servs_file,serv_hora);
        getline(servs_file,serv_temp);
        getline(servs_file,serv_merc);

        getline(servs_file,sinput);

        if (sinput!="")
        {
            vector<string> serv_matriculas = string_split(sinput,',');
            for (vector<string>::iterator it = serv_matriculas.begin(); it != serv_matriculas.end(); it++) {
                for (vector<Camiao *>::iterator it2 = camioes.begin(); it2 != camioes.end(); it2++) {
                    if ((*it2)->getMatricula() == (*it)) serv_cams.push_back(&(*(*it2)));
                }
            }
        }

        getline(servs_file,sinput);

        for (vector<Cliente *>::iterator it = clientes.begin();it!=clientes.end();it++)
        {
            if ((*it)->getNif()== stoi(sinput))
            {
                serv_cli=&(*(*it));
            }
        }


        getline(servs_file,serv_tip);

        Servico* serv_ptr=new Servico(serv_id,serv_origem,serv_dest,serv_temp,serv_data,serv_hora,serv_merc,serv_tip,serv_cli,serv_cams);
        servicos.push_back(serv_ptr);

        getline(servs_file,sinput);


        if (servs_file.fail()) break;
        if (sinput=="") break;
    }

    servs_file.close();

    for(auto i: cond)
    {
        double hor = 0;
        for(auto j: i->getServicos())
        {
            //so calcula para o caso de a data atual proceder/for igual à data do serviço e se a hora atual proceder a hora final do serviço
            string hora_final = calculaHoraFinal(servicos[j-1]->getHora_inicio(), servicos[j-1]->getTempo()) + ":00";
            //cout << servicos[j-1]->getData() << endl << hora_final << endl << endl;
            if(servicos[j-1]->getData() <= data_atual || (servicos[j-1]->getData() == data_atual &&  hora_final <= hora_atual))
            {
                vector<string> hor_sep = string_split(servicos[j-1]->getTempo(), ':');
                double horas_servico = stod(hor_sep[0]) + stod(hor_sep[1])/60.0;
                if(servicos[j-1]->getTipoServico() == "pontual")
                {
                    hor += horas_servico;
                    continue;
                }
                Data actual_date(1900 + ltm->tm_year,1 + ltm->tm_mon,ltm->tm_mday), serv_date = *servicos[j-1]->getDataObjecto();
                if (servicos[j-1]->getTipoServico() == "diario")
                {
                    long unsigned int num_dias_entre_datas = actual_date.numDiasDesdeCristo() - serv_date.numDiasDesdeCristo();
                    hor += num_dias_entre_datas * horas_servico;
                    if(hora_final < hora_atual)
                        hor += horas_servico;
                }
                else if(servicos[j-1]->getTipoServico() == "mensal")
                {
                    int n_meses = 1; //se entrou no primeiro if, este serviço é sempre efetuado, nem que seja uma sp vez (no dia em que foi criado)
                    if(serv_date.getAno()<actual_date.getAno())
                    {
                        n_meses += 12-serv_date.getMes(); // num de meses para completar esse ano
                        n_meses += (actual_date.getAno() - serv_date.getAno() + 1)*12; // adiciona-se 12 por cada ano completo entre o ano de serviço e o ano atual
                        n_meses += actual_date.getMes(); //agora adiciona-se o numero de meses do ano atual
                    }
                    else
                    {
                        n_meses += actual_date.getMes() - serv_date.getMes(); //n de meses entre os meses
                    }
                    if(actual_date.getDia() < serv_date.getDia() || (actual_date.getDia() == serv_date.getDia() && hora_atual < hora_final))  // se ainda nao passou o dia do serviço neste mes, retira-se 1
                        n_meses--;
                    hor += horas_servico*n_meses;
                }
            }
        }
        i->setHoras(hor);
        condutores.insert(i);
    }
    //Fim do tratamento do ficheiro dos serviços

    // Inicializa a tabela de dispersão com os clientes inativos,
    // ou seja, os clientes que deixaram de requisitar serviços há mais de um ano
    int anoAtual = 1900 + ltm->tm_year;
    for(auto itr = clientes.begin(); itr != clientes.end(); itr++)
    {
        bool inativar = false;
        vector <int> servicosRequisitados = (*itr)->getServicosRequisitados();
        int s_ = 0;
        for(auto s = servicos.begin(); s != servicos.end(); s++)
        {
            if((*s)->getId() >= servicos.size() || servicosRequisitados.size() == 0)
            {
                break;
            }

            else if((*s)->getId() == servicosRequisitados.at(s_))
            {
                int anoServico = (*s)->getDataObjecto()->getAno();
                if((anoAtual - anoServico) >= 1)
                {
                    inativar = true;
                }
                else
                {
                    inativar = false;
                }
                servicosRequisitados.erase(servicosRequisitados.begin());
            }
        }
        if(inativar == true)
            inativarCliente(*itr);

    }

    //Inicio do tratamento do ficheiro dos servicos das oficinas

    ifstream oficina_servicos_file;

    oficina_servicos_file.open("servicos_oficina.txt");

    vector<Servico_Oficina*> temp;

    while(!oficina_servicos_file.eof())
    {
        int id,duracao,esp_num;
        bool esp;
        string matricula_str;

        oficina_servicos_file>>id;
        oficina_servicos_file.ignore(1000,'\n');

        oficina_servicos_file>>esp_num;
        oficina_servicos_file.ignore(1000,'\n');
        if (esp_num==1) esp=true;
        else esp=false;
        getline(oficina_servicos_file,matricula_str);

        Camiao* cam_ptr;

        for (auto i:camioes)
        {
            if (i->getMatricula()==matricula_str)
            {
                cam_ptr=i;
                break;
            }
        }

        oficina_servicos_file>>duracao;
        oficina_servicos_file.ignore(1000,'\n');

        auto oficina_serv = new Servico_Oficina(id,esp,cam_ptr,duracao);

        temp.push_back(oficina_serv);


        getline(oficina_servicos_file,sinput);
        if (oficina_servicos_file.fail()) break;
        if (sinput=="") break;
    }

    oficina_servicos_file.close();

    int maior=0;
    for (auto i:temp) {if (i->getId()>maior) maior=i->getId();}

    servico_oficina_id_atual=maior;

    //Fim do tratamento do ficheiro dos servicos das oficinas

    //Inicio do tratamento do ficheiro das oficinas

    ifstream oficinas_file;

    oficinas_file.open("oficinas.txt");

    while(!oficinas_file.eof())
    {
        int id,indisp=0;
        string denom;
        vector<string> marcas;
        vector<Servico_Oficina*> servs;

        oficinas_file>>id;
        oficinas_file.ignore(1000,'\n');

        getline(oficinas_file,denom);

        getline(oficinas_file,sinput);

        if (sinput=="") marcas.clear();
        else if (sinput.find(',')==string::npos) marcas.push_back(sinput);
        else
        {
            for (auto i:string_split(sinput,','))
            {
                marcas.push_back(i);
            }
        }

        getline(oficinas_file,sinput);
        if (sinput=="") servs.clear();
        else if (sinput.find(',')==string::npos)
        {
            for (auto i:temp)
            {
                if (i->getId()==stoi(sinput))
                    {servs.push_back(i);
                    break;}
            }
        }
        else
        {
            for (auto i:string_split(sinput,','))
            {
                for (auto i2:temp)
                {
                    if (i2->getId()==stoi(i))
                    {
                        servs.push_back(i2);
                    }
                }
            }
        }

        for (auto i:servs)
        {
            indisp+=i->getDuracao();
        }

        Oficina nova_oficina=Oficina(id,denom,marcas,indisp,servs);

        oficinas.push(nova_oficina);

        getline(oficinas_file,sinput);
        if (oficinas_file.fail()) break;
        if (sinput=="") break;
    }

    oficinas_file.close();
    //Fim do tratamento do ficheiro das oficinas

}

/***************************************************************************************************************/

void Empresa::destrutor()
{
    /*
     * Escreve nos ficheiros
     */
    ofstream camioes_file;
    camioes_file.open("camioes.txt",ofstream::out | ofstream::trunc);

    for (vector<Camiao *>::iterator it=camioes.begin();it!=camioes.end();it++)
    {
        (**it).imprimirFicheiro(camioes_file);
        if ((*it)!=camioes.back()) camioes_file<<"::::::::::\n";
    }

    camioes_file.close();

    ofstream clientes_file;
    clientes_file.open("clientes.txt",ofstream::out | ofstream::trunc);

    for (vector<Cliente *>::iterator it=clientes.begin();it!=clientes.end();it++)
    {
        (**it).imprimirFicheiro(clientes_file);
        if ((*it)!=clientes.back()) clientes_file<<"::::::::::\n";
    }

    clientes_file.close();

    ofstream funcionarios_file;
    funcionarios_file.open("funcionarios.txt",ofstream::out | ofstream::trunc);

    for (vector<Funcionario *>::iterator it=funcionarios.begin();it!=funcionarios.end();it++)
    {
        (**it).imprimirFicheiro(funcionarios_file);
        if ((*it)!=funcionarios.back()) funcionarios_file<<"::::::::::\n";
    }
    funcionarios_file<<"::::::::::\n";
    for(auto it = condutores.begin(); it != condutores.end();it++ )
    {
        (*it)->imprimirFicheiro(funcionarios_file);
        auto it2 = it;
        it2++;
        if(it2 != condutores.end()) funcionarios_file<<"::::::::::\n";
    }

    funcionarios_file.close();

    ofstream servicos_file;
    servicos_file.open("servicos.txt",ofstream::out | ofstream::trunc);

    for (vector<Servico *>::iterator it=servicos.begin();it!=servicos.end();it++)
    {
        (**it).imprimirFicheiro(servicos_file);
        if ((*it)!=servicos.back()) servicos_file<<"::::::::::\n";
    }

    servicos_file.close();


    ofstream oficinas_file;

    oficinas_file.open("oficinas.txt",ofstream::out | ofstream::trunc);


    vector<Servico_Oficina*> servicos_oficina;

    while(!oficinas.empty())
    {
        oficinas.top().imprimirFicheiro(oficinas_file);

        if (oficinas.top().getServicos().size()!=0)
        {for (auto i:oficinas.top().getServicos())
        {
            servicos_oficina.push_back(i);
        }}
        if (oficinas.size()!=1) oficinas_file<<"::::::::::\n";
        oficinas.pop();
    }

    oficinas_file.close();

    ofstream servicos_oficina_file;
    servicos_oficina_file.open("servicos_oficina.txt",ofstream::out | ofstream::trunc);

    for (auto i:servicos_oficina)
    {
        i->imprimirFicheiro(servicos_oficina_file);
        if (i!=servicos_oficina.back()) servicos_oficina_file<<"::::::::::\n";
    }


    servicos_oficina_file.close();

    /*
     * Apaga os objectos
     */

    for (vector<Camiao *>::iterator it=camioes.begin();it!=camioes.end();it++)
    {
        delete *it;
    }
    camioes.clear();

    for (vector<Cliente *>::iterator it=clientes.begin();it!=clientes.end();it++)
    {
        delete *it;
    }
    clientes.clear();


    for (vector<Funcionario *>::iterator it=funcionarios.begin();it!=funcionarios.end();it++)
    {
        delete *it;
    }
    funcionarios.clear();


    for (vector<Servico *>::iterator it=servicos.begin();it!=servicos.end();it++)
    {
        delete *it;
    }
    servicos.clear();

    for (vector<Servico_Oficina*>::iterator it=servicos_oficina.begin();it!=servicos_oficina.end();it++)
    {
        delete *it;
    }
    servicos_oficina.clear();
}

/***************************************************************************************************************/

string Empresa::getNome() const
{
    return nome;
}

/***************************************************************************************************************/

unsigned int Empresa::getTelefone() const
{
    return telefone;
}

/***************************************************************************************************************/

string Empresa::getMorada() const
{
    return morada;
}

/***************************************************************************************************************/

string Empresa::getSite() const
{
    return site;
}

/***************************************************************************************************************/

vector <Servico *> Empresa::getServicos() const
{
    return servicos;
}

/***************************************************************************************************************/

void Empresa::setNome(string nome)
{
    this->nome = nome;
}

/***************************************************************************************************************/

void Empresa::setTelefone(unsigned int telefone)
{
    this->telefone = telefone;
}

/***************************************************************************************************************/

void Empresa::setMorada(string morada)
{
    this->morada = morada;
}

/***************************************************************************************************************/

void Empresa::setSite(string site)
{
    this->site = site;
}

/***************************************************************************************************************/

bool sort_clientes_nome(Cliente* cli1, Cliente* cli2)
{
    return cli1->getNome() < cli2->getNome();
}

void Empresa::imprimeClientesPorNome() const
{
    vector <Cliente *> copia_clientes = clientes;
    sort(copia_clientes.begin(), copia_clientes.end(), sort_clientes_nome);
    cabecalho_lista_clientes();
	for (unsigned i = 0; i < copia_clientes.size(); i++)
	{
		copia_clientes[i]->imprimir(cout);
	}
	
}

void Empresa::imprimeClientesInativosPorNome() const
{
    vector <Cliente*> copia_clientes_inativos;
    for(auto itr = clientesInativos.begin(); itr != clientesInativos.end(); itr++)
    {
        copia_clientes_inativos.push_back(*itr);
    }

    sort(copia_clientes_inativos.begin(), copia_clientes_inativos.end(), sort_clientes_nome);
    cabecalho_lista_clientes();
    for (unsigned i = 0; i < copia_clientes_inativos.size(); i++)
    {
        copia_clientes_inativos[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

bool sort_clientes_cidade(Cliente* cli1, Cliente* cli2)
{
    return cli1->getMorada() < cli2->getMorada();
}

void Empresa::imprimeClientesPorCidade() const
{
    vector <Cliente *> copia_clientes = clientes;
    sort(copia_clientes.begin(), copia_clientes.end(), sort_clientes_cidade);
    cabecalho_lista_clientes();
    for (unsigned i = 0; i < copia_clientes.size(); i++)
    {
        copia_clientes[i]->imprimir(cout);
    }

}

void Empresa::imprimeClientesInativosPorCidade() const
{
    vector <Cliente*> copia_clientes_inativos;
    for(auto itr = clientesInativos.begin(); itr != clientesInativos.end(); itr++)
    {
        copia_clientes_inativos.push_back(*itr);
    }

    sort(copia_clientes_inativos.begin(), copia_clientes_inativos.end(), sort_clientes_cidade);
    cabecalho_lista_clientes();
    for (unsigned i = 0; i < copia_clientes_inativos.size(); i++)
    {
        copia_clientes_inativos[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

bool sort_clientes_quantidade_servicos(Cliente* cli1, Cliente* cli2)
{
    return cli1->getServicosRequisitados().size() > cli2->getServicosRequisitados().size();
}

void Empresa::imprimeClientesPorQuantidadeServicos() const
{
    vector <Cliente *> copia_clientes = clientes;
    sort(copia_clientes.begin(), copia_clientes.end(), sort_clientes_quantidade_servicos);
    cabecalho_lista_clientes();
    for (unsigned i = 0; i < copia_clientes.size(); i++)
    {
        copia_clientes[i]->imprimir(cout);
    }

}

void Empresa::imprimeClientesInativosPorQuantidadeServicos() const
{
    vector <Cliente*> copia_clientes_inativos;
    for(auto itr = clientesInativos.begin(); itr != clientesInativos.end(); itr++)
    {
        copia_clientes_inativos.push_back(*itr);
    }

    sort(copia_clientes_inativos.begin(), copia_clientes_inativos.end(), sort_clientes_quantidade_servicos);
    cabecalho_lista_clientes();
    for (unsigned i = 0; i < copia_clientes_inativos.size(); i++)
    {
        copia_clientes_inativos[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

bool sort_funcionarios_nome(Funcionario* func1, Funcionario* func2)
{
    return func1->getNome() < func2->getNome();
}

void Empresa::imprimeFuncionariosPorNome() const
{
    vector <Funcionario*> copia_funcionarios = funcionarios;
    for(auto it = condutores.begin(); it != condutores.end(); it++)
    {
        copia_funcionarios.push_back(*it);
    }

    sort(copia_funcionarios.begin(),copia_funcionarios.end(),sort_funcionarios_nome);

    cabecalho_lista_funcionario();

    for (unsigned i = 0; i < copia_funcionarios.size(); i++)
    {
        copia_funcionarios[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

bool sort_funcionarios_cidade(Funcionario* func1, Funcionario* func2)
{
    return func1->getMorada() < func2->getMorada();
}

void Empresa::imprimeFuncionariosPorCidade() const
{
    vector <Funcionario *> copia_funcionarios = funcionarios;
    for(auto it = condutores.begin(); it != condutores.end(); it++)
    {
        copia_funcionarios.push_back(*it);
    }
    sort(copia_funcionarios.begin(), copia_funcionarios.end(), sort_funcionarios_cidade);
    cabecalho_lista_funcionario();

    for (unsigned i = 0; i < copia_funcionarios.size(); i++)
    {
        copia_funcionarios[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

bool sort_funcionarios_salario(Funcionario* func1, Funcionario* func2)
{
    return func1->getSalario() > func2->getSalario();
}

void Empresa::imprimeFuncionariosPorSalario() const
{
    vector <Funcionario *> copia_funcionarios = funcionarios;
    for(auto it = condutores.begin(); it != condutores.end(); it++)
    {
        copia_funcionarios.push_back(*it);
    }
    sort(copia_funcionarios.begin(), copia_funcionarios.end(), sort_funcionarios_salario);
    cabecalho_lista_funcionario();

    for (unsigned i = 0; i < copia_funcionarios.size(); i++)
    {
        copia_funcionarios[i]->imprimir(cout);
    }

}


/***************************************************************************************************************/
bool sort_camioes_ano(Camiao* cam1, Camiao* cam2)
{
    return cam1->getAno() > cam2->getAno();

}
void Empresa::imprimeCamioesPorAno() const
{
    vector <Camiao *> copia_camioes = camioes;
    sort(copia_camioes.begin(), copia_camioes.end(), sort_camioes_ano);
    cabecalho_lista_camioes();
    for (unsigned i = 0; i < copia_camioes.size(); i++)
    {
        copia_camioes[i]->imprimir(cout);
    }

}
/***************************************************************************************************************/

bool sort_camioes_capacidade(Camiao* cam1, Camiao* cam2)
{
    return cam1->getCapacidade() > cam2->getCapacidade();

}
void Empresa::imprimeCamioesPorCapacidade() const
{
    vector <Camiao *> copia_camioes = camioes;
    sort(copia_camioes.begin(), copia_camioes.end(), sort_camioes_capacidade);
    cabecalho_lista_camioes();
    for (unsigned i = 0; i < copia_camioes.size(); i++)
    {
        copia_camioes[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

bool sort_servicos_data(Servico* serv1, Servico* serv2)
{
    return !estaDepois(serv2->getDataObjecto(), serv1->getDataObjecto());

}
void Empresa::imprimeServicosPorData() const
{
    vector <Servico *> copia_servicos = servicos;
    sort(copia_servicos.begin(), copia_servicos.end(), sort_servicos_data);
    cabecalho_lista_servicos();
    for (unsigned i = 0; i < copia_servicos.size(); i++)
    {
        copia_servicos[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

bool sort_servicos_nif(Servico* serv1, Servico* serv2)
{
    return serv1->getCliente()->getNif() > serv2->getCliente()->getNif();

}
void Empresa::imprimeServicosPorNIF() const
{
    vector <Servico *> copia_servicos = servicos;
    sort(copia_servicos.begin(), copia_servicos.end(), sort_servicos_nif);
    cabecalho_lista_servicos();
    for (unsigned i = 0; i < copia_servicos.size(); i++)
    {
        copia_servicos[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

bool sort_servicos_tempo(Servico* serv1, Servico* serv2)
{
    return serv1->getTempo() > serv2->getTempo();

}
void Empresa::imprimeServicosPorTempoViagem() const
{
    vector <Servico *> copia_servicos = servicos;
    sort(copia_servicos.begin(), copia_servicos.end(), sort_servicos_tempo);
    cabecalho_lista_servicos();
    for (unsigned i = 0; i < copia_servicos.size(); i++)
    {
        copia_servicos[i]->imprimir(cout);
    }

}

/***************************************************************************************************************/

Cliente* Empresa::procuraNifClientes(int nif)
{
    for (unsigned i = 0; i < clientes.size(); i++){
        if (clientes[i]->getNif() == nif)
            return clientes[i];
    }
    throw clienteInexistente(nif);
}

/***************************************************************************************************************/

vector<Funcionario*> Empresa::procuraCargoFuncionarios(string cargo)
{
    vector<Funcionario *> result;
    result.clear();

    if(cargo == "condutor")
    {
        for(auto it = condutores.begin(); it != condutores.end(); it++)
        {
            result.push_back((*it));
        }
    }
    else
    {
        for (auto it = funcionarios.begin();it != funcionarios.end(); it++)
        {
            if ((**it).getCargo() == cargo)
            {
                result.push_back(*it);
            }

        }
    }

    if (result.size()==0) throw funcionarioCargoInexistente(cargo);

    return result;
}

/***************************************************************************************************************/

vector<Camiao*> Empresa::procuraTipoCamiao(string tipo)
{
	vector<Camiao *> result;
	result.clear();
    for (vector <Camiao *>::iterator it = camioes.begin(); it != camioes.end(); it++)
	{
		if ((*it)->getTipoMercadoria() == tipo)
		{
			result.push_back(*it);
		}
	}
	return result;
}

/***************************************************************************************************************/

Funcionario* Empresa::procuraNifFuncionarios(int nif)
{
    for(auto it = condutores.begin(); it != condutores.end(); it++)
    {
        if((*it)->getNif() == nif)
            return (*it);
    }
	for (unsigned i = 0; i < funcionarios.size(); i++)
	{
		if (funcionarios[i]->getNif() == nif)
			return funcionarios[i];
	}
	throw funcionarioInexistente(nif);
}

/***************************************************************************************************************/

Camiao* Empresa::procuraMatriculaCamiao(string matricula)
{
    for (auto it = camioes.begin(); it != camioes.end(); it++)
    {
        if ((*it)->getMatricula() == matricula)
            return *it;
    }
    throw camiaoInexistente(matricula);
}

/***************************************************************************************************************/

void Empresa::apagarCliente(Cliente* clientePtr)
{
	for (auto it = clientes.begin(); it != clientes.end(); it++)
	{
		if (*it == clientePtr) { clientes.erase(it); cout << "\nCliente removido com sucesso.\n"; break; }
	}
}

/***************************************************************************************************************/

void Empresa::apagarFuncionario(Funcionario *func_ptr)
{
    for(auto it=funcionarios.begin();it!=funcionarios.end();it++)
    {
		if (*it == func_ptr) { funcionarios.erase(it); it--; cout << "\nFuncionario removido com sucesso.\n"; break; }
    }
}

/***************************************************************************************************************/

void Empresa::apagarCamiao(Camiao *camiaoPtr)
{
	for (auto it = camioes.begin(); it != camioes.end(); it++)
	{
		if (*it == camiaoPtr) { camioes.erase(it); it--; cout << "\nCamiao removido com sucesso.\n"; break; }
	}
}

/***************************************************************************************************************/

void Empresa::adicionarCliente()
{

	string nome, morada, str;
	int nif, telefone;

	cout << "\nIndique o nome (Enter para cancelar):\n> ";
	getline(cin, nome);
	if (nome.empty())
		return;

	do{
        try {
            nif = validadeNIF("\nIndique o NIF (Enter para cancelar):\n> ", *this, true);
            if(!nif)
                return;
            else
                break;
        }
        catch(numInvalido &e)
        {
            cout<<e;
            return;
        }
	}while(true);


	do
	{
		cout << "\nIndique o numero telefone (Enter para cancelar):\n> ";
		getline(cin, str);
		if (!str.empty())
		{
			telefone = PositiveNumber(str);
			if (telefone == -1)
				cout << "\nIntroduza uma numero de telefone valido.\n";
			else
				break;
		}
		else
			return;
	} while (true);


	cout << "\nIndique a morada (Enter para cancelar):\n> ";
	getline(cin, morada);
	if (morada.empty())
		return;

	vector<int> v;
	Cliente* cliente = new Cliente(nome, nif, telefone, morada, v);
	clientes.push_back(cliente);
	
	cout << "\nO cliente foi adicionado com sucesso!\n";
}

/***************************************************************************************************************/

void Empresa::adicionarFuncionario(int tipo) {

    string nome, morada, str,sinput;
    int nif, telefone;
    float salario;

    cout << "\nIndique o nome (Enter para cancelar):\n> ";
    getline(cin, nome);
    if (nome.empty())
        return;

    do{
        try {
            nif = validadeNIF("\nIndique o NIF (Enter para cancelar):\n> ", *this, true);
            if (!nif)
                return;
            else
                break;
        }
        catch (numInvalido &e) {
            cout << e;
            return;
        }
    }while(true);


    do {
        try {
            cout << "\nIndique o numero telefone (Enter para cancelar):\n> ";
            getline(cin, str);
            if (str == "") return;
            telefone = PositiveNumber(str);
            break;
        }
        catch(numInvalido &e)
        {
            cout<<e;
        }
    } while (true);


    cout << "\nIndique a morada (Enter para cancelar):\n> ";
    getline(cin, morada);
    if (morada.empty())
        return;

    do {
        try {

            cout << "\nIndique o salario separando as casas decimais com um ponto (Enter para cancelar):\n> ";
            getline(cin, sinput);
            if (sinput == "") return;
            salario = validadeSalario(sinput);
            break;
        }
        catch (numInvalido &e)
        {
            cout<<e;
        }
    } while (true);

    switch (tipo) {
        case 1: {
            /*
            string sinput;
            vector<int> servicos;

            cout << "Digite os IDs dos serviços associados a esse condutor separados por virgulas:\n";
            getline(cin, sinput);

            for (auto i:string_split(sinput, ',')) {
                servicos.push_back(stoi(i));
            }
             */
            Condutor* condutor = new Condutor(nome, nif, telefone, morada, salario, "condutor", {}, 0);
            condutores.insert(condutor);
            break;
        }
        case 2: {
            string cargo;
            cout << "Indique o cargo:\n";
            getline(cin, cargo);
            Funcionario *funcionario = new Funcionario(nome, nif, telefone, morada, salario, cargo);
            funcionarios.push_back(funcionario);
            break;
        }
        default: {
            cout << "A opcao que introduziu nao e valida!\n";
            break;
        }
    }
    cout << "O funcionario foi adicionado com sucesso!\n";
}

/***************************************************************************************************************/

bool organizavetor(pair<Camiao*,int> p1, pair<Camiao*,int> p2)
{
    return p1.second < p2.second;
}

/***************************************************************************************************************/

void Empresa::adicionarServico(Cliente* clientePtr = nullptr)
{
    int id = servicos.size() +1, nif;
    string origem, destino, data, hora_inicio, duracao, tipo_mercadoria, matriculas, tipo_servico;
    Data *date;

    cout << "\nIndique o local de origem (Enter para cancelar):\n> ";
    getline(cin, origem);
    if (origem.empty())
        return;

    cout << "\nIndique o local de destino (Enter para cancelar):\n> ";
    getline(cin, destino);
    if (destino.empty())
        return;


    do {
        cout << "\nIndique a data (AAAA/MM/DD) (Enter para cancelar):\n> ";
        getline(cin, data);
        if (data.empty())
            return;

        date = new Data(data);
        if (!date->validade()) {
            cout << "A data introduzida nao e valida.\n\n";
        } else
            break;
    }while (true);

    cout << "\nIndique a hora de inicio (HH:MM) (Enter para cancelar):\n> ";
    getline(cin, hora_inicio);
    if (hora_inicio.empty())
        return;

    cout << "\nIndique a duracao (HH:MM) (Enter para cancelar):\n> ";
    getline(cin, duracao);
    if (duracao.empty())
        return;


    do{
        cout << "\nIndique o tipo de mercadoria a transportar (outros/animais/explosivos/congelados) (Enter para cancelar):\n> ";
        getline(cin, tipo_mercadoria);
        if(tipo_mercadoria.empty())
            return;
        else if (tipo_mercadoria == "outros" || tipo_mercadoria == "animais" || tipo_mercadoria == "explosivos" || tipo_mercadoria == "congelados")
            break;
        else
            cout << "\nIntroduza um tipo de mercadoria valido.\n";
    }while (true);

    string str;
    int n_cams;
    do
    {
        try
        {
            cout << "\nIndique o numero camioes necessarios (Enter para cancelar):\n> ";
            getline(cin, str);
            if (!str.empty()) {
                n_cams = PositiveNumber(str);
                break;
            }
            else
                return;
        }
        catch (numInvalido &e)
        {
            cout << e;
        }
    }while(true);


    vector<Camiao*> vcams = procuraTipoCamiao(tipo_mercadoria);

    for(unsigned i = 0; i < vcams.size(); i++)
    {
        if(vcams[i]->getTipoMercadoria() != tipo_mercadoria)
            vcams.erase(vcams.begin() + i);
    }

    if(vcams.size() < n_cams)
    {
        cout << "\nNao existem camioes suficientes para o tipo de mercadoria especificado.\n";
        return;
    }


    string pergunta;
    if(tipo_mercadoria == "animais")
        pergunta = "\nIndique as especies a transportar em cada camiao (Enter para cancelar):\n> ";
    else if (tipo_mercadoria == "explosivos")
        pergunta = "\nIndique o nivel de perigo da carga a transportar em cada camiao (Enter para cancelar):\n> ";


    if(tipo_mercadoria == "animais" || tipo_mercadoria == "explosivos")
    {
        vector<string> especificacoes;
        for(unsigned i = 0; i < n_cams; i++)
        {
            cout << pergunta;
            getline(cin, str);
            if (str.empty())
                return;
            especificacoes.push_back(str);
        }
    }
    else if (tipo_mercadoria == "congelados")
    {
        vector<int> especificacoes;
        int temperatura;
        for(unsigned i = 0; i < n_cams; i++)
        {
            do{
                try
                {

                    cout << "\nIndique a temperatura necessaria para a carga a transportar em cada camiao:\n> ";
                    getline(cin, str);
                    if (!str.empty())
                    {
                        temperatura = NegativeZeroPositiveNumber(str);
                        especificacoes.push_back(temperatura);
                        break;
                    }
                    else
                        return;
                }
                catch (numInvalido &e)
                {
                    cout << e;
                }
            }while(true);

        }
    }

    if(clientePtr == nullptr)
    {
        do{
            try {
                nif = validadeNIF("\nInserir NIF do cliente desejado (Enter para cancelar):\n> ", *this, false);
                if (!nif)
                    return;
                clientePtr = procuraNifClientes(nif);
                break;
            }
            catch (numInvalido &e) {
                cout << e;
            }
            catch (clienteInexistente &e)
            {
                cout<<e;
            }
        }while(true);

    }

    do
    {
        cout << "\nIndique o tipo de servico (pontual/diario/mensal) (Enter para cancelar):\n> ";
        getline(cin, tipo_servico);
        if (!tipo_servico.empty())
        {
            if (!(tipo_servico == "pontual" || tipo_servico == "diario" || tipo_servico == "mensal"))
                cout << "\nIntroduza um tipo de servico valido.\n";
            else
                break;
        }
        else
            return;
    } while (true);


    vector<pair<Camiao*,int>> vcams_counter;
    for(unsigned i = 0; i < vcams.size(); i++)
        vcams_counter.push_back(make_pair(vcams[i], 0));

    vector<Camiao*> camioes_usados;
    string hora_final, hora_final_servico;
    bool apagar;
    for(auto it = servicos.begin(); it != servicos.end(); it++)
    {
        apagar = false;
        camioes_usados = (*it)->getCamioes();
        for(unsigned i = 0; i < vcams_counter.size(); i++)
        {
            if(find(camioes_usados.begin(), camioes_usados.end(), vcams_counter[i].first) != camioes_usados.end())
                ++vcams_counter[i].second;
        }
        vector<string> data_servico_separada = string_split((*it)->getData(), '/');
        if((tipo_servico == "pontual" && date->isEqualTo((*it)->getData())) || (tipo_servico == "diario") || (tipo_servico == "mensal" && date->getDia() == stoi(data_servico_separada[0])))
        {
            if(hora_inicio < (*it)->getHora_inicio())
            {
                hora_final = calculaHoraFinal(hora_inicio, duracao);
                if(hora_final >= (*it)->getHora_inicio()) // TERA QUE ACABAR ANTES QUE O SERVICO COMECE
                    apagar = true;
            }
            else    // NO CASO DE A HORA PEDIDA COMECAR DEPOIS/AO MESMO TEMPO QUE O SERVICO
            {
                hora_final_servico = calculaHoraFinal((*it)->getHora_inicio(),(*it)->getTempo());
                if(hora_inicio >= hora_final_servico) // TERA QUE COMEÇAR DEPOIS DO SERVICO ACABAR
                    apagar = true;
            }
            if(apagar)
            {
                for(unsigned i = 0; i < vcams_counter.size(); i++)
                {
                    if(find(camioes_usados.begin(), camioes_usados.end(), vcams_counter[i].first) != camioes_usados.end())
                        vcams_counter.erase(vcams_counter.begin() + i); // APAGA DO VECTOR DE CAMIOES DISPONIVEIS TODOS OS CAMIOES EM COMUM COM ESTE SERVIÇO
                }
            }
            if(vcams_counter.size() < n_cams)
            {
                cout << "\nNao existem camioes suficientes para o tipo de mercadoria especificado.\n";
                return;
            }
        }
    }


    for(unsigned i = 0; i < vcams_counter.size(); i++)
    {
        vcams_counter[i].first->getSegundoCampo();
    }

    sort(vcams_counter.begin(), vcams_counter.end(), organizavetor);
    vector<Camiao *> vcams_final;

    for(unsigned i = 0; i < n_cams; i++)
    {
        vcams_final.push_back(vcams_counter[i].first);
    }

    vector<int> requisitados = clientePtr->getServicosRequisitados();
    requisitados.push_back(id);
    clientePtr->setServicosRequisitados(requisitados);

    Servico* serv_ptr = new Servico(id,origem,destino,duracao,date,hora_inicio,tipo_mercadoria,tipo_servico,clientePtr,vcams_final);
    servicos.push_back(serv_ptr);


    cout << "\nO servico foi adicionado com sucesso!\n";
}


void Empresa::adicionarCamiao() {
    string matricula, marca, modelo, tipo, str;
    int ano, capacidade;

    do
    {
        try {
            matricula = validadeMatricula("\nIndique a matricula (Enter para cancelar):\n> ", *this, true);
            if (matricula.empty())
                return;
            else
                break;
        }
        catch (matriculaInvalida &e) {
            cout << e;
        }
    }while(true);

    cout << "\nIndique a marca (Enter para cancelar):\n> ";
    getline(cin, marca);
    if (marca.empty())
        return;

    cout << "\nIndique o modelo (Enter para cancelar):\n> ";
    getline(cin, modelo);
    if (modelo.empty())
        return;

    do {
        try
        {
            cout << "\nIndique o ano (Enter para cancelar):\n> ";
            getline(cin, str);
            ano = PositiveNumber(str);
            if (!str.empty())
                break;
            else
                return;
        }
        catch (numInvalido &e)
        {
            cout << e;
        }
    } while (true);

    do {
        try
        {
            cout << "\nIndique a capacidade em toneladas(Enter para cancelar):\n> ";
            getline(cin, str);
            capacidade = PositiveNumber(str);
            if (!str.empty())
                break;
            else
                return;
        }
        catch (numInvalido &e)
        {
            cout << e;
        }
    } while (true);

    do
    {
        cout << "\nIndique o tipo de mercadoria a ser transportada (congelados/perigosas/animais/outros) (Enter para cancelar):\n> ";
        getline(cin,str);
        if (str.empty())
            return;
        else if (str == "congelados" || str == "perigosas" ||str == "animais" ||str == "outros")
        {
            tipo = str;
            break;
        }
        else
            cout << "\nTipo de mercadoria invalido.\n";
    }while(true);

    Camiao* cam;
    if(str == "congelados")
    {
        int temperatura;
        do{
            try
            {

                cout << "\nIndique a temperatura necessaria para a carga a transportar em cada camiao:\n> ";
                getline(cin, str);
                temperatura = NegativeZeroPositiveNumber(str);
                if (!str.empty())
                    break;
                else
                    return;
            }
            catch (numInvalido &e)
            {
                cout << e;
            }
        }while(true);
        cam = new Camiao_congelados(capacidade, matricula, marca, modelo, ano, tipo, temperatura);
    }
    else if (str == "perigosas")
    {
        string nivel;
        cout << "\nIndique o nivel de perigo (Enter para cancelar):\n> ";
        getline(cin, nivel);
        if (nivel.empty())
            return;
        cam = new Camiao_perigo(capacidade, matricula, marca, modelo, ano, tipo, nivel);
    }
    else if (str == "animais")
    {
        string especie;
        cout << "\nIndique a especie (Enter para cancelar):\n> ";
        getline(cin, especie);
        if (especie.empty())
            return;
        cam = new Camiao_animal(capacidade, matricula, marca, modelo, ano, tipo, especie);
    }
    else
        cam = new Camiao(capacidade, matricula, marca, modelo, ano, tipo);

    camioes.push_back(cam);

    cout << "\nO camiao foi adicionado com sucesso!\n";
}

/***************************************************************************************************************/

vector<Servico *> Empresa::procuraTipoMercadoriaServico(string tipo_mercadoria)
{
    vector<Servico *> result;
    result.clear();

    for (auto it = servicos.begin();it != servicos.end(); it++)
    {
        if ((**it).getTipoMercadoria() == tipo_mercadoria)
        {
            result.push_back(*it);
        }

    }

    if (result.size()==0) throw servicoTipoMercadoriaInexistente(tipo_mercadoria);

    return result;
}
/***************************************************************************************************************/

vector<Servico *> Empresa::procuraPeriodicidadeServico(string periodicidade)
{
    vector<Servico *> result;
    result.clear();

    for (auto it = servicos.begin();it != servicos.end(); it++)
    {
        if ((**it).getTipoServico() == periodicidade)
        {
            result.push_back(*it);
        }

    }

    if (result.size()==0) throw servicoPeriodicidadeInexistente(periodicidade);

    return result;
}

/***************************************************************************************************************/

void Empresa::lucroTotal() const
{
    float lucro_pontual = 0, lucro_diario = 0, lucro_mensal = 0, temp;
    double tempo= 0;
    for(auto i: servicos)
    {
        //so calcula para o caso de a data atual proceder/for igual à data do serviço e se a hora atual proceder a hora final do serviço
        string hora_final = calculaHoraFinal(i->getHora_inicio(), i->getTempo()) + ":00";
        //cout << servicos[j-1]->getData() << endl << hora_final << endl << endl;
        if(i->getData() <= data_atual || (i->getData() == data_atual &&  hora_final <= hora_atual)) {
            vector<Camiao *> v_cams = i->getCamioes();

            vector<string> hor_sep = string_split(i->getTempo(), ':');
            double horas_servico = stod(hor_sep[0]) + stod(hor_sep[1]) / 60.0;
            if (i->getTipoServico() == "pontual") {
                tempo = horas_servico;
                for (auto it3 = v_cams.begin(); it3 != v_cams.end(); it3++) {
                    lucro_pontual += (*it3)->custo(tempo, (*it3)->getCapacidade());
                }
            } else {
                vector<string> aux = string_split(data_atual, '/');
                Data actual_date(stoi(aux[0]), 1 + stoi(aux[1]), stoi(aux[2])), serv_date = *i->getDataObjecto();
                if (i->getTipoServico() == "diario") {
                    long unsigned int num_dias_entre_datas =
                            actual_date.numDiasDesdeCristo() - serv_date.numDiasDesdeCristo();
                    tempo += num_dias_entre_datas * horas_servico;
                    if (hora_final < hora_atual)
                        tempo += horas_servico;
                    for (auto it3 = v_cams.begin(); it3 != v_cams.end(); it3++) {
                        lucro_diario += (*it3)->custo(tempo, (*it3)->getCapacidade());
                    }
                } else if (i->getTipoServico() == "mensal") {
                    int n_meses = 1; //se entrou no primeiro if, este serviço é sempre efetuado, nem que seja uma sp vez (no dia em que foi criado)
                    if (serv_date.getAno() < actual_date.getAno()) {
                        n_meses += 12 - serv_date.getMes(); // num de meses para completar esse ano
                        n_meses += (actual_date.getAno() - serv_date.getAno() + 1) *
                                   12; // adiciona-se 12 por cada ano completo entre o ano de serviço e o ano atual
                        n_meses += actual_date.getMes(); //agora adiciona-se o numero de meses do ano atual
                    } else {
                        n_meses += actual_date.getMes() - serv_date.getMes(); //n de meses entre os meses
                    }
                    if (actual_date.getDia() < serv_date.getDia() || (actual_date.getDia() == serv_date.getDia() &&
                                                                      hora_atual <
                                                                      hora_final))  // se ainda nao passou o dia do serviço neste mes, retira-se 1
                        n_meses--;
                    tempo += horas_servico * n_meses;
                    for (auto it3 = v_cams.begin(); it3 != v_cams.end(); it3++) {
                        lucro_mensal += (*it3)->custo(tempo, (*it3)->getCapacidade());
                    }
                }
            }
        }
    }
    cout << "\nLucro de servicos pontuais: " << lucro_pontual
    << " euros\nLucro de servicos diarios: " << lucro_diario
    << " euros\nLucro de servicos mensais: " << lucro_mensal
    << " euros\nLucro total (aproximado): " << lucro_pontual << " euros (pontual) + " << lucro_diario*30 + lucro_mensal << " euros (todos os meses)\n";
}

/***************************************************************************************************************/

void Empresa::estatisticas()
{
    int num_condutores = 0;
    for(auto it = condutores.begin(); it != condutores.end(); it++)
        num_condutores++;
    cout << "\nNumero total de clientes: " << clientes.size();
    cout << "\nNumero total de clientes inativos: " << clientesInativos.size();
    cout << "\nNumero total de condutores: " << num_condutores;
    cout << "\nNumero total de outros funcionarios: " << funcionarios.size();
    cout << "\nNumero total de servicos: " << servicos.size();
    cout << "\nNumero total de camioes: " << camioes.size() << endl;
    lucroTotal();

}

/***************************************************************************************************************/

void Empresa::apagarServico(Servico *servico)
{
    for (auto it = servicos.begin(); it != servicos.end(); it++) {
        if (*it == servico)
        {
            servicos.erase(it);
            it--;
            cout << "\nServico removido com sucesso.\n";
            break;
        }
    }
}

/***************************************************************************************************************/

priority_queue<Oficina> Empresa::getOficinas() const
{
    return oficinas;
}

/***************************************************************************************************************/

void Empresa::adicionarOficina()
{
    string str,denom;

    cout<<"Indique o nome da oficina (Enter para cancelar):\n> ";
    getline(cin,denom);
    if (denom.empty())
        return;

    vector<Servico_Oficina*> servs;
    servs.clear();

    cout<<"Indique as marcas que com que a oficina trabalha para servicos especializados(separe as marcas com virgulas) (Enter para cancelar):\n> ";
    getline(cin,str);
    if(str.empty())
        return;
    Oficina nova_oficina=Oficina(oficinas.size()+1,denom,string_split(str,','),0,servs);

    oficinas.push(nova_oficina);

    cout<<"A oficina foi adicionada com sucesso!\n";
}

/***************************************************************************************************************/

void Empresa::removerOficina()
{
    bool found=false;
    string str;
    int id;

    do
    {
        try
        {
            cout<<"\nIndique o ID da oficina a remover (Enter para cancelar):\n> ";
            getline(cin,str);
            if(str.empty())
                return;
            id = PositiveNumber(str);
            break;
        }
        catch (numInvalido &e)
        {
            cout << e;
        }
    }while(true);


    vector<Oficina> copy;

    while(!oficinas.empty())
    {
        if (oficinas.top().getId()==id)
        {
            found=true;
        }
        else
            copy.push_back(oficinas.top());
        oficinas.pop();
    }

    for (auto i:copy)
    {
        oficinas.push(i);
    }

    if (!found) throw oficinaInexistente();
    cout << "\nOficina removida com sucesso.\n";
}

/***************************************************************************************************************/

void Empresa::adicionarServicoOficina()
{
    srand(time(NULL));

    string matricula,str;
    int id=++servico_oficina_id_atual;
    Camiao* cam_ptr;
    bool esp,found=false,found2=false;

    matricula = validadeMatricula("\nIndique a matricula do veiculo (Enter para cancelar):\n> ", *this, false);
    if (matricula=="")
        return;

    auto copy=oficinas;

    while (!copy.empty())
    {
        for (auto i:copy.top().getServicos())
        {
            if (i->getCamiao()->getMatricula()==matricula)
            {
                throw camiaoEmReparacao();
            }
        }
        copy.pop();
    }

    for (auto i:camioes)
    {
        if (i->getMatricula()==matricula) cam_ptr=i;
    }

    do
    {
        cout<<"\nO servico e especifico? (Responda com \"sim\" ou \"nao\") (Enter para cancelar)\n> ";
        getline(cin,str);
        if (str.empty()) return;
        if (str=="sim")
        {
            esp=true;
            break;
        }
        else if (str=="nao")
        {
            esp=false;
            break;
        }
        else cout<<"\nIntroduza uma opcao valida!\n";
    }while(true);

    int duracao=rand()%7+1;

    Servico_Oficina* servico_novo=new Servico_Oficina(id,esp,cam_ptr,duracao);

    if (esp)
    {
        vector<Oficina> copy;
        while (!oficinas.empty())
        {
            copy.push_back(oficinas.top());
            oficinas.pop();
        }
        for (auto i:copy)
        {
            for (auto i2:i.getMarcas())
            {
                if (i2==cam_ptr->getMarca() && !found2)
                {
                    found2=true;
                    i.adicionarServico(servico_novo);
                }
            }
            oficinas.push(i);
        }
        if (!found2) throw oficinaInexistente();
    }
    else
    {
        Oficina topo=oficinas.top();
        oficinas.pop();
        topo.adicionarServico(servico_novo);
        oficinas.push(topo);
    }

    cout<<"O servico foi adicionado com sucesso!\n";

}

/***************************************************************************************************************/

void Empresa::removerServicoOficina()
{
    string str;
    bool found=false;
    int id;

    do
    {
        try {
            cout<<"Indique o ID do serviço a terminar (Enter para cancelar):\n> ";
            getline(cin,str);
            if(str.empty())
                return;
            id = PositiveNumber(str);
            break;
        }
        catch (numInvalido &e)
        {
            cout << e;
        }
    }while(true);


    vector<Oficina> copy;

    while(!oficinas.empty())
    {
        copy.push_back(oficinas.top());
        oficinas.pop();
    }

    for (auto i:copy)
    {
        for (auto i2:i.getServicos())
        {
            if (i2->getId()==id)
            {
                found=true;
                i.removerServico(i2);
            }
        }
        oficinas.push(i);
    }

    if (!found) throw servicoOficinaInexistente();

    cout << "\nServico terminado com sucesso.\n";

}

/***************************************************************************************************************/

vector<Oficina> Empresa::procurarOficinas(string marca)
{
    vector<Oficina> result;
    bool found=false;
    auto copy=oficinas;

    while (!copy.empty())
    {
        for (auto i:copy.top().getMarcas())
        {
            if (i==marca)
            {
                found=true;
                result.push_back(copy.top());
                break;
            }
        }
        copy.pop();
    }

    if (!found) throw oficinaInexistente();

    return result;
}

/***************************************************************************************************************/

Oficina Empresa::procurarOficina(int id)
{
    auto copy=oficinas;

    while (!copy.empty())
    {
        if (copy.top().getId()==id)
            return copy.top();
        copy.pop();
    }

    throw oficinaInexistente();
}

/***************************************************************************************************************/

void cabecalho_lista_oficinas()
{
    cout << "ID " << setw(15)
         << "NOME" << setw(40)
         << "NUMEROS DIAS INDISPONIVEL" << setw(20)
         << "MARCAS" << setw(35)
         << "SERVICOS ASSOCIADOS" << endl;
}

/***************************************************************************************************************/

void cabecalho_lista_clientes()
{
    cout << "NOME " << setw(32)
         << "NIF" << setw(20)
         << "TELEFONE" << setw(15)
         << "MORADA" << setw(30)
         << " SERVICOS REQUISITADOS" << endl;
}

/***************************************************************************************************************/

void cabecalho_lista_funcionario()
{
    cout << "NOME " << setw(15)
         << "NIF" << setw(20)
         << "TELEFONE" << setw(15)
         << "CIDADE" << setw(13)
         << "CARGO" << setw(15)
         << "SALARIO" << setw(10)
         << "HORAS" << setw(25)
         << "SERVICOS ASSOCIADOS" << endl;
}

/***************************************************************************************************************/

void cabecalho_lista_camioes()
{
    cout << "MATRICULA " << setw(10)
         << "MARCA" << setw(10)
         << "MODELO" << setw(10)
         << "ANO" << setw(15)
         << "CAPACIDADE" << setw(25)
         << "TIPO DE MERCADORIA" << endl;
}

/***************************************************************************************************************/

void cabecalho_lista_servicos()
{
    cout << "ID " << setw(10)
         << "ORIGEM" << setw(15)
         << "DESTINO" << setw(10)
         << "DATA" << setw(20)
         << "TEMPO DE VIAGEM" << setw(15)
         << "NIF cliente" << setw(15)
         << "CAMIOES" << endl;
}

/***************************************************************************************************************/
