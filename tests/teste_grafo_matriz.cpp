#include "../headers/grafo_matriz.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    grafo_matriz grafo("receita de grafo2.txt");

    cout << "matriz de adjacencia criada a partir de \"receita de grafo.txt\" :" << endl << 
    grafo << endl;

    contador n_de_vertices = grafo.obter_numero_de_vertices();

    vertice pai[n_de_vertices], nivel[n_de_vertices];

    cout << "DFS" << endl;
    grafo.dfs(1, pai, nivel);
    for(contador i = 0; i<n_de_vertices; i++)
        cout << "pai[" << i+1 << "] = " << pai[i] << endl;
    for(contador i = 0; i<n_de_vertices; i++)
        cout << "nivel[" << i+1 << "] = " << nivel[i] << endl;
    cout << endl;

    cout << "BFS" << endl;
    grafo.bfs(1, pai, nivel);
    for(contador i = 0; i<n_de_vertices; i++)
        cout << "pai[" << i+1 << "] = " << pai[i] << endl;
    for(contador i = 0; i<n_de_vertices; i++)
        cout << "nivel[" << i+1 << "] = " << nivel[i] << endl;
    cout << endl;

    vertice u = 1, v = 10;
    cout << "Distancia entre " << u << " e " << v << ": " << grafo.calcula_distancia(u, v) << endl;
    
    cout << "Diametro do grafo: " << grafo.calcula_diametro() << endl;
    return EXIT_SUCCESS;
}