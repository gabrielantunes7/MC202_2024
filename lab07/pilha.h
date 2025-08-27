#ifndef PILHA_H
#define PILHA_H

#include "arvore.h"

typedef struct _pilha* p_pilha;

typedef struct _pilha{
    p_no *v;          // vetor de nós da pilha
    int topo;         // posição do topo da pilha
    int alocado;      // quantidade de memória alocada para a pilha
} pilha;

/** Cria uma pilha vazia, usada para montar a árvore da expressão.
 * 
 *  Não recebe nada e retorna um ponteiro para a pilha criada.
 */
p_pilha criar_pilha();

/** Destrói a pilha, liberando a memória em uso.
 * 
 *  Recebe a pilha e não retorna nada.
 */
void liberar_pilha(p_pilha pilha);

/** Aumenta a pilha, quando necessário, dobrando seu tamanho.
 * 
 *  Recebe a pilha e não retorna nada.
 */
void aumentar_pilha(p_pilha pilha);

/** Diminui a pilha, quando necessário (menos de 1/4 em uso), reduzindo o tama-
 *  nho pela metade.
 * 
 *  Recebe a pilha e não retorna nada.
 */
void diminuir_pilha(p_pilha pilha);

/** Empilha um elemento no topo da pilha.
 * 
 *  Recebe a pilha e um elemento e não retorna nada.
 */
void empilhar(p_pilha pilha, p_no no);

/** Desempilha o elemento do topo da pilha.
 * 
 *  Recebe a pilha e retorna o elemento desempilhado.
 */
p_no desempilhar(p_pilha pilha);

#endif