#include <iostream>
#include "../headers/matriz_simetrica_bits.hpp"

using namespace std;

void 
print_matriz(matriz_simetrica_bits matriz)
{
    for (unsigned i = 0; i < matriz.get_tamanho(); i++)
    {
        for (unsigned j = 0; j < matriz.get_tamanho(); j++)
            {
                cout << matriz[i][j]<< " ";
            }
        cout << endl;
    }
};

int
main (void)
{
    matriz_simetrica_bits& matriz = *new matriz_simetrica_bits(3);
    matriz.reset();
    matriz [0][0] = 1;
    matriz [0][1] = 0;
    matriz [0][2] = 1;
    matriz [1][1] = matriz[2][2] = 1;

    cout << "uma matriz simetrica de formato tabuleiro-de-xadrez:" << endl;
    print_matriz(matriz);

    matriz.set();
    matriz[2][0] = matriz[0][0] = matriz[2][2] = 0;
    cout << "matriz de cantos '0'" << endl;
    print_matriz(matriz);
}