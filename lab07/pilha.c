#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "arvore.h"

#define TAM_INICIAL 8 // tamanho inicial alocado da pilha

// Documentações no arquivo "pilha.h"

p_pilha criar_pilha(){
    p_pilha p = (p_pilha) malloc(sizeof(pilha));
    p->v = (p_no*) malloc(TAM_INICIAL * sizeof(p_no));
    p->alocado = TAM_INICIAL;
    p->topo = 0;

    return p;
}

void liberar_pilha(p_pilha pilha){
    free(pilha->v);
    free(pilha);
}

void aumentar_pilha(p_pilha pilha){
    p_no *temp; // vetor temporário

    temp = pilha->v;
    pilha->alocado *= 2;
    pilha->v = (p_no*) malloc(pilha->alocado * sizeof(p_no));

    for (int i = 0; i < pilha->alocado / 2; i++)
        pilha->v[i] = temp[i];

    free(temp);
}

void diminuir_pilha(p_pilha pilha){
    p_no *temp;

    temp = pilha->v;
    pilha->alocado /= 2;
    pilha->v = (p_no*) malloc(pilha->alocado * sizeof(p_no));

    for (int i = 0; i < pilha->alocado / 2; i++)
        pilha->v[i] = temp[i];

    free(temp);
}

void empilhar(p_pilha pilha, p_no no){
    if (pilha->topo == pilha->alocado)
        aumentar_pilha(pilha);
    
    pilha->v[pilha->topo] = no;
    pilha->topo++;
}

p_no desempilhar(p_pilha pilha){
    if (pilha->topo == 0)
        return NULL;

    pilha->topo--;

    return pilha->v[pilha->topo];
}