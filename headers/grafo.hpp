#include <cmath>
#include <stdexcept>
#ifndef GRAFO_HPP
#define GRAFO_HPP

using namespace std;

typedef unsigned long long vertice;
typedef unsigned long long contador; // usado para contar vertices e arestas

class grafo
{
    protected:
        contador numero_de_vertices = 0;
        contador numero_de_arestas = 0;
        contador *graus;

    public: 
        contador obter_numero_de_vertices () const {return numero_de_vertices;};
        contador obter_numero_de_arestas () const {return numero_de_arestas;};
        virtual bool adjacentes (vertice, vertice) {return false;};
        contador menor_grau () const {return (numero_de_vertices == 0) ? 0 : graus[0] ;};
        contador maior_grau () const {return (numero_de_vertices == 0) ? 0 : graus[numero_de_vertices-1] ;};
        contador grau_mediano () const {return (numero_de_vertices == 0) ? 0 : graus[numero_de_vertices/2] ;};
        double grau_medio () const
        {
            if (numero_de_vertices == 0) return 0.0;

            double soma = 0;
            for (contador i = 0; i < numero_de_vertices; i++)
                soma += graus[i];
            
            return soma/numero_de_vertices ;
        }
        void assegurar_bitagem_matriz ()
        {
            bool estouro = log2(numero_de_vertices*(numero_de_vertices+1)) >= pow (2.0, sizeof(contador)*8);
            estouro = estouro || (numero_de_vertices*(numero_de_vertices+1) < numero_de_vertices);
            if ( estouro )
                throw overflow_error ("tamanho do grafo eh " + to_string(numero_de_vertices) +
                string (" mas \"unsigned long\" usa ") +
                to_string (sizeof(contador)) +
                string(" bits"));
        }
};

#endif