#ifndef GRAFO_HPP
#define GRAFO_HPP

typedef unsigned long vertice;
typedef unsigned long contador; // usado para contar vertices e arestas

class grafo
{
    protected:
        contador numero_de_vertices = 0;
        contador numero_de_arestas = 0;

    public: 
        contador obter_numero_de_vertices () const {return numero_de_vertices;};
        contador obter_numero_de_arestas () const {return numero_de_arestas;};
        virtual bool adjacentes (vertice, vertice) {return false;};

};

#endif