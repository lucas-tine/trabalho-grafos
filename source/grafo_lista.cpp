#include "../headers/grafo_lista.hpp"
#include <fstream>
#include <stdexcept>
#include <stack>

grafo_lista::grafo_lista (string nome_do_arquivo)
{
    ifstream arquivo (nome_do_arquivo, ios::in);
    *this = grafo_lista(arquivo);
    arquivo.close();
}

grafo_lista::grafo_lista (ifstream& arquivo)
{
    arquivo.seekg(0, arquivo.beg);
    arquivo >> this->numero_de_vertices;
    lista_de_adjacencia = new forward_list<unsigned long> [numero_de_vertices];
    if (lista_de_adjacencia == nullptr) throw bad_alloc ();

    unsigned vertice1, vertice2;
    while (arquivo >> vertice1 >> vertice2)
    {
        vertice1--;
        vertice2--;
       
        if (not adjacentes (vertice1,vertice2))
        {
            lista_de_adjacencia[vertice1].push_front (vertice2);
            if (vertice1 != vertice2)
                lista_de_adjacencia[vertice2].push_front (vertice1);
        }

        this->numero_de_arestas++;
    }
}

bool 
grafo_lista::adjacentes (unsigned long vertice1, unsigned long vertice2)
{
    bool grau_do_vertice1_maior = 
            lista_de_adjacencia[vertice1].max_size() > lista_de_adjacencia[vertice2].max_size();
        
    if ( not grau_do_vertice1_maior )
            return contido (vertice2, lista_de_adjacencia[vertice1]);
    else 
            return contido (vertice1, lista_de_adjacencia[vertice2]);
       
}

forward_list<unsigned long> 
grafo_lista::operator[] (unsigned long vertice)
{
    return this->lista_de_adjacencia[vertice];
}

bool
grafo_lista::contido (unsigned long elemento, forward_list<unsigned long> lista)
{
    for (auto it = lista.begin(); it != lista.end() ; it++)
        if (*it == elemento)
            return true;
    return false;
}

void
grafo_lista::dfs (unsigned long vertice){
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
            for (auto it = lista_de_adjacencia[v].begin(); it != lista_de_adjacencia[v].end(); it++){
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