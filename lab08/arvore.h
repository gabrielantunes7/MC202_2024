#ifndef ARVORE_H
#define ARVORE_H
#define MAX 11

enum direcao {NO, NE, SO, SE, NA}; // NA = sem direção

typedef struct _pos{
    int x; // coordenada em x
    int y; // coordenada em y
} pos;

typedef struct _regiao{
    int x_ini; 
    int x_fim;
    // x_fim - x_ini + 1 = tamanho em x da região

    int y_ini;
    int y_fim;
    // y_fim - y_ini + 1 = tamanho em y da região
    
} regiao;

typedef struct _no* p_no; // ponteiro para um nó

typedef struct _no{
    char nome[MAX]; // nome da cidade
    pos coord;      // coordenada da cidade
    regiao tam;     // tamanho da região
    p_no pai;       // pai do nó, necessário para a remoção
    p_no NO;        // nó noroeste
    p_no NE;        // nó nordeste
    p_no SO;        // nó sudoeste
    p_no SE;        // nó sudeste
} no;

/** Cria um nó.
 * 
 *  Recebe um nome, uma coordenada e um tamanho e retorna o nó criado.
 *  Se o nó é interno/está vazio, nome = "vazio" e coord = (-1, -1).
 */
p_no criar_no(char nome[], pos coord, regiao tam, p_no pai);

/** Libera a memória utilizada por uma árvore.
 * 
 *  Recebe uma raiz e não retorna nada.
 */
void liberar_arvore(p_no *raiz_ref);

/** Insere um nó na árvore, mantendo a propriedade de busca.
 * 
 *  Recebe uma raiz, uma coordenada, um nome e o tamanho da raiz e retorna a raiz modificada.
 */
p_no inserir_no(p_no raiz, pos coord, char nome[], regiao tam, p_no pai);

/** Busca um ponto na árvore. 
 * 
 *  Recebe uma raiz e uma coordenada e retorna o nó encontrado (ou NULL).
 */
p_no busca_por_ponto(p_no raiz, pos coord);

/** Busca pontos numa região.
 * 
 *  Recebe uma raiz, uma coordenada (centro da região) e um raio não retorna nada,
 *  mas imprime as cidades encontradas na região.
 */
void busca_por_regiao(p_no raiz, pos coord, int raio);

/** Remove um nó da árvore.
 * 
 *  Recebe uma raiz, a coordenada de onde deve ser removido e um nó auxiliar para
 *  guardar as informações do nó removido e retorna a raiz modificada.
 */
p_no remover_no(p_no raiz, pos coord, p_no *removido);

/** Escolhe a operação que será feita.
 * 
 *  Recebe uma raiz e um caractere de comando e retorna 0 se o programa deve ser encerrado.
 */
int escolher_operacao(p_no *raiz_ref, char comando);

#endif