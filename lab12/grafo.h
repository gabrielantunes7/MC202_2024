#ifndef GRAFO_H
#define GRAFO_H

#include "heap.h"

#define INT_MAX 100000

typedef struct _vertice{
    int valor;     // índice do vértice
    char *nome;    // nome da cidade
    int populacao; // populacao da cidade
} vertice;

typedef struct _no* p_no;

// um nó representa um aresta entre um vértice e outro na lista de adjacências
typedef struct _no{
    vertice vertice; // destino da aresta
    int peso;        // peso de um caminho até aquela cidade 
    p_no prox;       // ponteiro para o pŕoximo nó na lista ligada 
} no;

typedef struct _grafo* p_grafo;

// Grafo não direcionado
typedef struct _grafo{
    int n;            // quantidade de vértices do grafo
    vertice *cidades; // vetor das cidades do grafo
    p_no *adj;        // lista de adjacências do grafo
} grafo;

/** Cria um grafo vazio.
 * 
 *  Recebe o número de vértices que o grafo terá e retorna um ponteiro para o grafo.
 */
p_grafo cria_grafo(int n);

/** Libera a memória utilizada pelo grafo.
 * 
 *  Recebe um grafo e não retorna nada.
 */
void destroi_grafo(p_grafo g);

/** Adiciona uma aresta entre dois vértices de um grafo.
 * 
 *  Recebe o grafo, os dois vértices e o peso da aresta e modifica a lista de adjacências do grafo.
 */
void insere_aresta(p_grafo g, vertice u, vertice v, int peso);

/** Remove uma aresta entre dois vértices de um grafo.
 * 
 *  Recebe o grafo e os dois vértices e modifica a lista de adjacências do grafo.
 */
void remove_aresta(p_grafo g, vertice u, vertice v);

/** Verifica se há uma aresta entre dois vértices (ou seja, se são vizinhos).
 * 
 *  Recebe o grafo e os dois vértices e retorna 1 se houver e 0 caso contrário.
 */
int tem_aresta(p_grafo g, vertice u, vertice v);

/** Encontra os menores caminhos a partir de um vértice do grafo.
 * 
 *  Recebe o grafo e o vértice inicial e retorna uma árvore de menores caminhos.
 */
item* dijkstra(p_grafo g, vertice ini);

/** Lê as cidades e suas ligações e cria um grafo.
 * 
 *  Não recebe nada e retorna o grafo criado.
 */
p_grafo le_grafo();

/** Encontra os melhores centros de distribuição e a maior distância de atendimento.
 * 
 *  Recebe o grafo e uma váriavel de distância máxima que será modificada por referência.
 */
vertice* encontra_melhores_centros(p_grafo g, int *distancia_max);

#endif