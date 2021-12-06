#include "../headers/grafo_matriz.hpp"

grafo_matriz::grafo_matriz (string nome_do_arquivo)
{
    ifstream arquivo (nome_do_arquivo, ios::in);
    *this = grafo_matriz (arquivo);
    arquivo.close();
}

grafo_matriz::grafo_matriz (ifstream& arquivo)
{
    arquivo.seekg(0, arquivo.beg);
    arquivo >> this->numero_de_vertices;
    matriz_de_adjacencia = matriz_simetrica_bits(numero_de_vertices);
    matriz_de_adjacencia.reset();

    unsigned vertice1, vertice2;
    while (arquivo >> vertice1 >> vertice2)
    {
        matriz_de_adjacencia[vertice1-1][vertice2-1] = 1;
        this->numero_de_arestas++;
    }
}

void
grafo_matriz::print_matriz_de_adjacencia ()
{
    for (unsigned i = 0; i < matriz_de_adjacencia.get_tamanho(); i++)
    {
        for (unsigned j = 0; j < matriz_de_adjacencia.get_tamanho(); j++)
                cout << matriz_de_adjacencia[i][j];
        cout << endl;
    }
}