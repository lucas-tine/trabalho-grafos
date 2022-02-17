#include "../headers/grafo_vetor_peso.hpp"
#include "../headers/vetor_de_bits.hpp"
#include <fstream>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <deque>
#include "../headers/vetor_de_bits.hpp"
#include "../headers/heap_de_arestas.hpp"
#include <limits>

grafo_vetor_peso::grafo_vetor_peso (string nome_do_arquivo, bool direcionado){
    /* Construtor do grafo. Recebe o nome do arquivo como parâmetro o nome do arquivo e um booleano
    O paramêtro direcionado define se o grafo é direcionado ou não. Caso seja, direcionado = true
    */

    ifstream arquivo (nome_do_arquivo, ios::in);
    *this = grafo_vetor_peso(arquivo, direcionado);
    arquivo.close();
}

grafo_vetor_peso::grafo_vetor_peso (ifstream& arquivo, bool direcionado){
    /* Construtor do grafo. Recebe o nome do arquivo como parâmetro o nome do arquivo e um booleano
    O paramêtro direcionado define se o grafo é direcionado ou não. Caso seja, direcionado = true
    */

    arquivo.seekg(0, arquivo.beg);
    arquivo >> this->numero_de_vertices;
    this->direcionado = direcionado;
    this->vetor_de_adjacencia = new vector<Tupla_peso> [numero_de_vertices];
    this->graus = (contador*) calloc (numero_de_vertices, sizeof (vertice));

    if (this->vetor_de_adjacencia == nullptr) 
        throw bad_alloc ();

    vertice vertice1, vertice2;
    double peso;
    this->tem_peso_negativo = false;
    while (arquivo >> vertice1 >> vertice2 >> peso)
    {
        vertice1--;
        vertice2--;
        if(peso < 0.0)
            this->tem_peso_negativo = true;
        vetor_de_adjacencia[vertice1].push_back({vertice2, peso});
        graus[vertice1] += 1;
        if (not this->direcionado)
        {
            vetor_de_adjacencia[vertice2].push_back({vertice1, peso});
            graus[vertice2] += 1;
        }
        this->numero_de_arestas++;
    }

    if(this->tem_peso_negativo and not this->direcionado)
        cout << "Esta biblioteca nao suporta grafos nao direcionados com pesos negativos." << endl;
    sort (graus, graus + this->numero_de_vertices);
}

vector<Tupla_peso> 
grafo_vetor_peso::operator[] (vertice vertice)
{
    return this->vetor_de_adjacencia [vertice];
}

void
grafo_vetor_peso::dfs (vertice inicio, vertice* pai, vertice* nivel){
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
                vertice u = (*it).vertice_conectado;
                pilha.push(u);;
                if(!visitado[u]){
                    pai[u] = v+1;
                    nivel[u] = nivel[v] + 1;
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
            vertice u = (*it).vertice_conectado;
            if(!visitado[u])
            {
                visitado[u] = true;
                fila.push(u);
                pai[u] = v+1;
                nivel[u] = nivel[v] + 1;
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

void
grafo_vetor_peso::componentes_conexas(){
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
                    vertice u = (*it).vertice_conectado;
                    if(!visitado[u]){
                        visitado[u] = true;
                        fila.push(u);
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

retorno_mst
grafo_vetor_peso::MST (){
    /* Calcula uma MST do grafo à partir do algoritmo de prim
    Retorna uma estrutura, definida no header, com informações sobre a MST
    */

    vector<aresta_completa> vetor_do_heap (this->numero_de_vertices); 
    heap_de_arestas arestas_disponiveis(vetor_do_heap.begin(), vetor_do_heap.end());
    vetor_de_bits alcancado(this->numero_de_vertices); // vertices alcancados
    retorno_mst mst_resultante = {
        true, // mst valida
        0.0,  // peso
        vector<vertice> (this->numero_de_vertices) // pais
    };
    alcancado.reset();
    for (contador i = 0; i < this->numero_de_vertices; i++)
        mst_resultante.pais_na_arvore[i] = this->numero_de_vertices; // isso indica que o vertice nao foi alcancado

    // começando no vertice 0
    for (Tupla_peso& aresta_incidente: (*this)[0])
        arestas_disponiveis.push (
            aresta_completa {
                0,
                aresta_incidente.vertice_conectado,
                aresta_incidente.peso
            }
        );
    alcancado[0] = true;
    mst_resultante.pais_na_arvore[0] = 0;

    // enquanto arestas não vazias
    while (not arestas_disponiveis.empty())
    {
        // escolher menor arestas
        aresta_completa aresta_preferencial = arestas_disponiveis.top();
        arestas_disponiveis.pop();

        // se extremidades da aresta nao são conhecidas
        if ( (not alcancado[aresta_preferencial.v1]) or (not alcancado[aresta_preferencial.v2]) )
        {
            bool v1_alcancado = alcancado[aresta_preferencial.v1] ;
            vertice recem_incluido = v1_alcancado ? 
                aresta_preferencial.v2 : aresta_preferencial.v1;

            vertice pai_do_mais_recente = v1_alcancado ? 
                aresta_preferencial.v1 : aresta_preferencial.v2;

            // incluir aresta no caminho
            mst_resultante.pais_na_arvore[recem_incluido] = pai_do_mais_recente;
            mst_resultante.custo_da_arvore += aresta_preferencial.peso;

            // atualizar extremidades da nova aresta como conhecidas
            alcancado[recem_incluido] = true;

            // atualizar arestas disponíveis
            for (Tupla_peso& aresta_incidente: (*this)[recem_incluido])
                if (aresta_incidente.vertice_conectado == pai_do_mais_recente) 
                    continue;
                else
                    arestas_disponiveis.push (
                        aresta_completa {
                            recem_incluido,
                            aresta_incidente.vertice_conectado,
                            aresta_incidente.peso
                        }
                    );  
        }
    }
    for (vertice i = 0; (i < alcancado.tamanho_em_bits()) and mst_resultante.eh_arvore; i++)
        if (not alcancado[i])
            mst_resultante.eh_arvore = false;
    return mst_resultante;
}

void 
grafo_vetor_peso::escrever_MST (string nome_do_arquivo){
    //Escreve uma MST do grafo no arquivo mst_[nome_do_grafo].txt

    ofstream arquivo (nome_do_arquivo.c_str(), ofstream::out|ofstream::trunc);
    retorno_mst mst = MST();

    if (not mst.eh_arvore)
        cout << "[nao ha MST para este grafo]" << endl;
    else 
        cout << "custo da MST encontrada: " << mst.custo_da_arvore << endl;
        

    for (contador i = 1; i < this->numero_de_vertices; i++)
        arquivo << i+1 << " " << 
        ( (mst.pais_na_arvore[i] < this->numero_de_vertices) ? to_string(mst.pais_na_arvore[i]+1) : string("x") ) 
        << endl;

    arquivo.close();
}

retorno_dijkstra
grafo_vetor_peso::dijkstra(vertice inicio){
    /* Realiza o algoristmo de Dijkstra a partir do vértice inicio
    Retorna uma estrutura, definida no header, com informações sobre o resultado do algoritmo
    */

    inicio--;

    vector<float> dist(this->numero_de_vertices, numeric_limits<float>::infinity());
    dist[inicio] = 0;

    vector<vertice> pai(this->numero_de_vertices);
    for(contador i = 0; i<this->numero_de_vertices; i++)
        pai[i] = i;

    set< pair<float, vertice> > visitados;
    visitados.insert({0, inicio});

    while(!visitados.empty()){
        vertice u = visitados.begin()->second;
        
        visitados.erase(visitados.begin());

        for(auto it = vetor_de_adjacencia[u].begin(); it != vetor_de_adjacencia[u].end(); it++){
            vertice v = it->vertice_conectado;

            if(dist[v] > dist[u] + it->peso){
                dist[v] = dist[u] + it->peso;
                pai[v] = u;
                visitados.insert({dist[v], v});
            }
        }
    }
    return{
        dist,
        pai
    };
}

retorno_bellman_ford 
grafo_vetor_peso::bellman_ford (vertice inicio){
    /* Realiza o algoristmo de Bellman-Ford a partir do vértice inicio
    Retorna uma estrutura, definida no header, com informações sobre o resultado do algoritmo
    */

    inicio--;

    vector<float> dist (this->numero_de_vertices);
    set<vertice> possiveis_atualizacoes; // guarda vertices do qual um vizinho foi atualizado na ultima iteracao, e portanto ainda podem se atualizar 
    vector<vertice> pai (this->numero_de_vertices); // pais na arvore geradora
    grafo_vetor_peso& grafo = *this;
    for (vertice v = 0; v < this->numero_de_vertices; v++)
    {
            dist[v] = numeric_limits<float>::infinity();
            possiveis_atualizacoes.insert(v); // a principio, qualquer vertice pode ser atualizado
            pai[v] = this->numero_de_vertices; // isso indica que o vertice ainda nao foi alcancado
    }
    dist[inicio] = 0;
    pai[inicio] = inicio; // se mantem sempre que nao houverem ciclos negativos

    for (contador i = 0; i < this->numero_de_vertices-1 ; i++)
    {
        
        set<vertice> proximas_atualizacoes;
        for (vertice v: possiveis_atualizacoes)
        {
            bool custo_de_v_modificado = false;
            for (Tupla_peso& aresta_ligada: grafo[v])
            {
                const vertice vizinho = aresta_ligada.vertice_conectado;
                const float peso = aresta_ligada.peso;
                if (dist[vizinho] > (dist[v] + peso) )
                {
                    dist[vizinho] = dist[v] + peso;
                    pai[vizinho] = v;
                    custo_de_v_modificado = true;
                }
            }
            if (custo_de_v_modificado)
                for (Tupla_peso& aresta_ligada: grafo[v])
                    proximas_atualizacoes.insert (aresta_ligada.vertice_conectado);
        }
        if (proximas_atualizacoes.empty()) break;
        possiveis_atualizacoes = proximas_atualizacoes;
    }

    //Loop para detecção de ciclos negativos
    bool ciclos_negativos = false;
    for (contador v=0; v<this->numero_de_vertices; v++){
        for (Tupla_peso& aresta_ligada: grafo[v])
        {
            const vertice vizinho = aresta_ligada.vertice_conectado;
            const float peso = aresta_ligada.peso;
            if (dist [vizinho] > (dist[v] + peso) )
            {
                if(not ciclos_negativos)
                pai[vizinho] = v;
                ciclos_negativos = true;
            }
        }
    }
    
    return retorno_bellman_ford {
        dist,
        pai,
        ciclos_negativos
    };
}

float 
grafo_vetor_peso::distancia_alvo(vertice inicio, vertice alvo){
    //Calcula e retorna distância entre o vertice inicio e alvo

    if(tem_peso_negativo){
        //Fazer floyd-warshal ou belmman-ford
        retorno_bellman_ford bf = bellman_ford(inicio);
        if(!bf.ciclos_negativos){
            return bf.custo_do_vertice[alvo-1];
        }else{
            cout << "Grafo com ciclo negativo: distancia indefinida." << endl;
            return {};
        }
    }
    else{
        
        return dijkstra(inicio).custo_do_vertice[alvo-1];
    }
}

vector<float>
grafo_vetor_peso::distancia_geral(vertice inicio){
    /* Calcula e retorna distância entre o vertice inicio e todos os outros.
    O retorno é um vetor contendo a distância entre i e inicio.
    */

    if(tem_peso_negativo){
        retorno_bellman_ford bf = bellman_ford(inicio);
        if(!bf.ciclos_negativos){
            return bf.custo_do_vertice;
        }else{
            cout << "Grafo com ciclo negativo: distancia indefinida." << endl;
            return {};
        }
    }
    else{
        return dijkstra(inicio).custo_do_vertice;
    }
}

vector<vertice> 
grafo_vetor_peso::caminho_alvo(vertice inicio, vertice alvo){
    /* Calcula e retorna o caminho entre o vertice inicio e alvo.
    O retorno é um vetor contendo o caminho entre o inicio e o alvo.
    */

    if(tem_peso_negativo){
        retorno_bellman_ford bf = bellman_ford(inicio);
        if(!bf.ciclos_negativos){
            vector<vertice> pai = bf.pai_do_vertice_no_caminho;
            vector<vertice> caminho;
            vertice it = pai[alvo-1];
            while(it != inicio-1){
                caminho.push_back(it+1);
                it = pai[it];
            }
            caminho.push_back(inicio);
            reverse(caminho.begin(), caminho.end());
            if(alvo!=inicio)
                caminho.push_back(alvo);
            return caminho;
        }else{
            cout << "Grafo com ciclo negativo: caminho minimo indefinido." << endl;
            return {};
        }
    }
    else{
        vector<vertice> pai = dijkstra(inicio).pai_do_vertice_no_caminho;
        vector<vertice> caminho;
        vertice it = pai[alvo-1];
        while(it != inicio-1){
            caminho.push_back(it+1);
            it = pai[it];
        }
        caminho.push_back(inicio);
        reverse(caminho.begin(), caminho.end());
        if(alvo!=inicio)
            caminho.push_back(alvo);
        return caminho;
    }
}

vector<vector<vertice>>
grafo_vetor_peso::caminho_geral(vertice inicio){
    /* Calcula e retorna o caminho entre o vertice inicio e alvo.
    O retorno é um vetor contendo vetores de caminho entre o i e inicio.
    */
   
    if(tem_peso_negativo){
        retorno_bellman_ford bf = bellman_ford(inicio);
        if(!bf.ciclos_negativos){
            vector<vector<vertice>> todos_caminhos;
            vector<vertice> pai = bf.pai_do_vertice_no_caminho;
            for(contador alvo = 1; alvo <= numero_de_vertices; alvo++){
                vector<vertice> caminho;
                vertice it = pai[alvo-1];
                while(it != inicio-1){
                    caminho.push_back(it+1);
                    it = pai[it];
                }
                caminho.push_back(inicio);
                reverse(caminho.begin(), caminho.end());
                if(alvo!=inicio)
                    caminho.push_back(alvo);
                todos_caminhos.push_back(caminho);
            }
            return todos_caminhos;
            
        }else{
            cout << "Grafo com ciclo negativo: caminho minimo indefinido." << endl;
            return {};
        }
    }
    else{
        vector<vertice> pai = dijkstra(inicio).pai_do_vertice_no_caminho;
        vector<vector<vertice>> todos_caminhos;
        for(contador alvo = 1; alvo <= numero_de_vertices; alvo++){
            vector<vertice> caminho;
            vertice it = pai[alvo-1];
            while(it != inicio-1){
                caminho.push_back(it+1);
                it = pai[it];
            }
            caminho.push_back(inicio);
            reverse(caminho.begin(), caminho.end());
            if(alvo!=inicio)
                caminho.push_back(alvo);
            todos_caminhos.push_back(caminho);
        }
        return todos_caminhos;
    }
}