#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "lista.h"

int main(){
    int conta_insercao = 0;
    int tam_cache, qtde_elem, qtde_acessos;
    scanf("%d %d %d", &tam_cache, &qtde_elem, &qtde_acessos);

    // vetor auxiliar para ler os elementos dos acessos
    item *aux = (item*) malloc(qtde_acessos * sizeof(item));

    // vetor de listas ligadas auxiliar para definir as prioridades

    // foram utilizadas listas ligadas pela rapidez em acessar as informações
    
    // como há ponteiros para o início e para o fim, as operações feitas nas
    // listas são em O(1)
    p_lista *vetor_listas = (p_lista*) malloc(qtde_elem * sizeof(p_lista));
    for (int i = 0; i < qtde_elem; i++)
        vetor_listas[i] = cria_lista();

    // cada posição do vetor indica a posição do elemento no cache
    // ex: se posicoes[3] == 2, o elemento de valor 3 está na posição 2 do cache
    int *posicoes = (int*) malloc(qtde_elem * sizeof(int));
    for (int i = 0; i < qtde_elem; i++)
        posicoes[i] = -1;

    for (int i = 0; i < qtde_acessos; i++){
        scanf("%d", &aux[i].valor);
        aux[i].prio = i; // sem prioridade
        aux[i].pos = -1; // ainda não inserido no heap

        vetor_listas[aux[i].valor] = adiciona_item(vetor_listas[aux[i].valor], aux[i]);
    }

    for (int i = 0; i < qtde_elem; i++)
        vetor_listas[i] = define_prioridades(vetor_listas[i]);
    
    p_fp cache = cria_fp(tam_cache);

    // define a prioridade dos itens antes de colocá-los no heap
    for (int i = 0; i < qtde_acessos; i++){
        aux[i].prio = vetor_listas[aux[i].valor]->ini->item.prio;
        if (posicoes[aux[i].valor] == -1){ // se não tem um elemento de mesmo valor no cache
            if (cache->uso >= cache->alocado){ // se o cache está cheio
                item extraido = extrai(cache, posicoes);
                posicoes[extraido.valor] = -1;
            }
            insere(cache, aux[i], posicoes);
            conta_insercao++;
        }
        else // substitui o elemento já presente no cache pelo elemento de mesmo valor
            muda_prioridade(cache, posicoes[aux[i].valor], aux[i].prio, posicoes);
        
        vetor_listas[aux[i].valor] = remove_item(vetor_listas[aux[i].valor]);
    }

    printf("%d\n", conta_insercao);

    for (int i = 0; i < qtde_elem; i++)
        destroi_lista(vetor_listas[i]);
    free(vetor_listas);
    free(posicoes);
    free(aux);
    libera_fp(cache);

    return 0;
}