#include "../headers/grafo_vetor_peso.hpp"
#include "../headers/vetor_de_bits.hpp"
#include <fstream>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <deque>

grafo_vetor_peso::grafo_vetor_peso (string nome_do_arquivo)
{
    ifstream arquivo (nome_do_arquivo, ios::in);
    *this = grafo_vetor_peso(arquivo);
    arquivo.close();
}

grafo_vetor_peso::grafo_vetor_peso (ifstream& arquivo)
{
    arquivo.seekg(0, arquivo.beg);
    arquivo >> this->numero_de_vertices;
    this->vetor_de_adjacencia = new vector<Tupla_peso> [numero_de_vertices];
    this->graus = (contador*) calloc (numero_de_vertices, sizeof (vertice));

    if (this->vetor_de_adjacencia == nullptr) 
        throw bad_alloc ();

    vertice vertice1, vertice2;
    double peso;
    while (arquivo >> vertice1 >> vertice2 >> peso)
    {
        vertice1--;
        vertice2--;
        Tupla_peso tupla;
        tupla.peso = peso;
        
        //if (not adjacentes(vertice1, vertice2)) // confiando que o grafo está descrito corretamente
        {
            tupla.vertice_conectado = vertice2;
            vetor_de_adjacencia[vertice1].push_back(tupla);
            graus[vertice1] += 1;
            if (vertice1 != vertice2)
            {
                tupla.vertice_conectado = vertice1;
                vetor_de_adjacencia[vertice2].push_back(tupla);
                graus[vertice2] += 1;
            }
        }
        this->numero_de_arestas++;
    }

    sort (graus, graus + this->numero_de_vertices);
}
/*
bool 
grafo_vetor_peso::adjacentes (vertice vertice1, vertice vertice2)
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
}*/

vector<Tupla_peso> 
grafo_vetor_peso::operator[] (vertice vertice)
{
    return this->vetor_de_adjacencia [vertice];
}
/*
void
grafo_vetor_peso::dfs (vertice inicio, vertice* pai, vertice* nivel){
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
grafo_vetor_peso::bfs(vertice inicio, vertice* pai, vertice* nivel){
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
grafo_vetor_peso::calcula_distancia(vertice u, vertice v){
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
grafo_vetor_peso::calcula_diametro(){
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
grafo_vetor_peso::componentes_conexas(){
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
grafo_vetor_peso::informacoes(){
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
grafo_vetor_peso::estima_diametro(){
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
*/