#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main(){
    p_grafo g = le_grafo();
    int maior_distancia = INT_MAX;
    vertice *melhores_centros = encontra_melhores_centros(g, &maior_distancia);

    // se já está em ordem alfabética
    // aparentemente funciona sem a verificação, mas deixei por desencargo de consciência
    if (strcmp(melhores_centros[0].nome, melhores_centros[1].nome) < 0)
        printf("Centros de distribuicao: %s e %s\n", melhores_centros[0].nome, melhores_centros[1].nome);
    else
        printf("Centros de distribuicao: %s e %s\n", melhores_centros[1].nome, melhores_centros[0].nome);

    printf("Distancia de atendimento: %d\n", maior_distancia);

    free(melhores_centros);
    destroi_grafo(g);

    return 0;
}