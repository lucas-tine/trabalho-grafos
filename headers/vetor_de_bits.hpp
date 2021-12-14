#include "grafo.hpp"
#include <iostream>
#ifndef VETOR_DE_BITS_HPP
#define VETOR_DE_BITS_HPP

typedef char byte;
class vetor_de_bits
{
    private:
        contador tamanho;
        contador numero_de_bytes;
        byte* bits;

    public:
        vetor_de_bits ();
        vetor_de_bits (contador tamanho);
        ~vetor_de_bits ();
        contador tamanho_em_bytes() {return numero_de_bytes;};
        contador tamanho_em_bits() {return tamanho;}

        class referencia_bit
        {
            contador indice_byte; 
            unsigned char indice_bit;

            byte* bits_pai;
            public:
                // An automatically generated copy constructor.
                referencia_bit (contador indice, byte* bits);
                referencia_bit& operator=(bool value);
                referencia_bit& operator=(const referencia_bit& rhs);
                referencia_bit& operator|=(bool value);
                referencia_bit& operator&=(bool value);
                referencia_bit& operator^=(bool value);

                bool operator~() const;
                operator bool() const;
                referencia_bit& flip();
        };
        referencia_bit operator[] (contador indice);
        void reset();
        void set();
        friend std::ostream& operator<< (std::ostream&, vetor_de_bits);
};

#endif