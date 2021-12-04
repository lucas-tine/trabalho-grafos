#include <iostream>
#include "vetor_de_bits.hpp"

using namespace std;

int
main (void)
{
    vetor_de_bits bits (8);
    bits.reset();
    cout << "bits setados:" << endl;
    for (int i = 0; i < 8; i++)
        cout << bits[i] ;
    cout << endl;
    
    bits.set();
    cout << "bits resetados:" << endl;
    for (int i = 0; i < 8; i++)
        cout << bits[i] ;
    cout << endl;

    bits.reset();
    cout << "bits alternados:" << endl;
    for (int i = 0; i < 8; i++)
        bits[i] = (i%2);
    for (int i = 0; i < 8; i++)
        cout << bits[i] ;
    cout << endl;
    
    return 0;
}