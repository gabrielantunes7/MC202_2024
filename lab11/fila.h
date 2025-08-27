#ifndef FILA_H
#define FILA_H

typedef struct _fila* p_fila;

typedef struct _fila{
    int *v;           // vetor de vértices da fila
    int ini, fim;     // posições do início e do fim da fila
    int n, alocado;   // número de vértices na fila e total de posições da fila
} fila;

/** Cria uma fila vazia, usada para montar a árvore da expressão.
 * 
 *  Recebe o tamanho da fila e retorna um ponteiro para a fila criada.
 */
p_fila criar_fila(int tam);

/** Destrói a fila, liberando a memória em uso.
 * 
 *  Recebe a fila e não retorna nada.
 */
void liberar_fila(p_fila f);

/** Mostra se uma fila está vazia.
 * 
 *  Recebe a fila e retorna 1 se a fila está vazia e 0 se não está.
 */
int fila_esta_vazia(p_fila f);

/** Mostra se uma fila está cheia.
 * 
 *  Recebe a fila e retorna 1 se a fila está totalmente ocupada.
 */
int fila_esta_cheia(p_fila f);

/** Enfileira um elemento no topo da fila.
 * 
 *  Recebe a fila e um elemento e não retorna nada.
 */
void enfileirar(p_fila f, int u);

/** Desenfileira o elemento do topo da fila.
 * 
 *  Recebe a fila e retorna o elemento desenfileirado.
 */
int desenfileirar(p_fila f);

/** Remove o último elemento da fila.
 * 
 *  Recebe a fila e retorna o elemento removido.
 */
int desempilhar(p_fila f);

/** Troca o valor de dois inteiros.
 * 
 *  Recebe dois inteiros por referência e modifica seus valores (a = b e b = a).
 */
void troca(int *a, int *b);

#endif