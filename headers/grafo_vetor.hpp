#include "grafo.hpp"
#include <vector>
#include <iostream>

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
        vector<vertice> operator[] (vertice);  
        void dfs (vertice, vertice*, vertice*);
        void bfs (vertice, vertice*, vertice*);
        unsigned int distancia_alvo(vertice, vertice);
        unsigned int calcula_diametro();
        void componentes_conexas();
        void informacoes();
        vertice estima_diametro();
};

#endif