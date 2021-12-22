#include "../headers/grafo_vetor.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    string nome_arquivo = "grafo_1.txt";
    grafo_vetor grafo(nome_arquivo);
    system("pause");
    return 0;

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

    cout << "DFS - Feita no txt" << endl;
    grafo.dfs(3, pai, nivel);

    cout << "BFS - Feita no txt" << endl;
    grafo.bfs(1, pai, nivel);

    vertice u = 1, v = 8;
    cout << "Distancia entre " << u << " e " << v << ": " << grafo.calcula_distancia(u, v) << endl;

    cout << "Diametro do grafo: " << grafo.calcula_diametro() << endl;

    cout << "Componentes conexas - Feita no txt " << endl; 
    grafo.componentes_conexas();

    grafo.informacoes();
    return EXIT_SUCCESS;
}