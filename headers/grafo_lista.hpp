#include <forward_list>
#include <iostream>
#include "grafo.hpp"
#ifndef GRAFO_LISTA_HPP
#define GRAFO_LISTA_HPP

using namespace std;

class grafo_lista: public grafo 
{
    private:
        forward_list<vertice> *lista_de_adjacencia ;
        static bool contido (vertice, forward_list<vertice>);

    public:
        grafo_lista (string nome_do_arquivo);
        grafo_lista (ifstream& arquivo);
        bool adjacentes (vertice, vertice) override;
        forward_list<vertice> operator[] (vertice);
        void dfs(vertice);
};

#endif