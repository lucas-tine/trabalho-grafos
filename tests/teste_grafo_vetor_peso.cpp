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
    //cout << "* [enter] para seguir";
    //cin.get();
    
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

    /*vertice x;
    cout << "Escolha o vertice de inicio do dijkstra:";;
    cin >> x;
    vector<double> v_dijkstra = grafo.dijkstra(x);
    cout << "Resultado do Dijsktra no vertice " << x << endl;
    int i = 0;
    for(auto it: v_dijkstra){
        cout << "dist[" << i+1 << "] = " << it << endl;
        i++;
    }
    */

    vertice x, y;
    cout << "Entre com dois vertices: ";
    cin >> x >> y; 
    cout << "Fazendo Distancia entre " << x << " e " << y << ": " << grafo.distancia_alvo(x,y) << endl;
    cout << "Distancia entre " << x << " e todos os vertices:" << endl;
    int i = 0;
    for(auto it: grafo.distancia_geral(x)){
        cout << "dist[" << i+1 << "] = " << it << endl;
        i++;
    }
    cout << "Caminho entre " << x << " e " << y << ":" << endl;
    for(auto it: grafo.caminho_alvo(x,y)){
        cout << it << ", ";
    }
    cout << endl;
    cout << "Caminho entre " << x << " e todos os vertices:" << endl;
    i=0;
    for(auto it: grafo.caminho_geral(x)){
        cout << "caminho ate "<< i+1 << ": ";
        for(auto it2: it){
            cout << it2 << ", ";
        }
        cout << endl;
        i++;
    }
}