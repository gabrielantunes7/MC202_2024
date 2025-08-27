#ifndef HASH_H
#define HASH_H

#include "lista.h"

typedef enum _cor {VERDE, AMARELO, VERMELHO} cor;

typedef struct _hash* p_hash;

typedef struct _hash{
    p_lista *vetor; // vetor de listas ligadas
    int tam;
} hash;

/** Cria um hash vazio.
 * 
 *  Recebe o tamanho do dicionário (hash) e retorna um ponteiro para o hash criado.
 */
p_hash cria_hash(int tam_dicionario);

/** Libera a memória utilizada pelo hash.
 * 
 *  Recebe o hash a ser liberado e não retorna nada.
 */
void libera_hash(p_hash t);

/** Insere um elemento no hash.
 * 
 *  Recebe o hash e a palavra do elemento a ser inserido e não retorna.
 */
void insere_hash(p_hash t, char *palavra);

/** Compara a palavra dada com as palavras que começam com a mesma letra no hash
 *  e define a cor da palavra dada.
 * 
 *  Recebe o hash e a palavra e retorna a cor definida. 
 */
cor define_cor(p_hash t, char *palavra);

#endif