#include <stdio.h>
#include <stdlib.h>
#include "batcomputador.h"
#define COMANDO 10

int main(){
    int qtde;
    char *comando = (char*) malloc(COMANDO * sizeof(char));
    p_bat_memoria memoria = cria_bat_memoria();

    scanf("%d", &qtde);

    for (int i = 0; i < qtde; i++){
        scanf(" %s", comando);
        escolhe_bat_operacao(memoria, comando);
    }

    free(comando);
    destroi_bat_memoria(memoria);

    return 0;
}