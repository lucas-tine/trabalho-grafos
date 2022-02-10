#include <vector>
#include <iostream>
#include "grafo.hpp"
#ifndef GRAFO_VETOR_PESO_HPP
#define GRAFO_VETOR_PESO_HPP

struct Tupla_peso {
    vertice vertice_conectado;
    double peso;
};

struct retorno_mst { // utilizada no calculo de MSTs
    bool eh_arvore;
    float custo_da_arvore;
    vector<vertice> pais_na_arvore;
};

using namespace std;

class grafo_vetor_peso: public grafo 
{
    private:
        vector<Tupla_peso> *vetor_de_adjacencia;
        bool tem_peso_negativo;

    public:
        grafo_vetor_peso (string nome_do_arquivo);
        grafo_vetor_peso (ifstream& arquivo);
        bool adjacentes (vertice, vertice) override;
        vector<Tupla_peso> operator[] (vertice);  
        void dfs (vertice, vertice*, vertice*);
        void bfs (vertice, vertice*, vertice*);
        unsigned int calcula_distancia(vertice, vertice);
        unsigned int calcula_diametro();
        void componentes_conexas();
        void informacoes();
        vertice estima_diametro();
        retorno_mst MST (); // calcula uma MST do grafo à partir do algoritmo de prim
        void escrever_MST (string nome_do_arquivo);
        pair < vector<double>, vector<vertice> > dijkstra(vertice);
        double distancia_alvo(vertice, vertice);
        vector<double> distancia_geral(vertice);
        vector<vertice> caminho_alvo(vertice, vertice);
        vector<vector<vertice>> caminho_geral(vertice);
};

#endif