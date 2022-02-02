#include "../headers/grafo_vetor_peso.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    string nome_arquivo;
    cout << "caminho do arquivo de texto do grafo:" << endl;  
    getline (cin, nome_arquivo);
    grafo_vetor_peso grafo(nome_arquivo);
    auto limite = min ((contador) grafo.obter_numero_de_vertices(),(contador) 30);
    cout << "vetor de adjacencia criado a partir de \"" << nome_arquivo << "\" :" << endl <<
    "* [enter] para seguir" ;
    cin.get();
    
    cout << "obtendo numero de vertices ..." << endl;
    contador n_de_vertices = grafo.obter_numero_de_vertices();

    for (unsigned i = 0; i < n_de_vertices; i++){
        cout << "[ " << i+1 << "] -> ";
        for (auto tupla : grafo[i]){
            cout << tupla.vertice_conectado+1 << ", ";
        }
        cout << endl;
    }
}