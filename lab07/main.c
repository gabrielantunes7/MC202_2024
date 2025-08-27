#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "arvore.h"
#define MAX 5000

int main(){
    p_no raiz;
    char *expressao = (char*) malloc(MAX * sizeof(char));
    scanf("%s", expressao);
    raiz = inserir_expressao(expressao);
    in_ordem(raiz);
    puts("");
    raiz = de_morgan(raiz);
    in_ordem(raiz);
    puts(""); // pular uma linha
    raiz = simplificar_expressao(raiz);
    in_ordem(raiz);
    puts("");
    free(expressao);
    liberar_arvore(raiz);
    
    return 0;
}