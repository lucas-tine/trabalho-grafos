#include "grafo.hpp"
#include "vetor_de_bits.hpp"
#ifndef MATRIZ_SIMETRICA_BITS_HPP
#define MATRIZ_SIMETRICA_BITS_HPP

using namespace std;

class matriz_simetrica_bits
{
    private:
        contador tamanho, // numero de linhas e de colunas da matriz quadrada
                 numero_de_bits;

        vetor_de_bits bits;

    public:
        matriz_simetrica_bits ();
        matriz_simetrica_bits (contador);
        ~matriz_simetrica_bits ();
        void reset() { return bits.reset();}
        void set ()  { return bits.set();}
        contador obter_tamanho (){ return tamanho;}

        class _referencia_linha_matriz
        {
            // representa uma linha da matriz simetrica, usado para fazer indexação 2D "[i] [j]"
            contador indice,
                tamanho;
            
            vetor_de_bits& bits;
            
            public:
                _referencia_linha_matriz (contador indice, contador tamanho, vetor_de_bits& bits);
                vetor_de_bits::referencia_bit operator[] (contador coluna);
        };

        _referencia_linha_matriz operator[] (contador);
        friend ostream& operator<< (ostream&, matriz_simetrica_bits);
};

#endif