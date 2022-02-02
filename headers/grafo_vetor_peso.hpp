#include <vector>
#include <iostream>
#include "grafo.hpp"
#ifndef GRAFO_VETOR_PESO_HPP
#define GRAFO_VETOR_PESO_HPP

typedef struct Tupla_peso {
    vertice vertice_conectado;
    double peso;
} Tupla_peso;

using namespace std;

class grafo_vetor_peso: public grafo 
{
    private:
        vector<Tupla_peso> *vetor_de_adjacencia;

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
};

#endif