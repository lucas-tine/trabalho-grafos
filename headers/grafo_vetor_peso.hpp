#include <vector>
#include <iostream>
#include "grafo.hpp"
#ifndef GRAFO_VETOR_PESO_HPP
#define GRAFO_VETOR_PESO_HPP

struct Tupla_peso {
    vertice vertice_conectado;
    double peso;
};

struct retorno_mst {
    bool eh_arvore;
    float custo_da_arvore;//Custo total da árvore
    vector<vertice> pais_na_arvore;
};

struct retorno_dijkstra {
    vector<float> custo_do_vertice;//Distancia até o vértice
    vector<vertice> pai_do_vertice_no_caminho;
};

struct retorno_bellman_ford {
    vector<float> custo_do_vertice;//Distancia até o vértice
    vector<vertice> pai_do_vertice_no_caminho;
    bool ciclos_negativos;
};

using namespace std;

class grafo_vetor_peso: public grafo 
{
    private:
        vector<Tupla_peso> *vetor_de_adjacencia;
        bool tem_peso_negativo;
        bool direcionado;

    public:
        grafo_vetor_peso (string nome_do_arquivo, bool);
        grafo_vetor_peso (ifstream& arquivo, bool);
        vector<Tupla_peso> operator[] (vertice);  
        void dfs (vertice, vertice*, vertice*);
        void bfs (vertice, vertice*, vertice*);
        void componentes_conexas();
        void informacoes();
        retorno_mst MST ();
        void escrever_MST (string nome_do_arquivo);
        retorno_dijkstra dijkstra(vertice);
        retorno_bellman_ford bellman_ford (vertice t);
        float distancia_alvo(vertice, vertice);
        vector<float> distancia_geral(vertice);
        vector<vertice> caminho_alvo(vertice, vertice);
        vector<vector<vertice>> caminho_geral(vertice);
};

#endif