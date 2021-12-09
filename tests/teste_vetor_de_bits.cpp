#include <iostream>
#include "../headers/vetor_de_bits.hpp"

using namespace std;

int
main (int argc, char** argv)
{
    unsigned quantidade_de_bits = (argc > 1) ? atoi( argv[1] ) : 8;
    vetor_de_bits bits (quantidade_de_bits);
    
    cout << "quantidade de bits no vetor: " << bits.tamanho_em_bits() << endl;
    cout << "quantidade de bytes no vetor: " << bits.tamanho_em_bytes() << endl << endl ;

    cout << "bits setados:" << endl;
    bits.set();
    cout << bits << endl;
    
    
    cout << "bits resetados:" << endl;
    bits.reset();
    cout << bits << endl;

    cout << "bits alternados:" << endl;
    for (unsigned i = 0; i < quantidade_de_bits; i++)
        bits[i] = (i%2);
        
    cout << bits << endl << endl;
    
    return EXIT_SUCCESS;
}