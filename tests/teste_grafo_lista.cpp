#include "../headers/grafo_lista.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    grafo_lista grafo("receita de grafo.txt");

    cout << "lista de adjacencia criada a partir de \"receita de grafo.txt\" :" << endl;

    for (unsigned i = 0; i < grafo.obter_numero_de_vertices(); i++){
        cout << "[" << i+1 << "] -> ";
        for (auto vertice : grafo[i]){
            cout << vertice+1 << ", ";
        }
        cout << endl;
    }

    cout << "DFS" << endl;
    grafo.dfs(1);

    cout << "BFS" << endl;
    grafo.bfs(1);

    return EXIT_SUCCESS;
}