#include "grafo.hpp"
#include "matriz_simetrica_bits.hpp"
#include <iostream>
#include <fstream>

#ifndef GRAFO_MATRIZ_HPP
#define GRAFO_MATRIZ_HPP

using namespace std;

class grafo_matriz: public grafo
{
    private:
        matriz_simetrica_bits matriz_de_adjacencia;

    public:
        grafo_matriz (string nome_do_arquivo);
        grafo_matriz (ifstream& arquivo);
        friend ostream& operator<< (ostream&, grafo_matriz);
        bool adjacentes (vertice, vertice ) override;
        matriz_simetrica_bits::_referencia_linha_matriz operator[] (vertice);
        void dfs (vertice, vertice*, vertice*);
        void bfs (vertice, vertice*, vertice*);
        unsigned int calcula_distancia(vertice, vertice);
        unsigned int calcula_diametro();
        void componentes_conexas();
        void informacoes();
        vertice estima_diametro();
};

#endif