#include "../headers/grafo_lista.hpp"
#include <fstream>
#include <stdexcept>

grafo_lista::grafo_lista (string nome_do_arquivo)
{
    ifstream arquivo (nome_do_arquivo, ios::in);
    *this = grafo_lista(arquivo);
    arquivo.close();
}

grafo_lista::grafo_lista (ifstream& arquivo)
{
    arquivo.seekg(0, arquivo.beg);
    arquivo >> this->numero_de_vertices;
    lista_de_adjacencia = new forward_list<vertice> [numero_de_vertices];
    if (lista_de_adjacencia == nullptr) throw bad_alloc ();

    vertice vertice1, vertice2;
    while (arquivo >> vertice1 >> vertice2)
    {
        vertice1--;
        vertice2--;
       
        if (not adjacentes (vertice1,vertice2))
        {
            lista_de_adjacencia[vertice1].push_front (vertice2);
            if (vertice1 != vertice2)
                lista_de_adjacencia[vertice2].push_front (vertice1);
        }

        this->numero_de_arestas++;
    }
}

bool 
grafo_lista::adjacentes (vertice vertice1, vertice vertice2)
{
    bool grau_do_vertice1_maior = 
            lista_de_adjacencia[vertice1].max_size() > lista_de_adjacencia[vertice2].max_size();
        
    if ( not grau_do_vertice1_maior )
            return contido (vertice2, lista_de_adjacencia[vertice1]);
    else 
            return contido (vertice1, lista_de_adjacencia[vertice2]);
       
}

forward_list<vertice> 
grafo_lista::operator[] (vertice vertice)
{
    return this->lista_de_adjacencia[vertice];
}

bool
grafo_lista::contido (vertice elemento, forward_list<vertice> lista)
{
    for (auto it = lista.begin(); it != lista.end() ; it++)
        if (*it == elemento)
            return true;
    return false;
}