#include "../headers/grafo_matriz.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    grafo_matriz grafo("receita de grafo.txt");

    cout << "matriz de adjacencia criada a partir de \"receita de grafo.txt\" :" << endl;
    grafo.print_matriz_de_adjacencia();
    return EXIT_SUCCESS;
}