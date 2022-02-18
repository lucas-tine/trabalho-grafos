# Biblioteca de Grafos
Este é o trabalhos da disciplina Teoria dos Grafos - COS242 referente à dupla Lucas Tiné e Victor Ribeiro,
no período de 2021.2, da UFRJ.<br>
O trabalho consiste numa biblioteca desenvolvida em C++ para representar grafos.

## Sumário
- [Como usar](#como-usar)
- [Representação](#representação)
    - [Vetor de adjacência](#vetor-de-adjac%C3%AAncia)
    - [Matriz de adjacência](#Matriz-de-adjac%C3%AAncia)
- [Métodos](#m%C3%A9todos)
    - [DFS](#dfs)
    - [BFS](#bfs)
    - [Componentes Conexas](#componentes-conexas)
    - [Informações](#informacoes)
    - [Distancia alvo](#distancia-alvo)
    - [Distancia geral](#distancia-geral)
    - [Caminho alvo](#caminho-alvo)
    - [Caminho geral](#caminho-geral)
    - [Calcula diametro](#calcula-diametro)
    - [Estima diametro](#estima-diametro)
    - [Dijkstra](#dijkstra)
    - [Bellman ford](#bellman-ford)
    - [MST](#mst)
    - [Escrever MST](#escrever-mst)

## Como Usar
Para utilizar a biblioteca, basta escolher uma das três classes de representação de grafos e instanciar um objeto. O construtor recebe como parâmetro o nome do arquivo de entrada

```cpp
#include "headers/grafo_vetor.hpp"
grafo_vetor meu_grafo("entrada.txt");
```

Após, basta utilizar o objeto criado para acessar os métodos da classe

```cpp
//Esta linha realiza uma DFS no grafo a partir do vértice 1
meu_grafo.dfs(1);
```

## Representação
A biblioteca pode representar grafos usando Vetor de adjacência e Matriz de adjacência.

### Vetor de adjacência
Essa representação admite os seguintes tipos de grafo 
* Grafos não direcionados e sem peso
* Grafos não direcionados com pesos positivos
* Grafos direcionados com pesos positivos e negativos

### Matriz de adjacência
Essa representação admite os seguintes tipos de grafo
- Grafos não direcionados e sem peso

## Métodos
Os métodos abaixos foram implementados na biblioteca 

### DFS
A DFS realiza uma busca em profundidade no grafo a partir do vértice de origem escolhido.

### BFS
A BFS realiza uma busca em largura no grafo a partir do vértice de origem escolhido.

### Componentes conexas
Calcula as componentes conexas do grafo.

### Informacoes
Escreve informações gerais do grafo em um arquivo texto.

### Distancia alvo
Calcula e retorna a distância entre dois vértices.

### Distancia geral
Calcula e retorna as distância entre um vértice e todos os outros.

### Caminho alvo
Calcula e retorna o caminho mínimo entre dois vértices.

### Caminho geral
Calcula e retorna os caminhos mínimos entre um vértice e todos os outros.

### Calcula diametro
Calcula e retorna o diâmetro do grafo.

### Estima diametro
Calcula e retorna uma estimativa do diâmetro do grafo.

### Dijkstra
Realiza o algoristmo de Dijkstra a partir do vértice escolhido.

### Bellman ford
Realiza o algoristmo de Bellman-Ford a partir do vértice escolhido.

### MST
Calcula uma MST do grafo à partir do algoritmo de prim.

### Escrever MST
Escreve uma MST do grafo em um arquivo texto.
    
