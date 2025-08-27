#ifndef COBRA_H
#define COBRA_H

/** A lista é duplamente ligada, ou seja, com ponteiros para o anterior e para 
 *  o próximo elemento da lista. Além disso, a struct lista tem ponteiros para
 *  o início (cabeça) e o fim da lista. Os nós guardam a posição de cada parte
 *  da cobra na matriz.
 */

typedef struct _coordenada{
    int x;
    int y;
} coordenada;

typedef struct _no* p_no;

typedef struct _no{
    coordenada pos;
    p_no ant;
    p_no prox;
} no;

typedef struct _lista* p_lista;

typedef struct _lista{
    p_no cabeca;
    p_no cauda;
    int tamanho;
} lista;

/** Cria uma matriz de tamanho m x n.
 * 
 *  Recebe m e n e retorna a matriz.
 */
char** cria_matriz(int m, int n);

/** Libera a memória de uma matriz.
 * 
 *  Recebe uma matriz e a quantidade de linhas e não retorna nada.
 */
void libera_matriz(char **matriz, int m);

/** Imprime a matriz ("tabuleiro").
 * 
 *  Recebe uma matriz e não retorna nada.
 */
void imprime_matriz(char **matriz, int m, int n);

/** Cria uma lista vazia.
 * 
 *  Não recebe nada e retorna a lista vazia criada.
 */
p_lista cria_lista(coordenada pos);

/** Destrói uma lista.
 * 
 *  Recebe a lista e não retorna nada.
 */
void libera_lista(p_lista lista);

/** Aumenta a cobra ao comer uma fruta (inserir elemento).
 * 
 *  Recebe uma lista, uma matriz e a próxima posição da cobra e retorna uma nova lista.
 */
p_lista aumenta(p_lista lista, char** matriz, coordenada prox_pos);

/** Insere a cobra na matriz.
 * 
 *  Recebe uma lista e uma matriz e altera a matriz, não retorna nada.
 */
void insere_cobra(p_lista lista, char **matriz);

/** Insere uma fruta na matriz.
 * 
 *  Recebe a posição da fruta e altera a matriz, não retorna nada.
 */
void insere_fruta(coordenada pos, char **matriz);

/** Move a cobra para cima (comando 'w').
 * 
 *  Recebe uma lista, uma matriz ("tabuleiro") e a próxima posição da cobra e altera a matriz.
 *  Retorna 0 se somente move a cobra, 1 se a cobra cresce e -1 se "GAME OVER".
 */
int move_cima(p_lista lista, char **matriz, coordenada prox_pos);

/* Semelhante à 'move_cima' (comando 's') */
int move_baixo(p_lista lista, char **matriz, coordenada prox_pos);

/* Semelhante à 'move_cima' (comando 'a') */
int move_esquerda(p_lista lista, char **matriz, coordenada prox_pos);

/* Semelhante à 'move_cima' (comando 'd') */
int move_direita(p_lista lista, char **matriz, coordenada prox_pos);

/** Decide para onde a cobra deve se mover e realiza o movimento.
 * 
 *  Recebe uma lista, uma matriz, seu tamanho e um comando e altera a matriz.
 *  Retorna 0 se for para continuar o jogo, 1 se "YOU WIN" e -1 se "GAME OVER".
 */
int move(p_lista lista, char **matriz, int m, int n, char comando);


#endif