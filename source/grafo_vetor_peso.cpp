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
    this->tem_peso_negativo = false;
    while (arquivo >> vertice1 >> vertice2 >> peso)
    {
        vertice1--;
        vertice2--;
        if(peso < 0.0)
            this->tem_peso_negativo = true;
        
        //if (not adjacentes(vertice1, vertice2)) // confiando que o grafo está descrito corretamente
        {
            vetor_de_adjacencia[vertice1].push_back({vertice2, peso});
            graus[vertice1] += 1;
            if (vertice1 != vertice2)
            {
                vetor_de_adjacencia[vertice2].push_back({vertice1, peso});
                graus[vertice2] += 1;
            }
        }
        this->numero_de_arestas++;
    }

    sort (graus, graus + this->numero_de_vertices);
}

bool 
grafo_vetor_peso::adjacentes (vertice vertice1, vertice vertice2)
{
    /*
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
    }*/
}

vector<Tupla_peso> 
grafo_vetor_peso::operator[] (vertice vertice)
{
    return this->vetor_de_adjacencia [vertice];
}

void
grafo_vetor_peso::dfs (vertice inicio, vertice* pai, vertice* nivel)
{
    
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
grafo_vetor_peso::bfs(vertice inicio, vertice* pai, vertice* nivel)
{
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

unsigned int
grafo_vetor_peso::calcula_distancia(vertice u, vertice v)
{
    /*
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
            vertice y = (*it).vertice_conectado;
            if(!visitado[y]){
                visitado[y] = true;
                fila.push(y);
                nivel[y] = nivel[x] + (*it).peso;
                if(y == v)
                    return nivel[v] - nivel[u]; 
            }
        }
    }
    return 0;//Não achou na busca = distancia não existe
    */
}

unsigned int
grafo_vetor_peso::calcula_diametro()
{
    /*
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
                vertice u = (*it).vertice_conectado;
                if(!visitado[u]){
                    visitado[u] = true;
                    fila.push(u);
                    nivel[u] = nivel[v] + 1;
                }
            }
        }
    }
    return distancia_max;
    */
}

void
grafo_vetor_peso::componentes_conexas()
{
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
grafo_vetor_peso::estima_diametro()
{
    /*
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
    */
}

retorno_mst
grafo_vetor_peso::MST ()
{
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

retorno_mst 
grafo_vetor_peso::escrever_MST (string nome_do_arquivo)
{
    ofstream arquivo (nome_do_arquivo.c_str(), ofstream::out|ofstream::trunc);
    retorno_mst mst = MST();

    if (not mst.eh_arvore)
        arquivo << "[nao ha MST para este grafo]" << endl;
    else 
        arquivo << "custo da MST encontrada: " << mst.custo_da_arvore << endl << endl;
        for (contador i = 0; i < this->numero_de_vertices; i++)
            arquivo << "pai[" << i+1 << "] = " << (i == 0 ? "(origem) " : "") <<
            ( (mst.pais_na_arvore[i] < this->numero_de_vertices) ? to_string(mst.pais_na_arvore[i] + 1) : string("x") ) 
            << endl;

    arquivo.close();
    return mst;
}

pair < vector<double>, vector<vertice> >
grafo_vetor_peso::dijkstra(vertice inicio){
    inicio--;

    vector<double> dist(this->numero_de_vertices, ULLONG_MAX);
    dist[inicio] = 0;

    vector<vertice> pai(this->numero_de_vertices);
    for(contador i = 0; i<this->numero_de_vertices; i++)
        pai[i] = i;

    set< pair<double, vertice> > visitados;
    visitados.insert({0, inicio});

    while(!visitados.empty()){
        double dist_atual = visitados.begin()->first;
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
    pair < vector<double>, vector<vertice> >p;
    p.first = dist;
    p.second = pai;
    return p;
}

double 
grafo_vetor_peso::distancia_alvo(vertice inicio, vertice alvo){
    /* Retorna distância entre o vertice inicio e alvo.
     */
    if(tem_peso_negativo){
        //Fazer floyd-warshal ou belmman-ford
    }
    else{
        
        return dijkstra(inicio).first[alvo-1];
    }
}

vector<double>
grafo_vetor_peso::distancia_geral(vertice inicio){
    /* Retorna distância entre o vertice inicio e todos os outros.
    O índice i do vetor de retorno é: id_vertice-1.
    O conteúdo é a distância entre os vértices.
     */
    if(tem_peso_negativo){
        //Fazer floyd-warshal ou belmman-ford
    }
    else{
        return dijkstra(inicio).first;
    }
}

vector<vertice> 
grafo_vetor_peso::caminho_alvo(vertice inicio, vertice alvo){
    /* Retorna o caminho entre o vertice inicio e alvo.
     */
    if(tem_peso_negativo){
        //Fazer floyd-warshal ou belmman-ford
    }
    else{
        vector<vertice> pai = dijkstra(inicio).second;
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
    /* Retorna caminho entre o vertice inicio e todos os outros.
    O índice i do vetor de retorno é: id_vertice-1.
    O conteúdo é o vetor caminho entre os vértices.
     */
    if(tem_peso_negativo){
        //Fazer floyd-warshal ou belmman-ford
    }
    else{
        vector<vertice> pai = dijkstra(inicio).second;
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

retorno_bellman_ford 
grafo_vetor_peso::bellman_ford (vertice t)
{
    // A existencia de um ciclo negativo parece causar os seguintes sintomas:
    // se t pertence ao ciclo, pai[t] não é t 
    // se t não pertence ao ciclo negativo, a arvore geradora se torna desconexa

    // OBS: descobertas empiricas e ainda questionaveis, CARECEM DE PROVAS

    vector<float> menor_custo_atual (this->numero_de_vertices);
    set<vertice> possiveis_atualizacoes; // guarda vertices do qual um vizinho foi atualizado na ultima iteracao, e portanto ainda podem se atualizar 
    vector<vertice> pais_no_melhor_caminho (this->numero_de_vertices); // pais na arvore geradora
    grafo_vetor_peso& grafo = *this;
    for (vertice v = 0; v < this->numero_de_vertices; v++)
    {
            menor_custo_atual[v] = numeric_limits<float>::infinity();
            possiveis_atualizacoes.insert(v); // a principio, qualquer vertice pode ser atualizado
            pais_no_melhor_caminho[v] = this->numero_de_vertices; // isso indica que o vertice ainda nao foi alcancado
    }
    menor_custo_atual[t] = 0;
    pais_no_melhor_caminho[t] = t; // se mantem sempre que nao houverem ciclos negativos

    for (contador i = 0; i < this->numero_de_vertices-1 ; i++)
    {
        /* // DEBUG
        for (contador v = 0; v < this->numero_de_vertices ; v++) 
            cout << "| " << menor_custo_atual[v] << ' ';
        cout << ' ' << '|' << endl;
        */
        set<vertice> proximas_atualizacoes;
        vector<float> custo_atual_congelado = vector<float> (menor_custo_atual); // restringe o numero de arestas percorridas na iteracao
        for (vertice v: possiveis_atualizacoes)
        {
            bool custo_de_v_modificado = false;
            for (Tupla_peso& aresta_ligada: grafo[v])
            {
                const vertice vizinho = aresta_ligada.vertice_conectado;
                const float peso = aresta_ligada.peso;
                if (pais_no_melhor_caminho[vizinho] == v) continue; // evita que uma aresta negativa forme loop
                if (custo_atual_congelado [v] > (custo_atual_congelado[vizinho] + peso) )
                {
                    menor_custo_atual[v] = custo_atual_congelado[vizinho] + peso;
                    pais_no_melhor_caminho[v] = vizinho;
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

    return retorno_bellman_ford {
        menor_custo_atual,
        pais_no_melhor_caminho
    };
}