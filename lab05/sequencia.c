#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequencia.h"

// OBS: documentações das funções feitas no arquivo "sequencia.h"

// cria um nó da sequência com a base e a posição dadas
p_no cria_no(char base, int pos){
    p_no p = (p_no) malloc(sizeof(no));
    p->base = base;
    p->pos = pos;
    p->ant = NULL;
    p->prox = NULL;

    return p;
}

// retorna 0 se a lista não está vazia, e diferente de zero se está
int sequencia_vazia(p_sequencia s){
    return s->tam == 0;
}

p_sequencia criar_sequencia(){
    p_sequencia s = (p_sequencia) malloc(sizeof(sequencia));
    s->ini = NULL;
    s->fim = NULL;
    s->tam = 0;

    return s;
}

void destruir_sequencia(p_sequencia s){
    if (!sequencia_vazia(s)){
        p_no aux = s->ini;
        for (p_no atual = s->ini; atual != NULL; atual = aux){
            aux = aux->prox;
            free(atual);
        }
        free(s);
    }
}


p_sequencia adicionar_base(p_sequencia s, char base, int pos){
    p_no p = cria_no(base, pos);
    p_no atual;

    if (pos == 0){ // adicionando no começo
        p->prox = s->ini;

        if (sequencia_vazia(s))
            s->fim = p;
        else
            s->ini->ant = p;

        s->ini = p;
    }
    else if (pos == s->tam){ // adicionando no fim
        p->ant = s->fim;
        s->fim->prox = p;
        s->fim = p;
    }
    else{
        for (atual = s->ini; atual != NULL; atual = atual->prox){
            if (atual->pos == pos){ // achou a posição onde deve inserir
                p->ant = atual->ant;
                p->prox = atual;
                atual->ant->prox = p;
                atual->ant = p;


                break;
            }
        }
    }
    for (atual = p->prox; atual != NULL; atual = atual->prox)
        atual->pos++;

    free(atual);
    s->tam++;
    
    return s;
}

p_sequencia remover_base(p_sequencia s, int pos){
    p_no aux, atual;
    if (pos == 0){
        aux = s->ini;
        s->ini = s->ini->prox;
        s->ini->ant = NULL;
    }
    else if (pos == s->tam - 1){
        aux = s->fim;
        s->fim = s->fim->ant;
        s->fim->prox = NULL;
    }
    else{
        for (aux = s->ini; aux != NULL; aux = aux->prox){
            if (aux->pos == pos){ // achou a posição de onde deve remover
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;

                break;
            }
        }
    }
    for (atual = aux->prox; atual != NULL; atual = atual->prox)
        atual->pos--;

    printf("%c removido de %d\n", aux->base, pos);
    free(aux);
    s->tam--;

    return s;
}

p_sequencia inverter_prefixo(p_sequencia s, int tam){
    p_sequencia nova = criar_sequencia();
    char *vetor = (char*) malloc(s->tam * sizeof(char));
    p_no aux = s->ini;

    for (int i = 0; i < tam && aux != NULL; i++, aux = aux->prox){
        vetor[i] = aux->base; // prefixo não invertido no vetor
        nova = adicionar_base(nova, vetor[i], 0); // adicionando no começo vai inverter
    }

    for (int i = tam; i < s->tam && aux != NULL; i++, aux = aux->prox)
        nova = adicionar_base(nova, aux->base, i);
    

    printf("prefixo");
    for (int i = 0; i < tam; i++)
        printf(" %c", vetor[i]);
    printf(" ->");
    for (aux = nova->ini; aux->pos < tam; aux = aux->prox)
        printf(" %c", aux->base);
    printf("\n");

    free(vetor);

    return nova;
}

p_sequencia inverter_sufixo(p_sequencia s, int tam){
    p_sequencia nova = criar_sequencia();
    char *vetor = (char*) malloc(s->tam * sizeof(char));
    p_no aux = s->fim;
        
    for (int i = 0; i < tam && aux != NULL; i++, aux = aux->ant){
        vetor[i] = aux->base; // sufixo invertido
        nova = adicionar_base(nova, vetor[i], i); // adicionando já invertido
    }

    for (aux = s->ini; aux->pos != s->tam - tam && aux != NULL; aux = aux->prox)
        nova = adicionar_base(nova, aux->base, aux->pos);

    printf("sufixo");
    aux = nova->fim;
    for (int i = 0; i < tam && aux != NULL; i++, aux = aux->ant)
        printf(" %c", aux->base);
    printf(" ->");
    for (int i = 0; i < tam; i++)
        printf(" %c", vetor[i]);
    printf("\n");

    free(vetor);

    return nova;
}

void desloca(p_no no1, int des){
    char temp = no1->base;
    for (p_no atual = no1->prox; atual != NULL && atual->pos != no1->prox->pos + des; atual = atual->prox){
        no1->base = atual->base;
        atual->base = temp;
    }
}

p_sequencia transposicao(p_sequencia s, int ini, int fim, int des){
    p_no atual, troca;
    int i = 0, tam = fim - ini + 1;
    char temp, *subsequencia = (char*) malloc(tam * sizeof(char));

    // encontra as bases para a impressão
    for (atual = s->ini; atual != NULL && atual->pos != fim + 1; atual = atual->prox){
        if (atual->pos <= fim && atual->pos >= ini){
            subsequencia[i] = atual->base;
            i++;
        }
    }

    if (des > 0){
        while (fim != ini - 1){
            for (atual = s->ini; atual->prox != NULL && atual->pos != fim; atual = atual->prox);
            // achou o último nó da subsequência

            for (troca = atual->prox; atual->prox != NULL && atual->pos != fim + des; atual = atual->prox, troca = troca->prox){
                temp = atual->base; // guarda a base do atual
                atual->base = troca->base;
                troca->base = temp;
            }

            fim--;
        }

        printf("subsequencia");
        for (i = 0; i < tam; i++){
            printf(" %c", subsequencia[i]);
        }
        printf(" >> %d\n", des);
    }
    else if (des < 0){
        while (ini != fim + 1){
            for (atual = s->fim; atual->ant != NULL && atual->pos != ini; atual = atual->ant);
            // achou o primeiro nó da subsequência

            for (troca = atual->ant; atual->ant != NULL && atual->pos != ini + des; atual = atual->ant, troca = troca->ant){
                temp = atual->base;
                atual->base = troca->base;
                troca->base = temp;
            }

            ini++;
        }

        printf("subsequencia");
        for (i = 0; i < tam; i++){
            printf(" %c", subsequencia[i]);
        }
        printf(" << %d\n", abs(des));
    }

    free(subsequencia);
    return s;
}

void imprimir_sequencia(p_sequencia s){
    p_no atual;
    printf("sequencia ");
    for (atual = s->ini; atual != NULL; atual = atual->prox)
        printf("%c ", atual->base);
    printf("\n");
}

void escolhe_operacao(p_sequencia *s, char *comando){
    if (!strcmp(comando, "inserir")){
        char base;
        int pos;
        scanf(" %c %d", &base, &pos);
        *s = adicionar_base(*s, base, pos);
        printf("%c inserido em %d\n", base, pos);
    }
    else if(!strcmp(comando, "remover")){
        int pos;
        scanf("%d", &pos);
        *s = remover_base(*s, pos);
    }
    else if(!strcmp(comando, "inverter-prefixo")){
        int tam;
        scanf("%d", &tam);
        p_sequencia nova = inverter_prefixo(*s, tam);
        destruir_sequencia(*s);
        *s = nova;
    }
    else if(!strcmp(comando, "inverter-sufixo")){
        int tam;
        scanf("%d", &tam);
        p_sequencia nova = inverter_sufixo(*s, tam);
        destruir_sequencia(*s);
        *s = nova;
    }
    else if(!strcmp(comando, "transpor")){
        int ini, fim, des;
        scanf("%d %d %d", &ini, &fim, &des);
        *s = transposicao(*s, ini, fim, des);
    }
    else if(!strcmp(comando, "imprimir")){
        imprimir_sequencia(*s);
    }
    else
        return;
}