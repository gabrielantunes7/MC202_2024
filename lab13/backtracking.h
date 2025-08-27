#ifndef BACKTRACKING_H
#define BACKTRACKING_H

typedef struct _alavanca{
    int indice; 
    char posicao; // se está para cima ou para baixo ('+' ou '-') 
} alavanca;

typedef struct _circuito{
    int peso;
    int n_alavancas;
    alavanca *alavancas; // alavancas conectadas ao circuito
} circuito;


/** Lê a entrada do problema e devolve a configuração dos circuitos.
 * 
 *  Recebe o número de circuitos e de alavancas e retorna um vetor contendo os circuitos
 */
circuito* le_circuitos(int n_circuitos, int n_alavancas);

/** Libera a memória utilizada por um vetor de circuitos.
 * 
 *  Recebe o vetor e a quantidade de circuitos e libera a memória utilizada.
 */
void libera_circuitos(circuito *vet_circuitos, int n_circuitos);

/** Encontra o valor da maior improbabilidade do sistema.
 * 
 *  Recebe um vetor de circuitos, a quantidade de circuitos e a quantidade de
 *  alavancas e calcula e imprime a maior improbabilidade do sistema, além de
 *  imprimir um vetor com a configuração final das alavancas.
 */
void encontra_maior_improbabilidade(circuito *vet_circuitos, int n_circuitos, int n_alavancas);

#endif