#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int main(){
    int tam_dicionario, qtde_palavras;
    scanf("%d %d", &tam_dicionario, &qtde_palavras);

    p_hash dicionario = cria_hash(tam_dicionario);

    for (int i = 0; i < tam_dicionario; i++){
        char palavra_lida[MAX_PALAVRA];
        scanf(" %s", palavra_lida);
        insere_hash(dicionario, palavra_lida);
    }

    for (int i = 0; i < qtde_palavras; i++){
        char palavra_corrigir[MAX_PALAVRA];
        scanf(" %s", palavra_corrigir);
        cor cor = define_cor(dicionario, palavra_corrigir);

        printf("%s: ", palavra_corrigir);
        if (cor == VERDE)
            printf("verde\n");
        else if (cor == AMARELO)
            printf("amarelo\n");
        else
            printf("vermelho\n");
    }

    libera_hash(dicionario);

    return 0;
}