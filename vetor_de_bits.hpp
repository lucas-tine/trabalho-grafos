#ifndef VETOR_DE_BITS_HPP
#define VETOR_DE_BITS_HPP

typedef char byte;
class vetor_de_bits
{
    private:
        unsigned long tamanho;
        byte* bits;

    public:
        vetor_de_bits (unsigned long tamanho);
        ~vetor_de_bits ();
        class referencia_bit
        {
            unsigned long indice_byte; 
            unsigned char indice_bit;

            byte* bits_pai;
            public:
                // An automatically generated copy constructor.
                referencia_bit (unsigned long indice, byte* bits);
                referencia_bit& operator=(bool value);
                referencia_bit& operator=(const referencia_bit& rhs);
                referencia_bit& operator|=(bool value);
                referencia_bit& operator&=(bool value);
                referencia_bit& operator^=(bool value);

                bool operator~() const;
                operator bool() const;
                referencia_bit& flip();
        };
        referencia_bit operator[] (unsigned long indice);
};

#endif