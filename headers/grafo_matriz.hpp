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
        void print_matriz_de_adjacencia ();
};

#endif