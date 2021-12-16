#include "../headers/grafo_vetor.hpp"
#include <fstream>
#include <stack>

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
    this->vetor_de_adjacencia = new set<vertice> [numero_de_vertices];

    if (this->vetor_de_adjacencia == nullptr) 
        throw bad_alloc ();

    vertice vertice1, vertice2;
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
grafo_vetor::adjacentes (vertice vertice1, vertice vertice2)
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

set<vertice> 
grafo_vetor::operator[] (vertice vertice)
{
    return this->vetor_de_adjacencia [vertice];
}

void
grafo_vetor::dfs (unsigned long vertice){
    vertice --;
    bool visitado[numero_de_vertices];
    unsigned long pai[numero_de_vertices], nivel[numero_de_vertices];
    for (unsigned long i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0; //Tá errado! Mudar
    }
    stack<unsigned long> pilha;
    pilha.push(vertice);
    nivel[vertice] = 0;
    while(!pilha.empty()){
        unsigned long v = pilha.top();
        pilha.pop();
        if(!visitado[v]){
            visitado[v] = true;
            for (auto it = vetor_de_adjacencia[v].begin(); it != vetor_de_adjacencia[v].end(); it++){
                pilha.push(*it);
                if(!visitado[*it]){
                    pai[*it] = v+1;
                    nivel[*it] = nivel[v] + 1;
                }
            }
        }
    }
    for(unsigned long i =0; i<6; i++)
        cout << "pai[" << i+1 << "] = " << pai[i] << endl;
    for(unsigned long i =0; i<6; i++)
        cout << "nivel[" << i+1 << "] = " << nivel[i] << endl;
    cout << endl;
}