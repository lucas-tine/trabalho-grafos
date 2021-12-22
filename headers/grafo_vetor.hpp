#include <vector>
#include <iostream>
#include "grafo.hpp"
#ifndef GRAFO_VETOR_HPP
#define GRAFO_VETOR_HPP

using namespace std;

class grafo_vetor: public grafo 
{
    private:
        vector<vertice> *vetor_de_adjacencia;

    public:
        grafo_vetor (string nome_do_arquivo);
        grafo_vetor (ifstream& arquivo);
        bool adjacentes (vertice, vertice) override;
        vector<vertice> operator[] (vertice);  
        void dfs (vertice, vertice*, vertice*);
        void bfs (vertice, vertice*, vertice*);
        unsigned int calcula_distancia(vertice, vertice);
        unsigned int calcula_diametro();
        void componentes_conexas();
};

#endif