#include <iostream>
#include "../headers/grafo_vetor_peso.hpp"

using namespace std;

int
main ()
{
    const string arquivo_saida = "mst.txt" ,
    arquivo_grafo = "grafo_1.txt";
    grafo_vetor_peso grafo_de_teste (arquivo_grafo, false);
    grafo_de_teste.escrever_MST(arquivo_saida);
    retorno_mst arvore = grafo_de_teste.MST();

    cout << (arvore.eh_arvore ? "tudo certo, " : "nao ") << "existe uma MST para este grafo" << 
    (arvore.eh_arvore ? " de custo " + to_string(arvore.custo_da_arvore) : "") << endl;
    
    for (vertice i = 0; i < arvore.pais_na_arvore.size(); i++)
        cout << "pai[" << i+1 << "] = " << arvore.pais_na_arvore[i] + 1 << 
        (arvore.pais_na_arvore[i] == grafo_de_teste.obter_numero_de_vertices() ? " (x)" : "" ) << endl;
    
    return EXIT_SUCCESS;
}