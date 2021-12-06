#include <iostream>
#include "../headers/vetor_de_bits.hpp"

using namespace std;

int
main (void)
{
    vetor_de_bits bits (15);
    
    cout << "quantidade de bytes no vetor: " << bits.tamanho_em_bytes() << endl ;
    cout << "quantidade de bits no vetor: " << bits.tamanho_em_bits() << endl << endl;

    cout << "bits setados:" << endl;
    bits.set();
    for (int i = 0; i < 15; i++)
        cout << bits[i] ;
    cout << endl;
    
    
    cout << "bits resetados:" << endl;
    bits.reset();
    for (int i = 0; i < 15; i++)
        cout << bits[i] ;
    cout << endl;

    cout << "bits alternados:" << endl;
    for (int i = 0; i < 15; i++)
        bits[i] = (i%2);
    for (int i = 0; i < 15; i++)
        cout << bits[i] ;
    cout << endl;
    
    return 0;
}