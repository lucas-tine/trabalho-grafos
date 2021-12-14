#include <set>
#include <iostream>
#include "grafo.hpp"
#ifndef GRAFO_VETOR_HPP
#define GRAFO_VETOR_HPP

using namespace std;

class grafo_vetor: public grafo 
{
    // implementado com "set" ao inves de "array" ou "vector" para usar a inserção e busca binária 
    // e ordenação automatica, o que seria feito manualmente com classes mais simples
    private:
        set<vertice> *vetor_de_adjacencia;

    public:
        grafo_vetor (string nome_do_arquivo);
        grafo_vetor (ifstream& arquivo);
        bool adjacentes (vertice, vertice) override;
        set<vertice> operator[] (vertice);  
};

#endif