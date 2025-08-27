#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// Documentações no arquivo "lista.h"

p_no cria_no(char *palavra){
    p_no p = (p_no) malloc(sizeof(no));
    strcpy(p->palavra, palavra);
    p->prox = NULL;

    return p;
}

int lista_vazia(p_lista l){
    return l->ini == NULL;
}

p_lista cria_lista(){
    p_lista l = (p_lista) malloc(sizeof(lista));
    l->ini = NULL;

    return l;
}

void libera_lista(p_lista l){
    if (!lista_vazia(l)){
        p_no aux = l->ini;
        for (p_no atual = l->ini; atual != NULL; atual = aux){
            aux = aux->prox;
            free(atual);
        }
    }
    free(l);
}

p_lista insere_lista(p_lista l, char *palavra){
    p_no p = cria_no(palavra);

    // insere no início
    p->prox = l->ini;
    l->ini = p;

    return l;
}