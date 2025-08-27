#include <stdio.h>
#include <stdlib.h>
#include "backtracking.h"

// Documentações em "backtracking.h"

circuito* le_circuitos(int n_circuitos, int n_alavancas){
    circuito *vet_circuitos = (circuito*) malloc(n_circuitos * sizeof(circuito));

    for (int i = 0; i < n_circuitos; i++){
        scanf("%d %d", &(vet_circuitos[i].peso), &(vet_circuitos[i].n_alavancas));

        alavanca *vet_alavancas = (alavanca*) malloc(vet_circuitos[i].n_alavancas * sizeof(alavanca));

        for (int j = 0; j < vet_circuitos[i].n_alavancas; j++)
            scanf(" %c%d", &(vet_alavancas[j].posicao), &(vet_alavancas[j].indice));

        vet_circuitos[i].alavancas = vet_alavancas;
    }

    return vet_circuitos;
}

void libera_circuitos(circuito *vet_circuitos, int n_circuitos){
    for (int i = 0; i < n_circuitos; i++)
        free(vet_circuitos[i].alavancas);
    free(vet_circuitos);
}

void copia_vetor_alavancas(alavanca **dest, alavanca *fonte, int tam){
    alavanca *novo = (alavanca*) malloc(tam * sizeof(alavanca));
    alavanca *temp = *dest;
    for (int i = 0; i < tam; i++)
        novo[i] = fonte[i];
    *dest = novo;
    free(temp);
}

int calcula_improbabilidade_atual(circuito *vet_circuitos, int n_circuitos, alavanca *config){
    int improb = 0;

    for (int i = 0; i < n_circuitos; i++)
        for (int j = 0; j < vet_circuitos[i].n_alavancas; j++)
            if (vet_circuitos[i].alavancas[j].posicao == config[vet_circuitos[i].alavancas[j].indice].posicao){
                improb += vet_circuitos[i].peso;
                break;
            }

    return improb;
}

int calcula_improbabilidade_maxima(circuito *vet_circuitos, int n_circuitos){
    int improb = 0;

    for (int i = 0; i < n_circuitos; i++)
        improb += vet_circuitos[i].peso;

    return improb;
}

/* Função recursiva utilizada para calcular a improbabilidade. 
   Calcula a improbabilidade e modifica o vetor de alavancas. */
void improbabilidadeR(circuito *vet_circuitos, int n_circuitos, int alavanca_atual, int n_alavancas, int *improb_atual, int improb_max, alavanca *config_atual, alavanca **melhor_config, int *continuar){
    if (alavanca_atual >= n_alavancas){
        int improb = calcula_improbabilidade_atual(vet_circuitos, n_circuitos, config_atual);

        if (improb < 9 * improb_max / 10)
            return;

        if (improb == improb_max || improb > *improb_atual){
            *improb_atual = improb;
            copia_vetor_alavancas(melhor_config, config_atual, n_alavancas);

            if (improb == improb_max)
                *continuar = 0;    
        }
        return;
    }

    if (*continuar == 0)
        return;

    config_atual[alavanca_atual].posicao = '-';
    improbabilidadeR(vet_circuitos, n_circuitos, alavanca_atual + 1, n_alavancas, improb_atual, improb_max, config_atual, melhor_config, continuar);

    config_atual[alavanca_atual].posicao = '+';
    improbabilidadeR(vet_circuitos, n_circuitos, alavanca_atual + 1, n_alavancas, improb_atual, improb_max, config_atual, melhor_config, continuar);
}

void encontra_maior_improbabilidade(circuito *vet_circuitos, int n_circuitos, int n_alavancas){
    int improb_atual = 0;
    alavanca *alavancas = (alavanca*) malloc(n_alavancas * sizeof(alavancas));
    alavanca *melhor_config = (alavanca*) malloc(n_alavancas * sizeof(alavancas));
    for (int i = 0; i < n_alavancas; i++)
        alavancas[i].indice = melhor_config[i].indice = i;

    int improb_max = calcula_improbabilidade_maxima(vet_circuitos, n_circuitos);
    int continuar = 1;

    improbabilidadeR(vet_circuitos, n_circuitos, 0, n_alavancas, &improb_atual, improb_max, alavancas, &melhor_config, &continuar);

    printf("%d\n", improb_atual);
    for (int i = 0; i < n_alavancas - 1; i++)
        printf("%c%d ", melhor_config[i].posicao, melhor_config[i].indice);
    printf("%c%d\n", melhor_config[n_alavancas - 1].posicao, melhor_config[n_alavancas - 1].indice);
    
    free(melhor_config);
    free(alavancas);
}