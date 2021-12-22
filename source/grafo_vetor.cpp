#include "../headers/grafo_vetor.hpp"
#include "../headers/vetor_de_bits.hpp"
#include <fstream>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <deque>

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
    this->vetor_de_adjacencia = new vector<vertice> [numero_de_vertices];
    this->graus = (contador*) calloc (numero_de_vertices, sizeof (vertice));

    if (this->vetor_de_adjacencia == nullptr) 
        throw bad_alloc ();

    vertice vertice1, vertice2;
    while (arquivo >> vertice1 >> vertice2)
    {
        vertice1--;
        vertice2--;
        
        //if (not adjacentes(vertice1, vertice2)) // confiando que o grafo está descrito corretamente
        {
            vetor_de_adjacencia[vertice1].push_back(vertice2);
            graus[vertice1] += 1;
            if (vertice1 != vertice2)
            {
                vetor_de_adjacencia[vertice2].push_back(vertice1);
                graus[vertice2] += 1;
            }
        }

        this->numero_de_arestas++;
    }

    sort (graus, graus + this->numero_de_vertices);
}

bool 
grafo_vetor::adjacentes (vertice vertice1, vertice vertice2)
{
    bool grau_do_vertice1_maior = 
            vetor_de_adjacencia[vertice1].size() > vetor_de_adjacencia[vertice2].size();

    if (not grau_do_vertice1_maior )
    {
        auto vetor = vetor_de_adjacencia[vertice1];
        return
        ( find (vetor.begin(), vetor.end(), vertice2) != vetor.end());
    }
    else 
    {
        auto vetor = vetor_de_adjacencia[vertice2];
        return 
        ( find (vetor.begin(), vetor.end(), vertice1) != vetor.end());
    }
}

vector<vertice> 
grafo_vetor::operator[] (vertice vertice)
{
    return this->vetor_de_adjacencia [vertice];
}

void
grafo_vetor::dfs (vertice inicio, vertice* pai, vertice* nivel){
    inicio--;
    bool visitado[numero_de_vertices];
    for (contador i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0; //Tá errado! Mudar
    }
    stack<unsigned long> pilha;
    pilha.push(inicio);
    nivel[inicio] = 0;
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
}

void
grafo_vetor::bfs(vertice inicio, vertice* pai, vertice* nivel){
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
        for (auto it = vetor_de_adjacencia[v].begin(); it != vetor_de_adjacencia[v].end(); it++){
            if(!visitado[*it]){
                visitado[*it] = true;
                fila.push(*it);
                pai[*it] = v+1;
                nivel[*it] = nivel[v] + 1;
            }
        }
    }
}

unsigned int
grafo_vetor::calcula_distancia(vertice u, vertice v){
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
        for (auto it = vetor_de_adjacencia[x].begin(); it != vetor_de_adjacencia[x].end(); it++){
            if(!visitado[*it]){
                visitado[*it] = true;
                fila.push(*it);
                nivel[*it] = nivel[x] + 1;
                if(*it == v)
                    return nivel[v] - nivel[u]; 
            }
        }
    }
    return 0;//Não achou na busca = distancia não existe
}

unsigned int
grafo_vetor::calcula_diametro(){
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
            for (auto it = vetor_de_adjacencia[v].begin(); it != vetor_de_adjacencia[v].end(); it++){
                if(!visitado[*it]){
                    visitado[*it] = true;
                    fila.push(*it);
                    nivel[*it] = nivel[v] + 1;
                }
            }
        }
    }
    return distancia_max;
}

void
grafo_vetor::componentes_conexas(){
    struct compara_tamanho {
        bool operator() (deque<vertice> a, deque<vertice> b) const {
            return a.size() > b.size();
        }
    };
    multiset< deque<vertice> , compara_tamanho> componentes;
    vetor_de_bits visitado(numero_de_vertices);
    for(contador i = 0; i < numero_de_vertices; i++)
        visitado[i] = false;
    for(contador i = 0; i < numero_de_vertices; i++){
        if(!visitado[i]){
            queue<vertice> fila;
            deque<vertice> vertices_conexos;
            visitado[i] = true;
            fila.push(i);
            while(!fila.empty()){
                vertice v = fila.front();
                vertices_conexos.push_front(v);
                fila.pop();
                for (auto it = vetor_de_adjacencia[v].begin(); it != vetor_de_adjacencia[v].end(); it++){
                    if(!visitado[*it]){
                        visitado[*it] = true;
                        fila.push(*it);
                    }
                }
            }
            componentes.insert(vertices_conexos);
        }
    }
    for(auto it = componentes.begin(); it != componentes.end(); it++){
        deque<vertice> f = *it;
        cout << "{";
        for(auto it2 = f.begin(); it2 != f.end(); it2++)
            cout << *it2+1 << ", ";
        cout << "}" << endl;
    }
}