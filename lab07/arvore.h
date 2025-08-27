#ifndef ARVORE_H
#define ARVORE_H

enum lado {ESQUERDA, DIREITA};

typedef struct _no* p_no; // ponteiro para um nó

typedef struct _no{
    char valor; // valor armazenado no nó da árvore (caractere da expressão)
    p_no esq;   // ponteiro para o filho esquerdo
    p_no dir;   // ponteiro para o filho direito
} no;

/** Cria uma árvore.
 * 
 *  Recebe um valor, um nó esquerdo e um nó direito e retorna a raiz da árvore.
 */
p_no criar_arvore(char x, p_no esq, p_no dir);

/** Libera a memória utilizada por uma árvore.
 *  
 *  Recebe a raiz de uma árvore e não retorna nada.
 */
void liberar_arvore(p_no raiz);

/** Insere um elemento numa árvore.
 *  
 *  Recebe uma raiz e o elemento a ser inserido e retorna a raiz após a inserção.
 */
p_no inserir_elemento(p_no raiz, char valor, enum lado lado);

/** Percorre uma árvore com o método "inordem".
 *  
 *  Recebe a raiz de uma árvore e não retorna nada.
 */
void in_ordem(p_no raiz);

/** Verifica se um caractere é um operador ('!', '&' ou '|').
 * 
 *  Recebe um caractere e retorna  4 se for ')', 3 se for '(', 2 se for operador
 *  binário, 1 se for unário e 0 se não for.
 */
int operador(char c);

/** Lê e insere uma expressão numa árvore, usando uma pilha para colocar na ordem certa.
 *  Um nó (operador) tem dois filhos (operandos).
 *  
 *  Não recebe nada e retorna a raiz criada.
 */
p_no inserir_expressao(char *expressao);

/** Simplifica uma expressão booleana utilizando os teoremas de De Morgan. 
 *  
 *  Recebe a raiz de uma árvore e devolve a raiz da árvore simplificada.
 */
p_no de_morgan(p_no raiz);

/** Simplifica uma expressão booleana até que se obtenha uma expressão irredutível.
 * 
 *  Recebe a raiz de uma árvore e retorna a raiz da árvore simplificada.
 */
p_no simplificar_expressao(p_no raiz);

#endif