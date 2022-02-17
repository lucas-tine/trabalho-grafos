#include "../headers/grafo_vetor.hpp"
#include "../headers/vetor_de_bits.hpp"
#include <fstream>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <deque>

grafo_vetor::grafo_vetor (string nome_do_arquivo){
    //Construtor do grafo. Recebe o nome do arquivo como parâmetro
    
    ifstream arquivo (nome_do_arquivo, ios::in);
    *this = grafo_vetor(arquivo);
    arquivo.close();
}

grafo_vetor::grafo_vetor (ifstream& arquivo){
    //Construtor do grafo. Recebe um ponteiro para o arquivo como parâmetro

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
        vetor_de_adjacencia[vertice1].push_back(vertice2);
        graus[vertice1] += 1;
        if (vertice1 != vertice2)
        {
            vetor_de_adjacencia[vertice2].push_back(vertice1);
            graus[vertice2] += 1;
        }
        this->numero_de_arestas++;
    }

    sort (graus, graus + this->numero_de_vertices);
}

vector<vertice> 
grafo_vetor::operator[] (vertice vertice)
{
    return this->vetor_de_adjacencia [vertice];
}

void
grafo_vetor::dfs (vertice inicio, vertice* pai, vertice* nivel){
    /* Executa uma DFS no grafo, partindo do vértice inicio. Escreve o resultado no arquivo dfs.txt
    Recebe como parâmetro dois ponteiros para vetores
    Pai[u] = v --> Vértice v descobriu o vértice u
    Nivel[u] --> Nível do vértice u na árvore
    */

    inicio--;
    bool visitado[numero_de_vertices];
    for (contador i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0;
    }
    stack<unsigned long> pilha;
    pilha.push(inicio);
    nivel[inicio] = 1;
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
    ofstream arquivo;
    arquivo.open("dfs.txt");
    for(contador i = 0; i<numero_de_vertices; i++){
        if(nivel[i] == 0)
            arquivo << "Pai[" << i+1 << "] = " << "---" << endl;
        else
            arquivo << "Pai[" << i+1 << "] = " << pai[i] << endl;
    }
    for(contador i = 0; i<numero_de_vertices; i++){
        if(nivel[i] == 0)
            arquivo << "Nivel[" << i+1 << "] = " << "---" << endl;
        else
            arquivo << "Nivel[" << i+1 << "] = " << nivel[i]-1 << endl;
    }
    arquivo.close();
}

void
grafo_vetor::bfs(vertice inicio, vertice* pai, vertice* nivel){
    /* Executa uma BFS no grafo, partindo do vértice inicio. Escreve o resultado no arquivo bfs.txt
    Recebe como parâmetro dois ponteiros para vetores
    Pai[u] = v --> Vértice v descobriu o vértice u
    Nivel[u] --> Nível do vértice u na árvore
    */

    inicio--;
    vetor_de_bits visitado(numero_de_vertices);
    for(contador i = 0; i < numero_de_vertices; i++)
    {
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0;
    }
    queue<vertice> fila;
    visitado[inicio] = true;
    nivel[inicio] = 1;
    fila.push(inicio);
    while(!fila.empty())
    {
        vertice v = fila.front();
        fila.pop();
        for (auto it = vetor_de_adjacencia[v].begin(); it != vetor_de_adjacencia[v].end(); it++)
        {
            if(!visitado[*it])
            {
                visitado[*it] = true;
                fila.push(*it);
                pai[*it] = v+1;
                nivel[*it] = nivel[v] + 1;
            }
        }
    }

    ofstream arquivo;
    arquivo.open("bfs.txt");
    for(contador i = 0; i<numero_de_vertices; i++){
        if(nivel[i] == 0)
            arquivo << "Pai[" << i+1 << "] = " << "---" << endl;
        else
            arquivo << "Pai[" << i+1 << "] = " << pai[i] << endl;
    }
    for(contador i = 0; i<numero_de_vertices; i++){
        if(nivel[i] == 0)
            arquivo << "Nivel[" << i+1 << "] = " << "---" << endl;
        else
            arquivo << "Nivel[" << i+1 << "] = " << nivel[i]-1 << endl;
    }
    arquivo.close();
}

unsigned int
grafo_vetor::distancia_alvo(vertice u, vertice v){
    //Calcula e retorna a distância entre os vértices u e v

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
    //Calcula e retorna o diâmetro do grafo

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
    /* Calcula as componentes conexas do grafo
    O resultado é escrito no arquivo componentes_conexas.txt
    */

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
    ofstream arquivo;
    arquivo.open("componentes conexas.txt");
    arquivo << "Quantidade de componentes conexas: " << componentes.size() << endl;
    arquivo << "Tamanho da maior componente: " << (*componentes.begin()).size() << endl;
    arquivo << "Tamanho da menor componente: " << (*componentes.rbegin()).size() << endl;
    for(auto it = componentes.begin(); it != componentes.end(); it++){
        deque<vertice> f = *it;
        arquivo << "{";
        for(auto it2 = f.begin(); it2 != f.end()-1; it2++){
            arquivo << *it2+1 << ", ";
        }
        arquivo << *(f.end()-1)+1 << "}" << endl;
    }
    arquivo.close();
}

void
grafo_vetor::informacoes(){
    //Escreve informações gerais do grafo no arquivo info_do_grafo.txt

    ofstream arquivo;
    arquivo.open("info do grafo.txt");
    arquivo << "Numero de vertices: " << numero_de_vertices << endl;
    arquivo << "Numero de arestas: " << numero_de_arestas << endl;
    arquivo << "Grau Minimo: " << this->menor_grau() << endl;
    arquivo << "Grau Maximo: " << this->maior_grau() << endl;
    arquivo << "Grau Medio: " << this->grau_medio() << endl;
    arquivo << "Mediana de Grau: " << this->grau_mediano() << endl;
    arquivo.close();
    
}

vertice
grafo_vetor::estima_diametro(){
    //Calcula e retorna uma estimativa do diâmetro do grafo

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
    deque <vertice> maior_componente = *(componentes.begin());
    contador diametro = 0;
    for(contador i = 0; i < 10; i++){
        vertice distancia_max = 0;
        vetor_de_bits visitado(numero_de_vertices);
        vertice nivel[numero_de_vertices];
        vertice inicio = *(maior_componente.begin() + rand() % maior_componente.size());
        maior_componente.pop_front();
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
        if(distancia_max > diametro)
            diametro = distancia_max;
    }
    return diametro;
}