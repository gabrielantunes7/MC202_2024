#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(){
    p_grafo g = le_grafo();

    // vetor que armazena o estado de um vértice (lâmpada acesa, apagada ou queimada)
    // ex: se vet_estados[3] == QUEIMADA, a lâmpada do vértice 3 está num ciclo e queimou
    estados *vet_estados = (estados*) malloc(g->n * sizeof(estados));

    // vetor que armazena a distância de um vértice até o vértice ligado na alimentação
    int *vet_distancias = (int*) malloc(g->n * sizeof(int));

    // vetor que armazena o caminho percorrido em ordem crescente de distância
    p_fila fila_imprimir = busca_em_largura(g, g->vertice_conectado, vet_estados, vet_distancias);

    imprime_caminho(g, vet_estados, vet_distancias, fila_imprimir);

    free(vet_estados);
    free(vet_distancias);
    liberar_fila(fila_imprimir);
    destroi_grafo(g);

    return 0;
}