#include <stdio.h>
#include <stdlib.h>
#include "cobra.h"

// Documentações no arquivo "cobra.h"

p_no cria_no(coordenada pos){
    p_no p = (p_no) malloc(sizeof(no));
    p->pos = pos;
    p->ant = NULL;
    p->prox = NULL;

    return p;
}

char** cria_matriz(int m, int n){
    char **matriz = (char**) malloc(m * sizeof(char*));
    for (int i = 0; i < m; i++){
        matriz[i] = (char*) malloc(n * sizeof(char));
        for (int j = 0; j < n; j++)
            matriz[i][j] = '_';
    }

    return matriz;
}

void libera_matriz(char **matriz, int m){
    for (int i = 0; i < m; i++)
        free(matriz[i]);
    free(matriz);
}

void imprime_matriz(char **matriz, int m, int n){
    for (int i = 0; i < m; i++){
    printf("%c", matriz[i][0]);
        for (int j = 1; j < n; j++)
            printf(" %c", matriz[i][j]);
        printf("\n");
    }
    printf("\n");
}

p_lista cria_lista(coordenada pos_inicial){
    p_lista lista = (p_lista) malloc(sizeof(struct _lista));
    p_no inicio = cria_no(pos_inicial);
    lista->cabeca = inicio;
    lista->cauda = inicio;
    lista->tamanho = 1;

    return lista;
}

int lista_vazia(p_lista lista){
    return lista->tamanho == 0;
}

void destroi_lista(p_no cabeca){
    if (cabeca != NULL){
        destroi_lista(cabeca->prox);
        free(cabeca);
    }
}

void libera_lista(p_lista lista){
    if (!lista_vazia(lista)){
        destroi_lista(lista->cabeca);
        free(lista);
    }
}

p_lista aumenta(p_lista lista, char** matriz, coordenada prox_pos){
    p_no novo = cria_no(prox_pos);
    novo->prox = lista->cabeca;
    lista->cabeca = novo;
    lista->tamanho++;
    matriz[prox_pos.x][prox_pos.y] = '#';

    return lista;
}

void insere_cobra(p_lista lista, char **matriz){
    coordenada pos_inicial = lista->cabeca->pos;
    matriz[pos_inicial.x][pos_inicial.y] = '#';
}

void insere_fruta(coordenada pos, char **matriz){
    matriz[pos.x][pos.y] = '*';
}

int move_cima(p_lista lista, char **matriz, coordenada prox_pos){
    if (matriz[prox_pos.x][prox_pos.y] == '*'){
        aumenta(lista, matriz, prox_pos);
        return 1; // cresce
    }
    else if (matriz[prox_pos.x][prox_pos.y] == '#')
        return -1; // não conseguiu mover para cima, GAME OVER
    else
        return 0; 
}

int move_baixo(p_lista lista, char **matriz, coordenada prox_pos){
    if (matriz[prox_pos.x][prox_pos.y] == '*'){
        aumenta(lista, matriz, prox_pos);
        return 1;
    }
    else if (matriz[prox_pos.x][prox_pos.y] == '#')
        return -1;
    else
        return 0;
}

int move_esquerda(p_lista lista, char **matriz, coordenada prox_pos){
    if (matriz[prox_pos.x][prox_pos.y] == '*'){
        aumenta(lista, matriz, prox_pos);
        return 1;
    }
    else if (matriz[prox_pos.x][prox_pos.y] == '#')
        return -1;
    else
        return 0;
}

int move_direita(p_lista lista, char **matriz, coordenada prox_pos){
    if (matriz[prox_pos.x][prox_pos.y] == '*'){
        aumenta(lista, matriz, prox_pos);
        return 1;
    }
    else if (matriz[prox_pos.x][prox_pos.y] == '#')
        return -1;
    else
        return 0;
}

int move(p_lista lista, char **matriz, int m, int n, char comando){
    int retorno;
    coordenada prox_pos = lista->cabeca->pos;
    switch(comando){
        case 'w':
            prox_pos.x -= 1;
            if (prox_pos.x < 0) // atravessar o tabuleiro
                prox_pos.x = m - 1;
            
            retorno = move_cima(lista, matriz, prox_pos);
            break;
        case 's':
            prox_pos.x += 1;
            if (prox_pos.x == m)
                prox_pos.x = 0;
            
            retorno = move_baixo(lista, matriz, prox_pos);
            break;
        case 'a':
            prox_pos.y -= 1;
            if (prox_pos.y < 0)
                prox_pos.y = n - 1;
            
            retorno = move_esquerda(lista, matriz, prox_pos);
            break;
        case 'd':
            prox_pos.y += 1;
            if (prox_pos.y == n)
                prox_pos.y = 0;
            
            retorno = move_direita(lista, matriz, prox_pos);
            break;
    }

    if (retorno == -1) // "GAME OVER"
        return -1;
    else if (retorno == 1 && lista->tamanho == m * n) // "YOU WIN"
        return 1; // função "aumenta" já move a cobra, não precisa mover de novo
    else if (retorno == 1) // continuar
        return 0;

    p_no atual = lista->cabeca;
    coordenada aux = atual->pos;
    atual->pos = prox_pos;
    if (matriz[prox_pos.x][prox_pos.y] != '#')
        matriz[prox_pos.x][prox_pos.y] = '#';
    for (atual = lista->cabeca->prox; atual != NULL; atual = atual->prox){
        prox_pos = atual->pos; // guardar a posição para a qual o próximo elemento deve ir 
        atual->pos = aux; // atualiza a posição
        if (matriz[aux.x][aux.y] != '#')
            matriz[aux.x][aux.y] = '#';
        aux = prox_pos;
    }
    matriz[aux.x][aux.y] = '_';

    return 0;
}