#include "../headers/grafo_vetor_peso.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <string.h>
#include <chrono>

using namespace std;

int
main ()
{
    string nome_arquivo;
    cout << "caminho do arquivo de texto do grafo:" << endl;  
    getline (cin, nome_arquivo);
    bool direcionado = true;
    grafo_vetor_peso grafo(nome_arquivo, direcionado);
    
    cout << "obtendo numero de vertices: ";
    contador n_de_vertices = grafo.obter_numero_de_vertices();
    cout << n_de_vertices << endl;

    //Teste de distancias
    /*
    cout << "Distancia entre 1 e 10: " << grafo.distancia_alvo(1, 10) << endl;
    cout << "Caminho entre " << "1" << " e " << "10" << ":" << endl;
    for(auto it: grafo.caminho_alvo(1,10)){
        cout << it << ", ";
    }
    cout << endl;
    cout << "Distancia entre 1 e 20: " << grafo.distancia_alvo(1, 20) << endl;
    cout << endl;
    cout << "Distancia entre 1 e 30: " << grafo.distancia_alvo(1, 30) << endl;
    cout << endl;
    cout << "Distancia entre 1 e 40: " << grafo.distancia_alvo(1, 40) << endl;
    cout << endl;
    cout << "Distancia entre 1 e 50: " << grafo.distancia_alvo(1, 50) << endl;
    cout << endl;
    */
    

    //Teste do tempo das distancias
    /*
    auto comeco = chrono::steady_clock::now();
    int i;
    for(i=1; i<=100; i++){
        int random = rand() % n_de_vertices + 1;
        grafo.distancia_geral(random);
    }
    auto fim = chrono::steady_clock::now();
    cout << "Tempo das "<< i-1 << " distancias: "
        << chrono::duration_cast<chrono::milliseconds>(fim - comeco).count()
        << " ms" << endl;
    */

    //Teste da MST do grafo
    grafo.escrever_MST("mst_"+nome_arquivo);

    //Teste da rede de colaboração
    /*
    struct struct_colaboracao{
        int id;
        string nome;
    };
    //Dicionario para relacionar vertices e colaboradores
    map<int, string> associacao;
    ifstream arquivo ("rede_colaboracao_vertices.txt", ios::in);
    arquivo.seekg(0, arquivo.beg);
    string linha, nome, str_id;
    int id;
    for(int i=1; i<= 722385; i++){
        getline(arquivo, linha);
        str_id = linha.substr(0, linha.find(','));
        nome = linha.substr(linha.find(',')+1);
        id = stoi(str_id);
        associacao.insert({id, nome});
    }

    int dijkstra_id = 2722;
    vector<struct_colaboracao> colaboradores;
    //colaboradores.push_back({2722 ,"Edsger W. Dijkstra"});
    //colaboradores.push_back({11365 ,"Alan M. Turing"});
    colaboradores.push_back({471365 ,"J. B. Kruskal"});
    colaboradores.push_back({5709 ,"Jon M. Kleinberg"});
    colaboradores.push_back({11386 ,"Eva Tardos"});
    colaboradores.push_back({343930 ,"Daniel R. Figueiredo"});
    for(auto colaborador:colaboradores){
        cout << "Distancia de Dijkstra ate " << colaborador.nome << ": " 
        << grafo.distancia_alvo(dijkstra_id, colaborador.id) << endl;
        cout << "Caminho de Dijkstra ate " << colaborador.nome << ": " << endl;
        for(auto it: grafo.caminho_alvo(dijkstra_id, colaborador.id)){
            cout << associacao.at(it) << ", ";
        }
        cout << endl << endl;
    }
    */
}