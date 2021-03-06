#include "../headers/grafo_matriz.hpp"
#include <iostream>
#include <chrono>

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

    vertice* pai = new vertice [n_de_vertices];
    vertice* nivel = new vertice [n_de_vertices];
    
    auto limite = min ((contador) grafo.obter_numero_de_vertices(),(contador) 30);
    auto comeco = chrono::steady_clock::now();

    for(vertice j = 1; j < limite; j++){
        grafo.bfs(j, pai, nivel);
        cout << j << endl;
    }
    

    auto fim = chrono::steady_clock::now();
    cout << "Tempo das 1000 bfs: "
        << chrono::duration_cast<chrono::milliseconds>(fim - comeco).count()
        << " ms" << endl;

    comeco = chrono::steady_clock::now();

    //for(vertice i = 1; i <= 10; i++){//Apenas para o grafo_1 e _2, por terem menos de 1000 vertices
        for(vertice j = 1; j < limite; j++){
            grafo.dfs(j, pai, nivel);
            cout << j << endl;
        }
    //}

    fim = chrono::steady_clock::now();
    cout << "Tempo das 1000 dfs: "
        << chrono::duration_cast<chrono::milliseconds>(fim - comeco).count()
        << " ms" << endl;

    for(vertice i = 1; i <= 3; i++){
        cout << "BFS comecando em: " << i << endl;
        grafo.bfs(i, pai, nivel);
        cout << "Pai[10] = " << pai[9] << endl;
        cout << "Pai[20] = " << pai[19] << endl;
        cout << "Pai[30] = " << pai[29] << endl;
    }

    for(vertice i = 1; i <= 3; i++){
        cout << "DFS comecando em: " << i << endl;
        grafo.dfs(i, pai, nivel);
        cout << "Pai[10] = " << pai[9] << endl;
        cout << "Pai[20] = " << pai[19] << endl;
        cout << "Pai[30] = " << pai[29] << endl;
    }

    cout << "Distancia entre (10, 20): " << grafo.distancia_alvo(10, 20) << endl;
    cout << "Distancia entre (10, 30): " << grafo.distancia_alvo(10, 30) << endl;
    cout << "Distancia entre (20, 30): " << grafo.distancia_alvo(20, 30) << endl;

    grafo.componentes_conexas();
    
    /*cout << "DFS - Feita no txt" << endl;
    grafo.dfs(1, pai, nivel);

    cout << "BFS - Feita no txt" << endl;
    grafo.bfs(1, pai, nivel);

    vertice u = 1, v = 10;
    cout << "Distancia entre " << u << " e " << v << ": " << grafo.calcula_distancia(u, v) << endl;
    
    cout << "Diametro do grafo: " << grafo.calcula_diametro() << endl;

    cout << "Componentes conexas - Feita no txt" << endl; 
    grafo.componentes_conexas();

    grafo.informacoes();*/
    return EXIT_SUCCESS;
}