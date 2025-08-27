#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batcomputador.h"
#define MIN 8

p_bat_memoria cria_bat_memoria(){
    /** Aloca o vetor dinâmico "bat_memoria", que representa a memória do bat-computador. Além disso,
     *  inicializa todas as posições com -1, para indicar que estão vazias (como se fosse o "NULL").
     */

    int tam = MIN;
    p_bat_memoria v;
    v = (p_bat_memoria) malloc(sizeof(bat_memoria));
    v->bat_dados = (int*) malloc(tam * sizeof(int));
    v->bat_alocado = tam;
    v->bat_uso = 0;

    for (int i = 0; i < tam; i++)
        v->bat_dados[i] = -1; // -1 = posição vazia

    return v; 
}

void destroi_bat_memoria(p_bat_memoria v){
    free(v->bat_dados);
    free(v);
}

p_bat_memoria duplica_bat_memoria(p_bat_memoria v){
    /* Duplica a memória, criando uma nova memória com o dobro do tamanho e copiando a atual */
    
    int *temp = v->bat_dados; // guarda as informações da memória atual
    v->bat_alocado *= 2;
    v->bat_dados = (int*) malloc(v->bat_alocado * sizeof(int)); // cria uma nova memória com o dobro do tamanho
    for (int i = 0; i < v->bat_alocado; i++){
        if (i < v->bat_alocado / 2)
            v->bat_dados[i] = temp[i]; // coloca as informações de volta na nova memória
        
        else
            v->bat_dados[i] = -1; // inicializa o resto da memória com -1 ("NULL")
    }
    free(temp);

    return v;
}

p_bat_memoria reduz_bat_memoria(p_bat_memoria v){
    /* Reduz a memória pela metade, criando uma nova memória com a metade do tamanho e copiando a atual (basicamente igual à de duplicar) */

    int *temp = v->bat_dados;
    v->bat_alocado /= 2;
    v->bat_dados = (int*) malloc(v->bat_alocado * sizeof(int));
    for (int i = 0; i < v->bat_alocado; i++){
        if (i < v->bat_alocado / 2) // quando reduz a memória, só tem um quarto dela em uso
            v->bat_dados[i] = temp[i];

        else
            v->bat_dados[i] = -1;
    }
    free(temp);

    return v;
}

int tem_espaco(p_bat_memoria v, int tam){
    /* Verifica se há espaço na memória para alocar uma lista de tamanho tam e retorna a posição onde deve ser alocada a lista */

    int i, j = 0, espaco = 0, pos_vazia, tem_espaco = 0; // se não houver espaço, pos_vazia = -1 (não tem posição vazia)

    if (v->bat_alocado == v->bat_uso)
        return -1;

    if (tam >= v->bat_alocado - v->bat_uso)
        return -1;

    for (i = 0; i < v->bat_alocado; i++){
        if (tem_espaco == 1) // tem_espaco é uma flag
            break;

        if (v->bat_dados[i] == -1)
            for (j = i; j < i + tam + 1 && j < v->bat_alocado; j++){
                if (v->bat_dados[j] == -1){
                    espaco++;

                    if (espaco == tam + 1){
                        tem_espaco = 1;
                        break;
                    }

                    continue;
                }

                else{
                    i = j + v->bat_dados[j]; // não há espaço para alocar a lista a partir do endereço i, 
                    espaco = 0;              // então pula para o próximo i depois do tamanho da lista
                    break;
                }
            }

        if (j == v->bat_alocado)
            return -1;
    }

    if (tem_espaco == 1) // encontrou espaço em que cabe a lista de tamanho tam na memória
        pos_vazia = i - 1;

    return pos_vazia;
}

void bat_alloc(p_bat_memoria v, int tam, int *lista){
    /* Verifica se há espaço na memória e, se houver, aloca uma lista, se não, dobra o tamanho da memória */
    
    int pos_vazia = tem_espaco(v, tam);
    while (pos_vazia == -1){
        v = duplica_bat_memoria(v);
        pos_vazia = tem_espaco(v, tam);
    }
    
    // há espaço, alocar a lista na memória
    v->bat_dados[pos_vazia] = tam;
    v->bat_uso++;
    for (int i = pos_vazia + 1; i < pos_vazia + tam + 1; i++){
        v->bat_dados[i] = lista[i - pos_vazia - 1];
        v->bat_uso++;
    }

    printf("%d\n", pos_vazia);
}

void bat_free(p_bat_memoria v, int endereco){
    /* Dado o endereço a liberar, troca os valores da lista por -1 ("NULL") */

    int tam = v->bat_dados[endereco];
    for (int i = endereco; i < endereco + tam + 1; i++){
        v->bat_dados[i] = -1;
        v->bat_uso--;
    }

    // se não há uso de memória depois do primeiro quarto do vetor, reduz a memória pela metade
    if (v->bat_uso <= v->bat_alocado / 4 && v->bat_alocado != MIN){
        int i;
        for (i = v->bat_uso; i < v->bat_alocado; i++)
            if (v->bat_dados[i] != -1)
                break;

        if (i == v->bat_alocado)
            v = reduz_bat_memoria(v);
    }

        
}

void bat_print(p_bat_memoria v, int endereco){
    /* Dado o endereço a imprimir, imprime os valores do vetor a partir dele */
    
    int tam = v->bat_dados[endereco];
    for (int i = endereco + 1; i < endereco + tam + 1; i++)
        printf("%d ", v->bat_dados[i]);

    printf("\n");
}

void bat_uso(p_bat_memoria v){
    /* Quando chamada, imprime o uso da memória, dado guardado na struct */

    printf("%d de %d\n", v->bat_uso, v->bat_alocado);
}

void escolhe_bat_operacao(p_bat_memoria v, char *comando){
    /* A partir de um comando dado, escolhe uma operação a ser feita */

    if (!strcmp(comando, "bat-alloc")){ // usando "!" antes do strcmp porque devolve 0 se é igual
        int tam, *lista;
        scanf("%d", &tam);
        lista = (int*) malloc(tam * sizeof(int));
        for (int i = 0; i < tam; i++)
            scanf("%d", &lista[i]);

        bat_alloc(v, tam, lista);
        free(lista);
    }

    else if (!strcmp(comando, "bat-free")){
        int endereco;
        scanf("%d", &endereco);

        bat_free(v, endereco);
    }

    else if (!strcmp(comando, "bat-print")){
        int endereco;
        scanf("%d", &endereco);

        bat_print(v, endereco);
    }

    else if (!strcmp(comando, "bat-uso"))
        bat_uso(v);

    else
        return; // se operação é inválida, não faz nada
}