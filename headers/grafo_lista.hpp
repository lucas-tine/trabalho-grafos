#include <forward_list>
#include <iostream>
#include "grafo.hpp"
#ifndef GRAFO_LISTA_HPP
#define GRAFO_LISTA_HPP

using namespace std;

class grafo_lista: public grafo 
{
    private:
        forward_list<unsigned long> *lista_de_adjacencia ;
        static bool contido (unsigned long, forward_list<unsigned long>);

    public:
        grafo_lista (string nome_do_arquivo);
        grafo_lista (ifstream& arquivo);
        bool adjacentes (unsigned long, unsigned long) override;
        forward_list<unsigned long> operator[] (unsigned long);
};

#endif