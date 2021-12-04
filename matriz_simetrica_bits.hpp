#include "vetor_de_bits.hpp"
#ifndef MATRIZ_SIMETRICA_BITS_HPP
#define MATRIZ_SIMETRICA_BITS_HPP

using namespace std;

class _referencia_linha_matriz
{
    // representa uma linha da matriz simetrica, usado para fazer indexação 2D "[i][j]"
    unsigned indice,
        tamanho;
    
    public:
        vetor_de_bits::referencia_bit operator[] (unsigned coluna);
};

class matriz_simetrica_bits
{
    private:
        unsigned tamanho, // numero de linhas e de colunas da matriz quadrada
                 numero_de_bits;

        vetor_de_bits bits;

    public:
        matriz_simetrica_bits (unsigned tamanho);
        _referencia_linha_matriz operator[] (unsigned linha);
};

#endif