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
    heap->uso = 0;
    heap->alocado = tam;

    return heap;
}

void troca(item *item_1, item *item_2, int *vet_posicao){
    item temp = *item_1;
    *item_1 = *item_2;
    *item_2 = temp;

    int pos_temp = (*item_1).pos;
    (*item_1).pos = (*item_2).pos;
    (*item_2).pos = pos_temp;

    vet_posicao[(*item_1).valor] = (*item_1).pos;
    vet_posicao[(*item_2).valor] = (*item_2).pos;
}

/* Para manter o heap organizado, se a prioridade de um item é maior que a do seu pai, ele sobe no heap */
void sobe_no_heap(p_fp heap, int pos, int *vet_posicao){
    if (pos > 0 && heap->v[PAI(pos)].prio < heap->v[pos].prio){
        troca(&heap->v[pos], &heap->v[PAI(pos)], vet_posicao);
        sobe_no_heap(heap, PAI(pos), vet_posicao);
    }
}

/* Mesma coisa da função sobe_no_heap(), mas agora comparando um elemento com seus filhos e descendo no heap */
void desce_no_heap(p_fp heap, int pos, int *vet_posicao){
    int maior_filho;

    if (F_ESQ(pos) < heap->uso){
        maior_filho = F_ESQ(pos);

        if (F_DIR(pos) < heap->uso && heap->v[F_ESQ(pos)].prio < heap->v[F_DIR(pos)].prio)
            maior_filho = F_DIR(pos);

        if (heap->v[pos].prio < heap->v[maior_filho].prio){
            troca(&heap->v[pos], &heap->v[maior_filho], vet_posicao);
            desce_no_heap(heap, maior_filho, vet_posicao);
        }
    }
}

void insere(p_fp heap, item item, int *vet_posicao){
    item.pos = heap->uso;
    heap->v[heap->uso] = item;
    heap->uso++;
    sobe_no_heap(heap, heap->uso - 1, vet_posicao);
    vet_posicao[item.valor] = item.pos;
}

item extrai(p_fp heap, int *vet_posicao){
    item item = heap->v[0]; // elemento com a maior prioridade está no começo do vetor
    troca(&heap->v[0], &heap->v[heap->uso - 1], vet_posicao); // coloca o último elemento no começo
    heap->uso--;
    desce_no_heap(heap, 0, vet_posicao); // desce o último elemento arrumando a ordem do heap

    return item;
}

void muda_prioridade(p_fp heap, int pos, int nova_prio, int *vet_posicao){
    if (heap->v[pos].prio < nova_prio){
        heap->v[pos].prio = nova_prio;
        sobe_no_heap(heap, pos, vet_posicao);
    }
    else{
        heap->v[pos].prio = nova_prio;
        desce_no_heap(heap, pos, vet_posicao);
    }
}

void libera_fp(p_fp heap){
    free(heap->v);
    free(heap);
}