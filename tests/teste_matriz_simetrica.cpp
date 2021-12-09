#include <iostream>
#include "../headers/matriz_simetrica_bits.hpp"

using namespace std;

int
main (void)
{
    matriz_simetrica_bits& matriz = *new matriz_simetrica_bits(3);
    matriz.reset();
    matriz [0][0] = 1;
    matriz [0][1] = 0;
    matriz [0][2] = 1;
    matriz [1][1] = matriz[2][2] = 1;

    cout << "uma matriz simetrica de formato tabuleiro-de-xadrez:" << endl <<matriz << endl;

    matriz.set();
    matriz[2][0] = matriz[0][0] = matriz[2][2] = 0;
    cout << "matriz de cantos '0'" << endl << matriz << endl;
}