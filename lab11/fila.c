#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

p_fila criar_fila(int tam){
    p_fila f = (p_fila) malloc(sizeof(fila));
    f->ini = f->fim = f->n = 0;
    f->v = (int*) malloc(tam * sizeof(int));
    f->alocado = tam;

    return f;
}

void liberar_fila(p_fila f){
    free(f->v);
    free(f);
}

int fila_esta_vazia(p_fila f){
    return f->n == 0;
}

int fila_esta_cheia(p_fila f){
    return f->n == f->alocado;
}

void enfileirar(p_fila f, int u){
    f->v[f->fim] = u;
    f->fim = (f->fim + 1) % f->alocado;
    f->n++;
}

int desenfileirar(p_fila f){
    int u = f->v[f->ini];
    f->ini = (f->ini + 1) % f->alocado;
    f->n--;

    return u;
}

int desempilhar(p_fila f){
    int u = f->v[f->fim - 1];
    f->fim = (f->fim - 1) % f->alocado;
    f->n--;

    return u;
}

void troca(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}