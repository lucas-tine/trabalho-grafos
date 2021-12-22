#include "../headers/grafo_vetor.hpp"
#include <iostream>

using namespace std;

int
main (void)
{
    grafo_vetor grafo("receita de grafo.txt");
    cout << "vetor de adjacencia criado a partir de \"receita de grafo.txt\" :" << endl ;

    cout << "informacoes basicas sobre o grafo: " << "\n\n" <<
    "numero de vertices: " << grafo.obter_numero_de_vertices() << "\n" <<
    "numero de arestas: " << grafo.obter_numero_de_arestas() << "\n" <<
    "maior grau: " << grafo.maior_grau() << "\n" <<
    "menor grau: " << grafo.menor_grau() << "\n" <<
    "grau medio: " << grafo.grau_medio() << "\n" <<
    "grau mediano: " << grafo.grau_mediano() << "\n";
}