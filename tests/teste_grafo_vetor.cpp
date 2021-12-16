#include "../headers/grafo_vetor.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    grafo_vetor grafo("receita de grafo2.txt");

    cout << "vetor de adjacencia criado a partir de \"receita de grafo.txt\" :" << endl ;

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