#ifndef HEAP_H
#define HEAP_H

#define MAX_PRIO 1000000 // prioridade de um item que não vai mais ser acessado

typedef struct _item{
    int valor; 
    int prio;        // número que representa a prioridade do item
    int pos;         // posição que o item ocupa no heap
} item;

typedef struct _fp{
    item *v;     // vetor de itens (representa uma árvore)
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
 *  for maior que a do seu pai.
 * 
 *  Recebe um heap, a posição a partir da qual deve subir e um vetor de posições e não retorna.
 */
void sobe_no_heap(p_fp heap, int pos, int *vet_posicao);

/* Semelhante a sobe_no_heap(), mas atua na remoção e compara com os filhos. */
void desce_no_heap(p_fp heap, int pos, int *vet_posicao);

/** Insere um item no heap.
 * 
 *  Recebe o heap, o item a ser inserido e um vetor que guarda as posições dos 
 *  itens no heap e não retorna nada.
 */
void insere(p_fp heap, item item, int *vet_posicao);

/** Extrai o item de maior prioridade do heap.
 * 
 *  Recebe o heap e um vetor de posições e retorna o item removido.
 */
item extrai(p_fp heap, int *vet_posicao);

/** Muda a prioridade de um item (na posição n) no heap.
 * 
 *  Recebe um heap, uma posição n, a nova prioridade e um vetor de posições e não retorna nada.
 */
void muda_prioridade(p_fp heap, int pos, int nova_prio, int *vet_posicoes);

/** Libera a memória utilizada pela fila de prioridade (heap).
 *  
 *  Recebe um heap e não retorna nada.
 */
void libera_fp(p_fp heap);

#endif