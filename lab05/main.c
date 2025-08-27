#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequencia.h"
#define COMANDO 17

int main(){
    p_sequencia dna = criar_sequencia();
    char *comando = (char*) malloc(COMANDO * sizeof(char));
    
    while (1){
        scanf(" %s", comando);
        if (!strcmp(comando, "sair"))
            break;
        else
            escolhe_operacao(&dna, comando);
    }


    free(comando);
    destruir_sequencia(dna);

    return 0;
}