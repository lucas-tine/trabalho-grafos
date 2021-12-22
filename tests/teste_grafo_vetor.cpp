#include "../headers/grafo_vetor.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    string nome_arquivo = "receita de grafo3.txt";
    grafo_vetor grafo(nome_arquivo);

    cout << "vetor de adjacencia criado a partir de \"" << nome_arquivo << "\" :" << endl ;

    contador n_de_vertices = grafo.obter_numero_de_vertices();

    for (unsigned i = 0; i < n_de_vertices; i++){
        cout << "[" << i+1 << "] -> ";
        for (auto vertice_ : grafo[i]){
            cout << vertice_+1 << ", ";
        }
        cout << endl;
    }  

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

    vertice u = 1, v = 8;
    cout << "Distancia entre " << u << " e " << v << ": " << grafo.calcula_distancia(u, v) << endl;

    cout << "Diametro do grafo: " << grafo.calcula_diametro() << endl;

    grafo.componentes_conexas();
    return EXIT_SUCCESS;
}