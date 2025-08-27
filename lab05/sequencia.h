#ifndef SEQUENCIA_H
#define SEQUENCIA_H

/** A sequência é uma lista duplamente encadeada com ponteiros para o início e para o fim, 
 *  com cada nó tendo o valor da base e da posição e a sequência tendo um valor de tamanho,
 *  que representa quantos nós estão alocados na lista.
 */

typedef struct _no* p_no;

typedef struct _no{
    char base;
    p_no ant;
    p_no prox;
    int pos;
} no;

typedef struct _sequencia* p_sequencia;

typedef struct _sequencia{
    p_no ini;
    p_no fim;
    int tam;
} sequencia;

/** Cria uma sequência vazia.
 *  
 *  Não recebe nada e retorna um ponteiro para a sequência.
 */
p_sequencia criar_sequencia();

/** Destrói uma sequência, liberando a memória corretamente.
 *  
 *  Recebe uma sequência a ser liberada e não retorna nada.
 */
void destruir_sequencia(p_sequencia s);

/** Adiciona uma base a uma sequência na posição indicada.
 * 
 *  Recebe uma sequência, o valor de uma base e a posição onde adicioná-la e retorna uma nova sequência.
 */
p_sequencia adicionar_base(p_sequencia s, char base, int pos);

/** Remove uma base de uma sequência na posição indicada.
 * 
 *  Recebe uma sequência e a posição de onde remover a base e retorna uma nova sequência.
 */
p_sequencia remover_base(p_sequencia s, int pos);

/** Inverte um prefixo (conjunto de bases no início de uma sequência) de um dado tamanho.
 * 
 *  Recebe uma sequência e o tamanho do prefixo a ser invertido e retorna uma nova sequência.
 */
p_sequencia inverter_prefixo(p_sequencia s, int tam);

/** Inverte um sufixo (conjunto de bases no fim de uma sequência) de um dado tamanho.
 * 
 *  Recebe uma sequência e o tamanho do sufixo a ser invertido e retorna uma nova sequência.
 */
p_sequencia inverter_sufixo(p_sequencia s, int tam);

/** Desloca um conjunto de bases (iniciado por uma certa base e terminado por outra) uma quantidade dada de posições.
 * 
 *  Recebe uma sequência, as posições inicial e final do conjunto e o deslocamento a ser feito (se des < 0, à esquerda; se des > 0, à direita)
 *  e retorna uma nova sequência.
 */
p_sequencia transposicao(p_sequencia s, int ini, int fim, int des);

/** Imprime uma sequência em seu estado atual.
 * 
 *  Recebe uma sequência a ser impressa e não retorna nada.
 */
void imprimir_sequencia(p_sequencia s);

/** Escolhe a operação a ser feita a partir de um comando dado.
 * 
 * Recebe um comando e uma sequência e não retorna nada.
 */
void escolhe_operacao(p_sequencia *s, char *comando);

#endif