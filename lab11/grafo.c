#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

// Documentações em "grafo.h"

p_grafo cria_grafo(int n){
    p_grafo g = (p_grafo) malloc(sizeof(grafo));
    g->n = n;
    g->adj = (int**) calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
        g->adj[i] = (int*) calloc(n, sizeof(int));
    g->vertice_conectado = -1;

    return g;
}

void destroi_grafo(p_grafo g){
    for (int i = 0; i < g->n; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);
}

void insere_aresta(p_grafo g, int u, int v){
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

void remove_aresta(p_grafo g, int u, int v){
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

int tem_aresta(p_grafo g, int u, int v){
    return g->adj[u][v];
}

p_grafo le_grafo(){
    int n_vertices, n_conexoes, vertice_conectado;
    scanf("%d %d %d", &n_vertices, &n_conexoes, &vertice_conectado);

    p_grafo g = cria_grafo(n_vertices);
    g->vertice_conectado = vertice_conectado;

    for (int i = 0; i < n_conexoes; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        insere_aresta(g, u, v);
    }

    return g;
}

int busca_em_profundidade_verificar_ciclo(p_grafo g, int u, int pai, int *visitados_profundidade, int ini){
    visitados_profundidade[u] = 1;

    for (int v = 0; v < g->n; v++){
        if (tem_aresta(g, u, v)){
            if (!visitados_profundidade[v]){
                if (busca_em_profundidade_verificar_ciclo(g, v, u, visitados_profundidade, ini))
                    return 1;
                }
            else if (v != pai && v == ini)
                return 1;
        }
    }

    return 0;
}

int esta_em_ciclo(p_grafo g, int u, int *visitados_profundidade){
    return busca_em_profundidade_verificar_ciclo(g, u, -1, visitados_profundidade, u);
}

/* Define o estado de um vértice.
Se está num ciclo, lâmpada queimada. 
Se não, se seu pai está queimado ou apagado, lâmpada apagada. Se não, acesa. */
void define_estado(p_grafo g, int w, int *pai, int *visitados_profundidade, estados *vet_estados){
    if (esta_em_ciclo(g, w, visitados_profundidade))
        vet_estados[w] = QUEIMADA;
    else{
        if (vet_estados[pai[w]] == ACESA)
            vet_estados[w] = ACESA;
        else
            vet_estados[w] = APAGADA;
    }
}

void define_estado_primeiro_vertice(p_grafo g, int w, estados *vet_estados){
    int *aux = (int*) calloc(g->n, sizeof(int));

    if (esta_em_ciclo(g, w, aux))
        vet_estados[w] = QUEIMADA;
    else
        vet_estados[w] = ACESA;

    free(aux);
}

/* Ordena a inserção de um elemento na fila de impressão. */
void ordena_fila_impressao(p_fila f, int *vet_distancias, int w){
    int fim;
    if (fila_esta_cheia(f))
        fim = (f->alocado - 2) % f->alocado;
    else
        fim = (f->fim - 2) % f->alocado;

    if (vet_distancias[f->v[fim]] == vet_distancias[w] && f->v[fim] > w){
        while (fim != f->ini && vet_distancias[f->v[fim]] == vet_distancias[w] && f->v[fim] > w){
            troca(&(f->v[fim]), &(f->v[(fim + 1) % f->alocado]));
            fim = (fim - 1) % f->alocado;
        }
    }
}

p_fila busca_em_largura(p_grafo g, int ini, estados *vet_estados, int *vet_distancias){
    int v;
    int *pai = (int*) malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++)
        pai[i] = -1;
    int *visitado = (int*) calloc(g->n, sizeof(int));

    // fila usada para imprimir os vértices na ordem correta
    p_fila fila_imprimir = criar_fila(g->n);
    p_fila f = criar_fila(g->n);

    enfileirar(f, ini);
    enfileirar(fila_imprimir, ini);
    pai[ini] = ini;
    vet_distancias[ini] = 0;
    visitado[ini] = 1;
    define_estado_primeiro_vertice(g, ini, vet_estados);

    while(!fila_esta_vazia(f)){
        v = desenfileirar(f);

        for (int w = 0; w < g->n; w++)
            if (tem_aresta(g, v, w) && !visitado[w]){
                visitado[w] = 1;
                pai[w] = v;
                vet_distancias[w] = vet_distancias[pai[w]] + 1;
                int *visitados_profundidade = (int*) calloc(g->n, sizeof(int));
                define_estado(g, w, pai, visitados_profundidade, vet_estados);
                enfileirar(f, w);
                enfileirar(fila_imprimir, w);
                ordena_fila_impressao(fila_imprimir, vet_distancias, w);
                
                free(visitados_profundidade);
            }
    }

    liberar_fila(f);
    free(visitado);
    free(pai);

    return fila_imprimir;
}

void imprime_caminho(p_grafo g, estados *vet_estados, int *vet_distancias, p_fila fila_imprimir){
    for (int i = 0; i < g->n; i++){
        if (!fila_esta_vazia(fila_imprimir)){
            int u = desenfileirar(fila_imprimir);
            printf("%d a distancia %d: ", u, vet_distancias[u]);
            
            if (vet_estados[u] == ACESA)
                printf("acesa\n");
            else if (vet_estados[u] == APAGADA)
                printf("apagada\n");
            else
                printf("queimada\n");
        }
    }
}