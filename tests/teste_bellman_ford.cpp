#include <iostream>
#include "../headers/grafo_vetor_peso.hpp"

using namespace std;

int 
main ()
{ 
    const string nome_arquivo = "grafo.txt";
    vertice t;
    grafo_vetor_peso grafo (nome_arquivo);
    cout << "vertice t para algoritmo bellman-ford: " << endl;
    cin >> t;
    retorno_bellman_ford resultado = grafo.bellman_ford (t);

    for (vertice v = 0; v < grafo.obter_numero_de_vertices(); v++)
        cout << "custo[" << v+1 << "] = " << resultado.custo_do_vertice[v] << endl;
    cout << endl;

    for (vertice v = 0; v < grafo.obter_numero_de_vertices(); v++)
        cout << "pai[" << v+1 << "] = " << 
        resultado.pai_do_vertice_no_caminho[v]+1 << endl;
    cout << endl;

    cout << (resultado.ciclos_negativos ? "" : "NÃO ") << "temos ciclos negativos no grafo " << endl;
}