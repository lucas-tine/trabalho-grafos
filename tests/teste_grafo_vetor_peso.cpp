#include "../headers/grafo_vetor_peso.hpp"
#include <iostream>

using namespace std;

int
main ()
{
    string nome_arquivo;
    cout << "caminho do arquivo de texto do grafo:" << endl;  
    getline (cin, nome_arquivo);
    grafo_vetor_peso grafo(nome_arquivo);
    cout << "* [enter] para seguir";
    cin.get();
    
    cout << "obtendo numero de vertices ..." << endl;
    contador n_de_vertices = grafo.obter_numero_de_vertices();
    cout << n_de_vertices << endl;

    cout << "vetor de adjacencia criado a partir de \"" << nome_arquivo << "\" :" << endl;
    for (unsigned i = 0; i < n_de_vertices; i++){
        cout << "[" << i+1 << "] -> ";
        for(auto t : grafo[i]){
            cout << "{" << t.vertice_conectado+1 << ", " << t.peso << "}, ";
        }
        cout << endl;
    }

    vertice *pai, *nivel;
    pai = new vertice [n_de_vertices];
    nivel = new vertice [n_de_vertices];

    cout << "Fazendo DFS..." << endl;
    grafo.dfs(1, pai, nivel);

    cout << "Fazendo BFS..." << endl;
    grafo.bfs(1, pai, nivel);

    //vertice x = 1, y = 5;
    //cout << "Fazendo Distancia entre " << x << " e " << y << ": " << grafo.calcula_distancia(x,y) << endl;

    //cout << "Calculando diametro: " << grafo.calcula_diametro();

    cout << "Checando componentes conexas..." << endl;
    grafo.componentes_conexas();

    cout << "Escrevendo informacoes do grafo..." << endl;
    grafo.informacoes();

}