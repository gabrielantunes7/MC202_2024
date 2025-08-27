#ifndef LISTA_H
#define LISTA_H

#define MAX_PALAVRA 26 // quantidade máxima de caracteres em uma palavra

typedef struct _no* p_no;

typedef struct _no{
    char palavra[MAX_PALAVRA];
    p_no prox;
} no;

typedef struct _lista* p_lista;

typedef struct _lista{
    p_no ini;
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
void libera_lista(p_lista l);

/** Insere um elemento no início de uma lista ligada.
 * 
 *  Recebe a lista e o elemento a ser inserido e retorna a lista modificada.
 */
p_lista insere_lista(p_lista l, char *palavra);

#endif