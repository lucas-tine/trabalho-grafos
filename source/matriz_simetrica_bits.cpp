#include "../headers/matriz_simetrica_bits.hpp"

matriz_simetrica_bits::matriz_simetrica_bits (contador tamanho):
tamanho(tamanho), numero_de_bits ( (tamanho * (tamanho+1))/2 ),
 bits(vetor_de_bits (this->numero_de_bits)) {}

matriz_simetrica_bits::matriz_simetrica_bits ():
tamanho(0), numero_de_bits (0),
 bits(vetor_de_bits ()) {}

matriz_simetrica_bits::~matriz_simetrica_bits ()
{
    this->bits.~vetor_de_bits();
}

matriz_simetrica_bits::_referencia_linha_matriz
matriz_simetrica_bits::operator[] (contador indice)
{
    return  _referencia_linha_matriz(indice, this->tamanho, this->bits);
}

matriz_simetrica_bits::_referencia_linha_matriz::
_referencia_linha_matriz (contador indice, contador tamanho, vetor_de_bits& bits):
indice(indice), tamanho(tamanho), bits(bits) {}

vetor_de_bits::referencia_bit 
matriz_simetrica_bits::_referencia_linha_matriz::operator[] (contador coluna)
{
    // como a matriz é simetrica, o vetor "bits" só guarda acima da diagonal principal da matriz
    contador indice_coluna = coluna, indice_linha = this->indice;

    if (indice_linha > indice_coluna ) // caso positivo, swap
    {
        contador coluna_reserva = indice_coluna;
        indice_coluna = indice_linha;
        indice_linha = coluna_reserva;
    }
    contador posicao_no_vetor = ( (indice_coluna)*(indice_coluna+1) )/2 ;
    posicao_no_vetor += indice_linha;
    return bits[posicao_no_vetor];
}

ostream& 
operator<< (ostream& os, matriz_simetrica_bits matriz)
{
    for (contador i = 0; i < matriz.obter_tamanho(); i++)
    {
        for (contador j = 0; j < matriz.obter_tamanho(); j++)
            {
                cout << matriz[i][j]<< " ";
            }
        cout << endl;
    }
    return os;
}