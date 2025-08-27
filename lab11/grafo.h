#ifndef GRAFO_H
#define GRAFO_H

#include "fila.h"

typedef enum _estado {ACESA, APAGADA, QUEIMADA} estados;

typedef struct _grafo* p_grafo;

typedef struct _grafo{
    int **adj;             // matriz de adjacência do grafo (se adj[u][v] == 1, u e v são vizinhos)
    int n;                 // quantidade de vértices do grafo
    int vertice_conectado; // vértice conectado à alimentação
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
 *  Recebe o grafo e os dois vértices e modifica a matriz de adjacências do grafo.
 */
void insere_aresta(p_grafo g, int u, int v);

/** Remove uma aresta entre dois vértices de um grafo.
 * 
 *  Recebe o grafo e os dois vértices e modifica a matriz de adjacências do grafo.
 */
void remove_aresta(p_grafo g, int u, int v);

/** Verifica se há uma aresta entre dois vértices (ou seja, se são vizinhos).
 * 
 *  Recebe o grafo e os dois vértices e retorna 1 se houver e 0 caso contrário.
 */
int tem_aresta(p_grafo g, int u, int v);

/** Lê a entrada do programa e monta o grafo desejado.
 * 
 *  Não recebe nada e retorna o grafo montado.
 */
p_grafo le_grafo();

/** Realiza uma busca em profundidade dos caminhos a partir de um vértice inicial.
 *  A busca serve para verificar se um vértice está em um ciclo.
 * 
 *  Recebe o grafo, o vértice, o pai do vértice e o vetor de visitados e retorna
 *  1 se o vértice está em um ciclo e 0 se não está.
 * 
 *  O vértice "ini" é passado para que as chamadas recursivas carreguem a origem do
 *  caminho para poder fazer a comparação ao final.
 */
int busca_em_profundidade_verificar_ciclo(p_grafo g, int u, int pai, int *visitados_profundidade, int ini);

/** Chama a função de busca em profundidade para verificar se um vértice está num ciclo.
 * 
 * Recebe o grafo, o vértice e o vetor de visitados e tem o mesmo retorno da busca.
 */
int esta_em_ciclo(p_grafo g, int u, int *visitados_profundidade);

/** Realiza uma busca em largura dos caminhos a partir de um vértice inicial.
 *  Enquanto faz a busca, define o estado de um vértice a partir de seu pai.
 * 
 *  Recebe o grafo, o vértice inicial, um vetor de estados e um vetor de distâncias
 *  e retorna uma fila que representa o caminho.
 */
p_fila busca_em_largura(p_grafo g, int ini, estados *vet_estados, int *vet_distancias);

/** Imprime um caminho de um grafo, com as distâncias e os estados de cada vértice.
 * 
 *  Recebe o grafo, o vetor dos estados, o vetor das distâncias e a fila de impressão
 *  e imprime o caminho.
 */
void imprime_caminho(p_grafo g, estados *vet_estados, int *vet_distancias, p_fila fila_imprimir);

#endif