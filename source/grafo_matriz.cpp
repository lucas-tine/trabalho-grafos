#include "../headers/grafo_matriz.hpp"
#include <stack>

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

void 
grafo_matriz::dfs (unsigned long vertice_){
    vertice_--;
    vetor_de_bits visitado (numero_de_vertices);
    vertice pai[numero_de_vertices];
    vertice nivel[numero_de_vertices];

    for (contador i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0; //Tá errado! Mudar
    }

    stack<vertice> pilha;
    pilha.push(vertice_);
    nivel[vertice_] = 0;
    while(!pilha.empty()){
        vertice v = pilha.top();
        pilha.pop();
        if(not visitado[v]){
            visitado[v] = true;
            for (vertice i = 0; i < numero_de_vertices; i++){
                if(matriz_de_adjacencia[v][i] == 1){
                    pilha.push(i);
                    if(not visitado[i]){
                        pai[i] = v+1;
                        nivel[i] = nivel[v] + 1;
                    }
                }
            }
        }
    }
    for(contador i =0; i<6; i++)
        cout << "pai[" << i+1 << "] = " << pai[i] << endl;
    for(contador i =0; i<6; i++)
        cout << "nivel[" << i+1 << "] = " << nivel[i] << endl;
    cout << endl;
}