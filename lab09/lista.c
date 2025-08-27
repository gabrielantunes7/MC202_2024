#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


// Documentações no arquivo "lista.h"

p_no cria_no(item item){
    p_no p = (p_no) malloc(sizeof(no));
    p->item = item;
    p->ant = NULL;
    p->prox = NULL;

    return p;
}

int lista_vazia(p_lista l){
    return l->ini == NULL;
}

p_lista cria_lista(){
    p_lista l = (p_lista) malloc(sizeof(lista));
    l->ini = NULL;
    l->fim = NULL;

    return l;
}

void destroi_lista(p_lista l){
    if (!lista_vazia(l)){
        p_no aux = l->ini;
        for (p_no atual = l->ini; atual != NULL; atual = aux){
            aux = aux->prox;
            free(atual);
        }
    }
    free(l);
}

p_lista adiciona_item(p_lista l, item item){
    p_no p = cria_no(item);

    // adicionando no fim
    if (!lista_vazia(l)){
        p->ant = l->fim;
        l->fim->prox = p;
        l->fim = p;
    }
    else{
        l->ini = l->fim = p;
        p->ant = p->prox = NULL;
    }

    return l;
}

p_lista remove_item(p_lista l){
    // remove do começo
    p_no aux = l->ini;
    l->ini = l->ini->prox;

    if (l->ini == NULL)
        l->fim = l->ini;
    else
        l->ini->ant = NULL;

    free(aux);

    return l;
}

p_lista define_prioridades(p_lista l){
    if (!lista_vazia(l)){
        p_no atual;
        for (atual = l->ini; atual->prox != NULL; atual = atual->prox)
            atual->item.prio = atual->prox->item.prio;

        if (atual->prox == NULL)
            atual->item.prio = MAX_PRIO;
    }

    return l;
}