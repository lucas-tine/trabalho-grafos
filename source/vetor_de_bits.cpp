#include "../headers/vetor_de_bits.hpp"
#include <stdexcept>

using namespace std; 

vetor_de_bits::vetor_de_bits (contador tamanho): tamanho (tamanho)
{
    cout << "Vetor criado: " << tamanho << " bits." << endl;
    numero_de_bytes = tamanho/8 ;
    bool tamanho_divisivel_por_oito = ( (7 + tamanho)/8 == numero_de_bytes);

    if (not tamanho_divisivel_por_oito) numero_de_bytes++;
    
    this->bits = new byte [numero_de_bytes];

    if (bits == nullptr) 
        throw "alocacao de memoria mal-sucedida";
}

vetor_de_bits::vetor_de_bits ()
{
    this->tamanho = 0;
    this->bits = nullptr;
}

vetor_de_bits::~vetor_de_bits () 
{ 
    if (bits != nullptr) 
    {
        //delete bits;  (erro estranho quando delete é usado)
        bits = nullptr;
    } 
}

vetor_de_bits::referencia_bit
vetor_de_bits::operator[] (contador indice) 
{
    if (indice < this->tamanho) 
        return referencia_bit (indice, this->bits );
    else 
        throw out_of_range("posicao do bit excede o tamanho do vetor de bits: " + to_string(indice) 
        + " em um vetor de: " + to_string(this->tamanho_em_bits()));
};

void 
vetor_de_bits::reset()
{
    for (contador i = 0; i < numero_de_bytes; i++)
        bits[i] = 0b00000000;
}

void 
vetor_de_bits::set()
{
    for (contador i = 0; i < numero_de_bytes; i++)
        bits[i] = 0b11111111;
}


vetor_de_bits::referencia_bit::referencia_bit (contador indice, byte* bits_pai):
indice_byte (indice/8), indice_bit(indice%8), bits_pai(bits_pai){}

vetor_de_bits::referencia_bit& 
vetor_de_bits::referencia_bit::operator=(bool value)
{
    byte* byte_ = &( bits_pai[indice_byte] );
    if (value)
        *byte_ = (*byte_) | ( 0b0001 << indice_bit);
    else
        *byte_ = (*byte_) & ( ~ ( 0b0001 << indice_bit)  );

    return *this;
}

vetor_de_bits::referencia_bit::operator bool() const
{
    byte byte_ =  bits_pai[indice_byte];
    return ( byte_ & ( 0b0001 << (indice_bit)));
}

bool 
vetor_de_bits::referencia_bit::operator~() const
{
    bool value = (*this);
    return !value;
}

vetor_de_bits::referencia_bit& 
vetor_de_bits::referencia_bit::flip()
{
    bool value = (*this);

    if (value)
        *this = false;
    else
        *this = true;

    return *this;
}

vetor_de_bits::referencia_bit& 
vetor_de_bits::referencia_bit::operator=(const referencia_bit& rhs)
{
    bool value = rhs;
    *this = value;
    return *this;
}

vetor_de_bits::referencia_bit& 
vetor_de_bits::referencia_bit::operator|=(bool value)
{
    bool my_value = *this;
    my_value = my_value | value;
    *this = my_value;
    return *this;
}

vetor_de_bits::referencia_bit& 
vetor_de_bits::referencia_bit::operator&=(bool value)
{
    bool my_value = *this;
    my_value = my_value & value;
    *this = my_value;
    return *this;
}

vetor_de_bits::referencia_bit& 
vetor_de_bits::referencia_bit::operator^=(bool value)
{
    bool my_value = *this;
    my_value = my_value ^ value;
    *this = my_value;
    return *this;
}

ostream&
operator<< (ostream& os, vetor_de_bits vetor)
{
    for (contador i = 0; i < vetor.tamanho_em_bits() ; i++)
        os << vetor[i] ;
    return os;
}