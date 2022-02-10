#ifndef HEAP_DE_ARESTAS
#define HEAP_DE_ARESTAS
#include <bits/stdc++.h>

struct aresta_completa { // utilizada no calculo de MSTs
    vertice v1, v2;
    double peso;
};

struct prioridade_de_menores{
        bool operator() (aresta_completa a, aresta_completa b) {
            return a.peso > b.peso; 
        }
};

typedef priority_queue <aresta_completa, vector<aresta_completa>, prioridade_de_menores> heap_de_arestas;

#endif