#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Como o vetor do heap representa uma árvore, os seguintes defines são úteis
#define PAI(i) ((i-1)/2) // posição do pai de um item
#define F_ESQ(i) (2*i+1) // posição do filho esquerdo de um item
#define F_DIR(i) (2*i+2) // posição do filho direito de um item

// Documentações no arquivo "heap.h"

p_fp cria_fp(int tam){
    p_fp heap = (p_fp) malloc(sizeof(fp));
    heap->v = (item*) malloc(tam * sizeof(item));
    heap->indice = (int*) malloc(tam * sizeof(int));
    for (int i = 0; i < tam; i++)
        heap->indice[i] = -1;
    heap->uso = 0;
    heap->alocado = tam;

    return heap;
}

void troca(p_fp heap, item *item_1, item *item_2){
    item temp = *item_1;
    *item_1 = *item_2;
    *item_2 = temp;

    int pos_temp = heap->indice[(*item_1).valor];
    heap->indice[(*item_1).valor] = heap->indice[(*item_2).valor];
    heap->indice[(*item_2).valor] = pos_temp;
}

/* Para manter o heap organizado, se a prioridade de um item é maior que a do seu pai, ele sobe no heap */
void sobe_no_heap(p_fp heap, int pos){
    if (pos > 0 && heap->v[PAI(pos)].prio > heap->v[pos].prio){
        troca(heap, &heap->v[pos], &heap->v[PAI(pos)]);
        sobe_no_heap(heap, PAI(pos));
    }
}

/* Mesma coisa da função sobe_no_heap(), mas agora comparando um elemento com seus filhos e descendo no heap */
void desce_no_heap(p_fp heap, int pos){
    int menor_filho;

    if (F_ESQ(pos) < heap->uso){
        menor_filho = F_ESQ(pos);

        if (F_DIR(pos) < heap->uso && heap->v[F_ESQ(pos)].prio > heap->v[F_DIR(pos)].prio)
            menor_filho = F_DIR(pos);

        if (heap->v[pos].prio > heap->v[menor_filho].prio){
            troca(heap, &heap->v[pos], &heap->v[menor_filho]);
            desce_no_heap(heap, menor_filho);
        }
    }
}

void insere(p_fp heap, int valor, int prio){
    item novo;
    novo.valor = valor;
    novo.prio = prio;
    heap->indice[novo.valor] = heap->uso;
    heap->v[heap->uso] = novo;
    heap->uso++;
    sobe_no_heap(heap, heap->uso - 1);
}

int extrai(p_fp heap){
    item item = heap->v[0]; // elemento com a menor prioridade está no começo do vetor
    troca(heap, &heap->v[0], &heap->v[heap->uso - 1]); // coloca o último elemento no começo
    heap->uso--;
    desce_no_heap(heap, 0); // desce o último elemento arrumando a ordem do heap

    return item.valor;
}

int prioridade(p_fp heap, int valor){
    return heap->v[heap->indice[valor]].prio;
}

void muda_prioridade(p_fp heap, int pos, int nova_prio){
    if (heap->v[pos].prio > nova_prio){
        heap->v[pos].prio = nova_prio;
        sobe_no_heap(heap, pos);
    }
    else{
        heap->v[pos].prio = nova_prio;
        desce_no_heap(heap, pos);
    }
}

void libera_fp(p_fp heap){
    free(heap->indice);
    free(heap->v);
    free(heap);
}

int heap_vazio(p_fp heap){
    return heap->uso == 0;
}