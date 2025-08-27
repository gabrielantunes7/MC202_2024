#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "pilha.h"

p_no criar_arvore(char x, p_no esq, p_no dir){
    p_no raiz = (p_no) malloc(sizeof(no));
    raiz->valor = x;
    raiz->esq = esq;
    raiz->dir = dir;

    return raiz;
}

void liberar_arvore(p_no raiz){
    if (raiz == NULL)
        return;

    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

p_no inserir_elemento(p_no raiz, char valor, enum lado lado){
    p_no novo = criar_arvore(valor, NULL, NULL);
    if (raiz == NULL)
        return novo;

    if (lado == ESQUERDA){
        novo->dir = raiz->esq;
        raiz->esq = novo;
    }
    else{
        novo->dir = raiz->dir;
        raiz->dir = novo;
    }

    return raiz;
}

void in_ordem(p_no raiz){
    if (raiz != NULL){
        if (operador(raiz->valor) == 2)
            printf("(");
        
        if (operador(raiz->valor) == 1){
            printf("%c", raiz->valor);
            in_ordem(raiz->dir);
        }
        else{
            in_ordem(raiz->esq);
            printf("%c", raiz->valor);
            in_ordem(raiz->dir);
        }

        if (operador(raiz->valor) == 2)
            printf(")");
    }
}

int operador(char c){
    switch (c){
        case ')':
            return 4;
            break;
        case '(':
            return 3;
            break;
        case '&':
            return 2;
            break;
        case '|':
            return 2;
            break;
        case '!':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

/* Determina se um caractere é true ou false ou nenhum dos dois */
int true_ou_false(char c){
    if (c == 'T')
        return 1;
    else if (c == 'F')
        return 0;
    else
        return -1;
}

p_no inserir_expressao(char *expressao){
    char caractere;
    p_no raiz, esq = NULL, dir = NULL;
    p_pilha pilha = criar_pilha();
    p_pilha pilha_operadores = criar_pilha();
    int i = 0;

    while (1){
        caractere = expressao[i];
        
        if (caractere == '\0')
            break;

        int op = operador(caractere);

        if (op == 4){ // fim de uma subexpressão (')')
            // enquanto não chega no fim da pilha ou não chega no início da subexpressão
            while (pilha_operadores->topo != 0 && pilha_operadores->v[pilha_operadores->topo-1]->valor != '('){
                dir = desempilhar(pilha);
                p_no operador = desempilhar(pilha_operadores);

                if (operador->valor == '!'){
                    operador->dir = dir; // operando
                    empilhar(pilha, operador); // coloca na pilha principal
                    
                }
                else{
                    esq = desempilhar(pilha);
                    operador->esq = esq; // operando 1
                    operador->dir = dir; // operando 2
                    empilhar(pilha, operador); // coloca na pilha principal
                }
            }
            p_no abre_parenteses = desempilhar(pilha_operadores); // tirar o '('
            free(abre_parenteses); // para não vazar memória
            
            // quando '!' precede uma operação, não uma variável
            while (pilha_operadores->topo != 0 && pilha_operadores->v[pilha_operadores->topo-1]->valor == '!'){
                dir = desempilhar(pilha);
                p_no operador = desempilhar(pilha_operadores);
                operador->dir = dir;
                empilhar(pilha, operador);
            }
        }
        // se for operando
        else if (op == 0){
            p_no novo = criar_arvore(caractere, NULL, NULL);
            
            // '!' imediatamente aplicado à variável
            if (pilha_operadores->topo != 0 && pilha_operadores->v[pilha_operadores->topo-1]->valor == '!'){
                p_no operador = desempilhar(pilha_operadores);
                operador->dir = novo;
                empilhar(pilha, operador);

                while (pilha_operadores->topo != 0 && pilha_operadores->v[pilha_operadores->topo-1]->valor == '!'){
                    p_no operador = desempilhar(pilha_operadores);
                    operador->dir = desempilhar(pilha);
                    empilhar(pilha, operador);
                }
            }
            else
                empilhar(pilha, novo);
        }
        // se for operador
        else{
            empilhar(pilha_operadores, criar_arvore(caractere, NULL, NULL));
        }

        i++;
    }

    raiz = desempilhar(pilha);

    // se houver dupla negação no início, não seria visitado pelo programa
    // se sobrar algo na pilha de operadores, só pode ser '!'
    while (pilha_operadores->topo != 0)
        if (pilha_operadores->v[pilha_operadores->topo-1]->valor == '!'){
            p_no operador = desempilhar(pilha_operadores);
            operador->dir = raiz;
            raiz = operador;
        }
    
    liberar_pilha(pilha);
    liberar_pilha(pilha_operadores);
    return raiz;
}

p_no de_morgan(p_no raiz){
    if (raiz == NULL)
        return raiz;

    // se a raiz é '!'
    if (operador(raiz->valor) == 1){
        // remove dupla negação
        if (operador(raiz->dir->valor) == 1){
            while (raiz->dir != NULL && operador(raiz->dir->valor) == 1){
                if (operador(raiz->valor) == 1){
                    p_no temp1 = raiz;
                    p_no temp2 = raiz->dir;
                    raiz = raiz->dir->dir;
                    free(temp1);
                    free(temp2);
                }
                else
                    break;
            }
            raiz = de_morgan(raiz);
        }
        // se o '!' está aplicado a uma variável, não fazer nada
        else if (operador(raiz->dir->valor) == 0){
            raiz = raiz;
        }
        else{
            p_no sub_raiz = raiz->dir; // raiz da sub_arvore direita
            free(raiz);
            
            if (operador(sub_raiz->valor) == 2){
                if (sub_raiz->valor == '&')
                    sub_raiz->valor = '|';
                else if (sub_raiz->valor == '|')
                    sub_raiz->valor = '&';

                sub_raiz->esq = criar_arvore('!', NULL, sub_raiz->esq);
                sub_raiz->esq = de_morgan(sub_raiz->esq);
                sub_raiz->dir = criar_arvore('!', NULL, sub_raiz->dir);
                sub_raiz->dir = de_morgan(sub_raiz->dir);
            }
            else
                sub_raiz = de_morgan(sub_raiz);

            return sub_raiz;
        }
    }
    
    if (operador(raiz->valor) == 2){
        raiz->esq = de_morgan(raiz->esq);
        raiz->dir = de_morgan(raiz->dir);
    }

    return raiz;
}

/* Transforma o nó da esquerda na raiz, liberando o outro nó */
p_no trazer_da_esquerda(p_no raiz){
    p_no temp_dir = raiz->dir;
    raiz = raiz->esq;
    // if (temp_dir->esq != NULL)
    //     free(temp_dir->esq);
    // if (temp_dir->dir != NULL)
    //     free(temp_dir->dir);
    liberar_arvore(temp_dir->esq);
    liberar_arvore(temp_dir->dir);
    free(temp_dir);
    
    return raiz;
}

/* Função simétrica à de trazer da esquerda */
p_no trazer_da_direita(p_no raiz){
    p_no temp_esq = raiz->esq;
    raiz = raiz->dir;
    // if (temp_esq->esq != NULL)
    //     free(temp_esq->esq);
    // if (temp_esq->dir != NULL)
    //     free(temp_esq->dir);
    liberar_arvore(temp_esq->esq);
    liberar_arvore(temp_esq->dir);
    free(temp_esq);

    return raiz;
}

/* Transforma '!T' em 'F' e '!F' em 'T' */
p_no inverter_valor(p_no raiz){
    if (raiz->valor == 'T')
        raiz->valor = 'F';
    else if (raiz->valor == 'F')
        raiz->valor = 'T';

    return raiz;
}

/* Verifica se duas expressões são equivalentes */
int equivalentes(p_no exp1, p_no exp2){
    if (exp1 == NULL || exp2 == NULL)
        return 0;

    if (operador(exp1->valor) == 0 && operador(exp2->valor) == 0)
        if (exp1->valor == exp2->valor)
            return 1;
        else
            return 0;
    else if (operador(exp1->valor) == 1 && operador(exp2->valor) == 1)
        if (exp1->dir->valor == exp2->dir->valor)
            return 1;
        else
            return 0;
    else if (operador(exp1->valor) == 2 && operador(exp2->valor) == 2)
        if (exp1->valor != exp2->valor)
            return 0;
        else{
            if (equivalentes(exp1->esq, exp2->esq) && equivalentes(exp1->dir, exp2->dir))
                return 1;
            else if (equivalentes(exp1->esq, exp2->dir) && equivalentes(exp1->dir, exp2->esq))
                return 1;
            else if (equivalentes(exp1->dir, exp2->esq) && equivalentes(exp1->esq, exp2->dir))
                return 1;
            else if (equivalentes(exp1->dir, exp2->dir) && equivalentes(exp1->esq, exp2->esq))
                return 1;
            else
                return 0;
        }
    else
        return 0;
}

p_no simplificar_expressao(p_no raiz){
    if (raiz == NULL)
        return raiz;

    raiz->esq = simplificar_expressao(raiz->esq);
    raiz->dir = simplificar_expressao(raiz->dir);

    if (operador(raiz->valor) == 2){
        if (raiz->valor == '&'){
            // se esquerda e direita são variáveis
            if (operador(raiz->esq->valor) == 0 || operador(raiz->dir->valor) == 0){
                if (raiz->esq->valor == raiz->dir->valor){
                    p_no temp_raiz = raiz;
                    raiz = trazer_da_esquerda(raiz);
                    free(temp_raiz);
                    return raiz;
                }
                else if (true_ou_false(raiz->esq->valor) == -1 && true_ou_false(raiz->dir->valor) == -1)
                    return raiz;
            }
                    
            p_no temp_raiz = raiz;
            if (raiz->esq->valor == 'T')
                raiz = trazer_da_direita(raiz);
            else if (raiz->esq->valor == 'F')
                raiz = trazer_da_esquerda(raiz);
            else if (raiz->dir->valor == 'T')
                raiz = trazer_da_esquerda(raiz);
            else if (raiz->dir->valor == 'F')
                raiz = trazer_da_direita(raiz);
            if (temp_raiz != raiz)
                free(temp_raiz);
        }
        else if (raiz->valor == '|'){
            if (operador(raiz->esq->valor) == 0 || operador(raiz->dir->valor) == 0){
                if (raiz->esq->valor == raiz->dir->valor){
                    p_no temp_raiz = raiz;
                    raiz = trazer_da_esquerda(raiz);
                    free(temp_raiz);
                    return raiz;
                }
                else if (true_ou_false(raiz->esq->valor) == -1 && true_ou_false(raiz->dir->valor) == -1)
                    return raiz;
                }
            
            p_no temp_raiz = raiz;
            if (raiz->esq->valor == 'T')
                raiz = trazer_da_esquerda(raiz);
            else if (raiz->esq->valor == 'F')
                raiz = trazer_da_direita(raiz);
            else if (raiz->dir->valor == 'T')
                raiz = trazer_da_direita(raiz);
            else if (raiz->dir->valor == 'F')
                raiz = trazer_da_esquerda(raiz);
            if (temp_raiz != raiz)
                free(temp_raiz);
        }
    }
    else if (operador(raiz->valor) == 1){
        if (operador(raiz->dir->valor) == 0){
            if (true_ou_false(raiz->dir->valor) == -1)
                return raiz;
            else{
                // traz da direita e libera a raiz
                p_no temp_raiz = raiz;
                raiz = raiz->dir;
                free(temp_raiz);
                raiz = inverter_valor(raiz);
            }
        }
    }

    if (equivalentes(raiz->esq, raiz->dir)){
        p_no temp_raiz = raiz;
        p_no temp_dir = raiz->dir;
        raiz = raiz->esq;
        free(temp_raiz);
        liberar_arvore(temp_dir);
    }

    return raiz;
}