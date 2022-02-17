#include <iostream>
#include "../headers/grafo_vetor_peso.hpp"

using namespace std;

int 
main ()
{ 
    const string nome_arquivo = "receitapeso2.txt";
    vertice t;
    bool direcao = true;
    grafo_vetor_peso grafo(nome_arquivo, direcao);
    cout << "vertice t para algoritmo bellman-ford: " << endl;
    cin >> t;
    retorno_bellman_ford resultado = grafo.bellman_ford (--t);

    /*
    for (unsigned i = 0; i < grafo.obter_numero_de_vertices(); i++){
        cout << "[" << i+1 << "] -> ";
        for (auto vertice_ : grafo[i]){
            cout << vertice_.vertice_conectado+1 << ", ";
        }
        cout << endl;
    }
    */

    for (vertice v = 0; v < grafo.obter_numero_de_vertices(); v++)
        cout << "custo[" << v+1 << "] = " << resultado.custo_do_vertice[v] << endl;
    cout << endl;

    for (vertice v = 0; v < grafo.obter_numero_de_vertices(); v++)
        cout << "pai[" << v+1 << "] = " << 
        resultado.pai_do_vertice_no_caminho[v]+1 << endl;
    cout << endl;

    cout << (resultado.ciclos_negativos ? "" : "NAO ") << "temos ciclos negativos alcancaveis a partir do vertice escolhido " << endl;
}