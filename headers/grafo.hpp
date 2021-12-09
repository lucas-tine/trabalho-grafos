#ifndef GRAFO_HPP
#define GRAFO_HPP

class grafo
{
    protected:
        unsigned numero_de_vertices = 0;
        unsigned numero_de_arestas = 0;

    public: 
        unsigned obter_numero_de_vertices () const {return numero_de_vertices;};
        unsigned obter_numero_de_arestas () const {return numero_de_arestas;};
        virtual bool adjacentes (unsigned long, unsigned long) {return false;};

};

#endif