#include "vetor_de_bits.hpp"
#ifndef MATRIZ_SIMETRICA_BITS_HPP
#define MATRIZ_SIMETRICA_BITS_HPP

using namespace std;

class matriz_simetrica_bits
{
    private:
        unsigned tamanho, // numero de linhas e de colunas da matriz quadrada
                 numero_de_bits;

        vetor_de_bits bits;

    public:
        matriz_simetrica_bits ();
        matriz_simetrica_bits (unsigned);
        ~matriz_simetrica_bits ();
        void reset() { return bits.reset();}
        void set ()  { return bits.set();}
        unsigned obter_tamanho (){ return tamanho;}

        class _referencia_linha_matriz
        {
            // representa uma linha da matriz simetrica, usado para fazer indexação 2D "[i] [j]"
            unsigned indice,
                tamanho;
            
            vetor_de_bits& bits;
            
            public:
                _referencia_linha_matriz (unsigned indice, unsigned tamanho, vetor_de_bits& bits);
                vetor_de_bits::referencia_bit operator[] (unsigned coluna);
        };

        _referencia_linha_matriz operator[] (unsigned);
        friend ostream& operator<< (ostream&, matriz_simetrica_bits);
};

#endif