#ifndef HEAP_H
#define HEAP_H


typedef struct _item{
    int valor; // índice do vértice do grafo guardado no heap
    int prio;  // número que representa a prioridade (distância) do item
} item;

// Heap de mínimo (encontrar a menor distância entre os vértices)
typedef struct _fp{
    item *v;     // vetor de itens (representa uma árvore)
    int *indice; // vetor de posições
    int uso;     // número de elementos no vetor
    int alocado; // tamanho total do vetor
} fp;

typedef fp* p_fp;

/** Cria uma fila de prioridades (heap).
 * 
 *  Recebe o tamanho da fila de prioridades e retorna um ponteiro para ela.
 */
p_fp cria_fp(int tam);

/** Mantém o heap organizado na inserção, subindo o item inserido se sua prioridade
 *  for menor que a do seu pai.
 * 
 *  Recebe um heap e a posição a partir da qual deve subir e não retorna.
 */
void sobe_no_heap(p_fp heap, int pos);

/* Semelhante a sobe_no_heap(), mas atua na remoção e compara com os filhos. */
void desce_no_heap(p_fp heap, int pos);

/** Insere um item no heap.
 * 
 *  Recebe o heap e o valor e a prioridade do item a ser inserido e não retorna nada.
 */
void insere(p_fp heap, int valor, int prio);

/** Extrai o item de menor prioridade do heap.
 * 
 *  Recebe o heap e retorna o valor do item removido.
 */
int extrai(p_fp heap);

/** Muda a prioridade de um item (na posição n) no heap.
 * 
 *  Recebe um heap, uma posição n e a nova prioridade e não retorna nada.
 */
void muda_prioridade(p_fp heap, int pos, int nova_prio);

/** Encontra a prioridade de um item no heap.
 * 
 *  Recebe o heap e o valor do item e retorna sua prioridade.
 */
int prioridade(p_fp heap, int valor);

/** Libera a memória utilizada pela fila de prioridade (heap).
 *  
 *  Recebe um heap e não retorna nada.
 */
void libera_fp(p_fp heap);

/** Retorna se um heap está vazio.
 * 
 *  Recebe o heap e retorna 1 se estiver vazio e 0 se não.
 */
int heap_vazio(p_fp heap);

#endif