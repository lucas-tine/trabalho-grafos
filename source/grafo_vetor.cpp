#include "../headers/grafo_vetor.hpp"
#include <fstream>

grafo_vetor::grafo_vetor (string nome_do_arquivo)
{
    ifstream arquivo (nome_do_arquivo, ios::in);
    *this = grafo_vetor(arquivo);
    arquivo.close();
}

grafo_vetor::grafo_vetor (ifstream& arquivo)
{
    arquivo.seekg(0, arquivo.beg);
    arquivo >> this->numero_de_vertices;
    this->vetor_de_adjacencia = new set<unsigned long> [numero_de_vertices];

    if (this->vetor_de_adjacencia == nullptr) 
        throw bad_alloc ();

    unsigned long vertice1, vertice2;
    while (arquivo >> vertice1 >> vertice2)
    {
        vertice1--;
        vertice2--;
        
        if (not adjacentes(vertice1, vertice2))
        {
            vetor_de_adjacencia[vertice1].insert(vertice2);
            if (vertice1 != vertice2)
                vetor_de_adjacencia[vertice2].insert(vertice1);
        }

        this->numero_de_arestas++;
    }
}

bool 
grafo_vetor::adjacentes (unsigned long vertice1, unsigned long vertice2)
{
    bool grau_do_vertice1_maior = 
            vetor_de_adjacencia[vertice1].size() > vetor_de_adjacencia[vertice2].size();

    if (not grau_do_vertice1_maior )
        return
        ( vetor_de_adjacencia[vertice1].find (vertice2) != vetor_de_adjacencia[vertice1].end());
    else 
        return 
        ( vetor_de_adjacencia[vertice2].find (vertice1) != vetor_de_adjacencia[vertice2].end());
}

set<unsigned long> 
grafo_vetor::operator[] (unsigned long vertice)
{
    return this->vetor_de_adjacencia [vertice];
}  