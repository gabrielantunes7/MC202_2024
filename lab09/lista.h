#ifndef LISTA_H
#define LISTA_H

#include "heap.h"

typedef struct _no* p_no;

/* Um nó é composto de um item, um nó anterior e um próximo (lista dupla) */
typedef struct _no{
    item item;
    p_no ant;
    p_no prox;
} no;

typedef struct _lista* p_lista;

/* A lista tem ponteiros para o início e para o fim, para facilitar inserção e remoção */
typedef struct _lista{
    p_no ini;
    p_no fim;
} lista;

/** Cria uma lista ligada vazia.
 * 
 *  Não recebe nada e retorna a lista vazia.
 */
p_lista cria_lista();

/** Libera a memória utilizada por uma lista ligada.
 * 
 *  Recebe a lista e não retorna nada.
 */
void destroi_lista(p_lista l);

/** Insere um item no fim de uma lista ligada (em O(1) por conta do ponteiro para o fim).
 * 
 *  Recebe a lista e o item a ser inserido e retorna a lista modificada.
 */
p_lista adiciona_item(p_lista l, item item);

/** Remove um item que já foi adicionado no cache do início de uma lista ligada
 *  (em O(1) por conta do ponteiro para o início).
 * 
 *  Recebe a lista e retorna a lista modificada.
 */
p_lista remove_item(p_lista l);

/** Define as prioridades dos itens na lista. A prioridade de um item é a posição do
 *  seu próximo acesso.
 * 
 *  Recebe a lista e retorna a lista com as prioridades definidas.
 */
p_lista define_prioridades(p_lista l);

#endif