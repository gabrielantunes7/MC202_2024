#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"

#define MAX 20

// Documentações em "grafo.h"

p_grafo cria_grafo(int n){
    p_grafo g = (p_grafo) malloc(sizeof(grafo));
    g->n = n;
    g->cidades = (vertice*) calloc(n, sizeof(vertice));
    for (int i = 0; i < n; i++)
        g->cidades[i].nome = (char*) malloc(MAX * sizeof(char));
    g->adj = (p_no*) calloc(n, sizeof(p_no));

    return g;
}

p_no cria_lista(){
    return NULL;
}

void libera_lista(p_no lista){
    if (lista != NULL){
        libera_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(p_grafo g){
    for (int i = 0; i < g->n; i++)
        libera_lista(g->adj[i]);
    free(g->adj);
    for (int i = 0; i < g->n; i++)
        free(g->cidades[i].nome);
    free(g->cidades);
    free(g);
}

p_no insere_na_lista(p_no lista, vertice v, int peso){
    p_no novo = (p_no) malloc(sizeof(no));
    novo->vertice = v;
    novo->peso = peso;
    novo->prox = lista;

    return novo;
}

void insere_aresta(p_grafo g, vertice u, vertice v, int peso){
    g->adj[u.valor] = insere_na_lista(g->adj[u.valor], v, peso);
    g->adj[v.valor] = insere_na_lista(g->adj[v.valor], u, peso);
}

p_no remove_da_lista(p_no lista, vertice u){
    p_no prox;

    if (lista == NULL)
        return NULL;
    else if (lista->vertice.valor == u.valor){
        prox = lista->prox;
        free(lista);
        
        return prox;
    }
    else{
        lista->prox = remove_da_lista(lista->prox, u);

        return lista;
    }
}

void remove_aresta(p_grafo g, vertice u, vertice v){
    g->adj[u.valor] = remove_da_lista(g->adj[u.valor], v);
    g->adj[v.valor] = remove_da_lista(g->adj[v.valor], u);
}

int tem_aresta(p_grafo g, vertice u, vertice v){
    for (p_no aux = g->adj[u.valor]; aux != NULL; aux = aux->prox)
        if (aux->vertice.valor == v.valor)
            return 1;
    
    return 0;
}

item* dijkstra(p_grafo g, vertice ini){
    int v;

    // vetor pai é como um dicionário (tem o valor do vértice e sua prioridade)
    item *pai = (item*) malloc(g->n * sizeof(item));
    p_fp h = cria_fp(g->n);
    for (v = 0; v < g->n; v++){
        pai[v].valor = -1;
        pai[v].prio = INT_MAX;
        insere(h, v, INT_MAX);
    }

    muda_prioridade(h, h->indice[ini.valor], 0);
    pai[ini.valor].valor = ini.valor;
    pai[ini.valor].prio = prioridade(h, ini.valor);

    while (!heap_vazio(h)){
        v = extrai(h);

        if (prioridade(h, v) != INT_MAX)
            for (p_no aux = g->adj[v]; aux != NULL; aux = aux->prox)
                if (prioridade(h, v) + aux->peso < prioridade(h, aux->vertice.valor)){
                    muda_prioridade(h, h->indice[aux->vertice.valor], prioridade(h, v) + aux->peso);
                    pai[aux->vertice.valor].valor = v;
                    // a prioridade, nesse caso, é a distância de x a pai[x]
                    pai[aux->vertice.valor].prio = prioridade(h, v) + aux->peso;
                }
    }

    libera_fp(h);

    return pai;
}

/* Encontra o valor de um vértice num vetor. */
int encontra_valor(p_grafo g, char *nome){
    for (int i = 0; i < g->n; i++)
        if (!strcmp(nome, g->cidades[i].nome))
            return g->cidades[i].valor;
    
    return -1; // se não encontrar
}

p_grafo le_grafo(){
    int n_cidades, n_percursos;
    scanf("%d ", &n_cidades);

    p_grafo g = cria_grafo(n_cidades);

    // lê as cidades e as guarda num vetor
    for (int i = 0; i < n_cidades; i++){
        g->cidades[i].valor = i;
        scanf("%s %d", g->cidades[i].nome, &(g->cidades[i].populacao));
    }

    // lê os percursos e os insere no grafo
    scanf("%d ", &n_percursos);
    for (int i = 0; i < n_percursos; i++){
        char *cidade1 = (char*) malloc(MAX * sizeof(char));
        char *cidade2 = (char*) malloc(MAX * sizeof(char));
        int distancia;
        scanf("%s %s %d", cidade1, cidade2, &distancia);

        int valor_cidade1 = encontra_valor(g, cidade1);
        int valor_cidade2 = encontra_valor(g, cidade2);

        insere_aresta(g, g->cidades[valor_cidade1], g->cidades[valor_cidade2], distancia);

        free(cidade1);
        free(cidade2);
    }

    return g;
}

vertice* encontra_melhores_centros(p_grafo g, int *distancia_max){
    vertice *centros = (vertice*) malloc(2 * sizeof(vertice));

    // inicializando os centros com cidades quaisquer ("chute inicial")
    for (int i = 0; i < 2; i++)
        centros[i] = g->cidades[i];

    // testa todas as combinações de cidades
    for (int i = 0; i < g->n - 1; i++){
        item *distancias_c1 = dijkstra(g, g->cidades[i]);
        for (int j = i + 1; j < g->n; j++){
            item *distancias_c2 = dijkstra(g, g->cidades[j]);

            // encontrar a maior distância para essas duas cidades
            // e comparar com a maior distância geral até agora
            int maior_distancia = 0;
            for (int k = 0; k < g->n; k++){
                int menor_distancia = (int) fminf(distancias_c1[k].prio, distancias_c2[k].prio);
                maior_distancia = (int) fmaxf(maior_distancia, menor_distancia);

                // se a distância já deu maior que distancia_max, não tem como ficar menor ou igual
                if (maior_distancia > *distancia_max)
                    break;
            }

            // se a distância atual é menor que a geral, significa que as
            // cidades atuais são melhor opção para centros

            // se a distância empata, verificar a soma das populações
            if (maior_distancia < *distancia_max || 
            (maior_distancia == *distancia_max && 
            g->cidades[i].populacao + g->cidades[j].populacao > centros[0].populacao + centros[1].populacao)){
                *distancia_max = maior_distancia;
                centros[0] = g->cidades[i];
                centros[1] = g->cidades[j];
            }

            free(distancias_c2);
        }

        free(distancias_c1);
    }

    return centros;
}