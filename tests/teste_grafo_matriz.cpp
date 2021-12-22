#include "../headers/grafo_matriz.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    string nome_arquivo;
    cout << "caminho do arquivo de texto do grafo:" << endl;  
    getline (cin, nome_arquivo);
    grafo_matriz grafo(nome_arquivo);
    cout << "matriz de adjacencia criada a partir de \"receita de grafo.txt\" :" << endl << 
    // grafo << 
    "* [enter] para seguir" ;
    cin.get();
    
    contador n_de_vertices = grafo.obter_numero_de_vertices();

    vertice pai[n_de_vertices], nivel[n_de_vertices];

    cout << "DFS - Feita no txt" << endl;
    grafo.dfs(1, pai, nivel);

    cout << "BFS - Feita no txt" << endl;
    grafo.bfs(1, pai, nivel);

    vertice u = 1, v = 10;
    cout << "Distancia entre " << u << " e " << v << ": " << grafo.calcula_distancia(u, v) << endl;
    
    cout << "Diametro do grafo: " << grafo.calcula_diametro() << endl;

    cout << "Componentes conexas - Feita no txt" << endl; 
    grafo.componentes_conexas();

    grafo.informacoes();
    return EXIT_SUCCESS;
}