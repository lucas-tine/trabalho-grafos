#include "../headers/grafo_matriz.hpp"
#include "../headers/vetor_de_bits.hpp"
#include <stack>
#include <queue>

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
grafo_matriz::dfs (vertice inicio, vertice* pai, vertice* nivel){
    inicio--;
    vetor_de_bits visitado (numero_de_vertices);

    for (contador i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0; //Tá errado! Mudar
    }

    stack<vertice> pilha;
    pilha.push(inicio);
    nivel[inicio] = 0;
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
}

void
grafo_matriz::bfs(vertice inicio, vertice* pai, vertice* nivel){
    inicio--;
    vetor_de_bits visitado(numero_de_vertices);
    for(contador i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0;//Errado! Mudar
    }
    queue<vertice> fila;
    visitado[inicio] = true;
    fila.push(inicio);
    while(!fila.empty()){
        vertice v = fila.front();
        fila.pop();
        for (vertice i = 0; i < numero_de_vertices; i++){
            if(matriz_de_adjacencia[v][i] == 1){
                if(!visitado[i]){
                    visitado[i] = true;
                    fila.push(i);
                    pai[i] = v+1;
                    nivel[i] = nivel[v] + 1;
                }
            }
        }
    }
}

unsigned int
grafo_matriz::calcula_distancia(vertice u, vertice v){
    u--;
    v--;
    vetor_de_bits visitado(numero_de_vertices);
    vertice nivel[numero_de_vertices];
    for(contador i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        nivel[i] = 0;
    }
    queue<vertice> fila;
    visitado[u] = true;
    fila.push(u);
    while(!fila.empty()){
        vertice x = fila.front();
        fila.pop();
        for (vertice i = 0; i < numero_de_vertices; i++){
            if(matriz_de_adjacencia[x][i] == 1){
                if(!visitado[i]){
                    visitado[i] = true;
                    fila.push(i);
                    nivel[i] = nivel[x] + 1;
                    if(i == v)
                        return nivel[v] - nivel[u]; 
                }
            }
        }
    }
    return 0;//Não achou na busca = distancia não existe
}

unsigned int
grafo_matriz::calcula_diametro(){
    vertice distancia_max = 0;
    vetor_de_bits visitado(numero_de_vertices);
    vertice nivel[numero_de_vertices];
    for(vertice i = 0; i < numero_de_vertices; i++){
        vertice inicio = i;
        for(contador i = 0; i < numero_de_vertices; i++){
            visitado[i] = false;
            nivel[i] = 0;
        }
        queue<vertice> fila;
        visitado[inicio] = true;
        fila.push(inicio);
        while(!fila.empty()){
            vertice v = fila.front();
            fila.pop();
            if(nivel[v] > distancia_max)
                distancia_max = nivel[v];
            for (vertice i = 0; i < numero_de_vertices; i++){
                if(matriz_de_adjacencia[v][i] == 1){
                    if(!visitado[i]){
                        visitado[i] = true;
                        fila.push(i);
                        nivel[i] = nivel[v] + 1;
                    }
                }
            }
        }
    }
    return distancia_max;
}