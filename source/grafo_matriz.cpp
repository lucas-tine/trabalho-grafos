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

    vertice vertice1, vertice2;
    while (arquivo >> vertice1 >> vertice2)
    {
        matriz_de_adjacencia[vertice1-1][vertice2-1] = 1;
        this->numero_de_arestas++;
    }
}

bool
grafo_matriz::adjacentes (vertice vertice1, vertice vertice2)
{
    return (*this)[vertice1][vertice2];
}

ostream& 
operator<< (ostream& os, grafo_matriz grafo)
{
    return (os << grafo.matriz_de_adjacencia);
}

matriz_simetrica_bits::_referencia_linha_matriz 
grafo_matriz::operator[] (vertice vertice)
{
    return this->matriz_de_adjacencia[vertice];
}