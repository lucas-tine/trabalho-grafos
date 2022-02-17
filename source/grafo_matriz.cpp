#include "../headers/grafo_matriz.hpp"
#include "../headers/vetor_de_bits.hpp"
#include <stack>
#include <queue>
#include <algorithm>
#include <set>
#include <deque>

grafo_matriz::grafo_matriz (string nome_do_arquivo){
    //Construtor do grafo. Recebe o nome do arquivo como parâmetro
    
    ifstream arquivo (nome_do_arquivo, ios::in);
    *this = grafo_matriz (arquivo);
    arquivo.close();
}

grafo_matriz::grafo_matriz (ifstream& arquivo){
    //Construtor do grafo. Recebe um ponteiro para o arquivo como parâmetro

    arquivo.seekg(0, arquivo.beg);
    arquivo >> this->numero_de_vertices;
    assegurar_bitagem_matriz();
    graus = (contador*) calloc (numero_de_vertices, sizeof (vertice));
    matriz_de_adjacencia = matriz_simetrica_bits(numero_de_vertices);
    matriz_de_adjacencia.reset();
    vertice vertice1, vertice2;
    while (arquivo >> vertice1 >> vertice2)
    {
        vertice1--;
        vertice2--;
        matriz_de_adjacencia[vertice1][vertice2] = 1;
        this->numero_de_arestas++;
        graus [vertice1] += 1;
        if (vertice1 != vertice2)
            graus[vertice2] += 1;
    }

    sort (graus, graus + this->numero_de_vertices);
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
    /* Executa uma DFS no grafo, partindo do vértice inicio. Escreve o resultado no arquivo dfs.txt
    Recebe como parâmetro dois ponteiros para vetores
    Pai[u] = v --> Vértice v descobriu o vértice u
    Nivel[u] --> Nível do vértice u na árvore
    */

    inicio--;
    vetor_de_bits visitado (numero_de_vertices);

    for (contador i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0;
    }

    stack<vertice> pilha;
    pilha.push(inicio);
    nivel[inicio] = 1;
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
grafo_matriz::bfs(vertice inicio, vertice* pai, vertice* nivel){
    /* Executa uma BFS no grafo, partindo do vértice inicio. Escreve o resultado no arquivo bfs.txt
    Recebe como parâmetro dois ponteiros para vetores
    Pai[u] = v --> Vértice v descobriu o vértice u
    Nivel[u] --> Nível do vértice u na árvore
    */

    inicio--;
    vetor_de_bits visitado(numero_de_vertices);
    for(contador i = 0; i < numero_de_vertices; i++){
        visitado[i] = false;
        pai[i] = 0;
        nivel[i] = 0;
    }
    queue<vertice> fila;
    visitado[inicio] = true;
    nivel[inicio] = 1;
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
grafo_matriz::distancia_alvo(vertice u, vertice v){
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

void
grafo_matriz::componentes_conexas(){
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
                for (vertice j = 0; j < numero_de_vertices; j++){
                    if(matriz_de_adjacencia[v][j] == 1){
                        if(!visitado[j]){
                            visitado[j] = true;
                            fila.push(j);
                        }
                    }
                }
            }
            componentes.insert(vertices_conexos);
        }
    }
    ofstream arquivo;
    arquivo.open("componentes_conexas.txt");
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
grafo_matriz::informacoes(){
    //Escreve informações gerais do grafo no arquivo info_do_grafo.txt

    ofstream arquivo;
    arquivo.open("info_do_grafo.txt");
    arquivo << "Numero de vertices: " << numero_de_vertices << endl;
    arquivo << "Numero de arestas: " << numero_de_arestas << endl;
    arquivo << "Grau Minimo: " << this->menor_grau() << endl;
    arquivo << "Grau Maximo: " << this->maior_grau() << endl;
    arquivo << "Grau Medio: " << this->grau_medio() << endl;
    arquivo << "Mediana de Grau: " << this->grau_mediano() << endl;
    arquivo.close();
    
}

vertice
grafo_matriz::estima_diametro(){
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
                fila.pop();
                for (vertice i = 0; i < numero_de_vertices; i++){
                    if(matriz_de_adjacencia[v][i] == 1){
                        if(!visitado[i]){
                            visitado[i] = true;
                            fila.push(i);
                        }
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
        if(distancia_max > diametro)
            diametro = distancia_max;
    }
    return diametro;
}