#include "../headers/grafo_vetor.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    grafo_vetor grafo("receita de grafo.txt");

    cout << "vetor de adjacencia criado a partir de \"receita de grafo.txt\" :" << endl ;

    for (unsigned i = 0; i < grafo.obter_numero_de_vertices(); i++)
    {
        for (unsigned j = 0; j < grafo.obter_numero_de_vertices(); j++)
        {
            cout << grafo.adjacentes (i, j) << ' ';
        }
        cout << endl;
    }
    
    return EXIT_SUCCESS;
}