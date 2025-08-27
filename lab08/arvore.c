#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arvore.h"

// Documentações em "arvore.h"

p_no criar_no(char nome[], pos coord, regiao tam, p_no pai){
    p_no no = (p_no) malloc(sizeof(struct _no));
    strcpy(no->nome, nome);
    no->coord = coord;
    no->tam = tam;
    no->pai = pai;
    no->NO = NULL;
    no->NE = NULL;
    no->SO = NULL;
    no->SE = NULL;

    return no;
}

/* Retorna 1 se a raiz não tem filhos (nó folha) e 0 se tem */
int raiz_sem_filhos(p_no raiz){
    return (raiz->NO == NULL && raiz->NE == NULL && raiz->SO == NULL && raiz->SE == NULL);
}

/* Retorna 1 se precisa contrair o nó, ou seja, se, quando houver remoção, só 
sobra um filho não vazio, e 0 sobram mais filhos. */
int precisa_contrair(p_no no){
    int contador = 0;
    if (raiz_sem_filhos(no->NO) && !strcmp(no->NO->nome, "vazio"))
        contador++;
    if (raiz_sem_filhos(no->NE) && !strcmp(no->NE->nome, "vazio"))
        contador++;
    if (raiz_sem_filhos(no->SO) && !strcmp(no->SO->nome, "vazio"))
        contador++;
    if (raiz_sem_filhos(no->SE) && !strcmp(no->SE->nome, "vazio"))
        contador++;
    
    if (contador >= 3)
        return 1;
    else
        return 0;
} 

/* Dado um tamanho a ser dividido e uma direção para onde haverá expansão, define o tamanho da divisão. */
regiao definir_tamanho(regiao tam_dividir, enum direcao direcao){
    regiao tam_novo;

    // tamanho ímpar, divide em retângulos
    if ((tam_dividir.x_fim - tam_dividir.x_ini + 1) % 2 != 0){
        if (direcao == NO){
            tam_novo.x_ini = tam_dividir.x_ini;
            tam_novo.x_fim = (tam_dividir.x_fim + tam_dividir.x_ini) / 2 - 1;
        }
        else if (direcao == NE){
            tam_novo.x_ini = (tam_dividir.x_fim + tam_dividir.x_ini) / 2;
            tam_novo.x_fim = tam_dividir.x_fim;
        }
        else if (direcao == SO){
            tam_novo.x_ini = tam_dividir.x_ini;
            tam_novo.x_fim = (tam_dividir.x_fim + tam_dividir.x_ini) / 2 - 1;
        }
        else{
            tam_novo.x_ini = (tam_dividir.x_fim + tam_dividir.x_ini) / 2;
            tam_novo.x_fim = tam_dividir.x_fim;
        }
    }
    else{
        if (direcao == NO){
            tam_novo.x_ini = tam_dividir.x_ini;
            tam_novo.x_fim = (tam_dividir.x_fim - 1 + tam_dividir.x_ini) / 2;
        }
        else if (direcao == NE){
            tam_novo.x_ini = (tam_dividir.x_fim - 1 + tam_dividir.x_ini) / 2 + 1;
            tam_novo.x_fim = tam_dividir.x_fim;
        }
        else if (direcao == SO){
            tam_novo.x_ini = tam_dividir.x_ini;
            tam_novo.x_fim = (tam_dividir.x_fim - 1 + tam_dividir.x_ini) / 2;
        }
        else{
            tam_novo.x_ini = (tam_dividir.x_fim - 1 + tam_dividir.x_ini) / 2 + 1;
            tam_novo.x_fim = tam_dividir.x_fim;
        }
    }

    if ((tam_dividir.y_fim - tam_dividir.y_ini + 1) % 2 != 0){
        if (direcao == NO){
            tam_novo.y_ini = (tam_dividir.y_fim + tam_dividir.y_ini) / 2;
            tam_novo.y_fim = tam_dividir.y_fim;
        }
        else if (direcao == NE){
            tam_novo.y_ini = (tam_dividir.y_fim + tam_dividir.y_ini) / 2;
            tam_novo.y_fim = tam_dividir.y_fim;
        }
        else if (direcao == SO){
            tam_novo.y_ini = tam_dividir.y_ini;
            tam_novo.y_fim = (tam_dividir.y_fim + tam_dividir.y_ini) / 2 - 1;
        }
        else{
            tam_novo.y_ini = tam_dividir.y_ini;
            tam_novo.y_fim = (tam_dividir.y_fim + tam_dividir.y_ini) / 2 - 1;
        }
    }
    else{
        if (direcao == NO){
            tam_novo.y_ini = (tam_dividir.y_fim - 1 + tam_dividir.y_ini) / 2 + 1;
            tam_novo.y_fim = tam_dividir.y_fim;
        }
        else if (direcao == NE){
            tam_novo.y_ini = (tam_dividir.y_fim - 1 + tam_dividir.y_ini) / 2 + 1;
            tam_novo.y_fim = tam_dividir.y_fim;
        }
        else if (direcao == SO){
            tam_novo.y_ini = tam_dividir.y_ini;
            tam_novo.y_fim = (tam_dividir.y_fim - 1 + tam_dividir.y_ini) / 2;
        }
        else{
            tam_novo.y_ini = tam_dividir.y_ini;
            tam_novo.y_fim = (tam_dividir.y_fim - 1 + tam_dividir.y_ini) / 2;
        }
    }
    
    return tam_novo;
}

/* Define para onde o nó já ocupado deve ser expandido */
enum direcao definir_direcao_expansao(pos coord, regiao tam){
    // Verifica a posição pelo ponto médio do tamanho atual
    if (coord.x < (tam.x_fim + tam.x_ini) / 2 && coord.y >= (tam.y_fim + tam.y_ini) / 2)
        return NO;
    else if (coord.x >= (tam.x_fim + tam.x_ini) / 2 && coord.y >= (tam.y_fim + tam.y_ini) / 2)
        return NE;
    else if (coord.x < (tam.x_fim + tam.x_ini) / 2 && coord.y < (tam.y_fim + tam.y_ini) / 2)
        return SO;
    else
        return SE;
}

/* Na inserção, quando um nó está ocupado, é necessário expandi-lo, dividindo a região novamente. */
p_no expandir_no_NO(p_no no){
    pos coord_vazia = {-1, -1};

    char nome[MAX];
    strcpy(nome, no->nome);
    pos coord = no->coord;

    strcpy(no->nome, "vazio");
    no->coord = coord_vazia;
    
    regiao tam_NO = definir_tamanho(no->tam, NO);
    regiao tam_NE = definir_tamanho(no->tam, NE);
    regiao tam_SO = definir_tamanho(no->tam, SO);
    regiao tam_SE = definir_tamanho(no->tam, SE);

    no->NO = criar_no(nome, coord, tam_NO, no);
    no->NE = criar_no("vazio", coord_vazia, tam_NE, no);
    no->SO = criar_no("vazio", coord_vazia, tam_SO, no);
    no->SE = criar_no("vazio", coord_vazia, tam_SE, no);

    return no;
}

p_no expandir_no_NE(p_no no){
    pos coord_vazia = {-1, -1};

    char nome[MAX];
    strcpy(nome, no->nome);
    pos coord = no->coord;

    strcpy(no->nome, "vazio");
    no->coord = coord_vazia;

    regiao tam_NO = definir_tamanho(no->tam, NO);
    regiao tam_NE = definir_tamanho(no->tam, NE);
    regiao tam_SO = definir_tamanho(no->tam, SO);
    regiao tam_SE = definir_tamanho(no->tam, SE);

    no->NO = criar_no("vazio", coord_vazia, tam_NO, no);
    no->NE = criar_no(nome, coord, tam_NE, no);
    no->SO = criar_no("vazio", coord_vazia, tam_SO, no);
    no->SE = criar_no("vazio", coord_vazia, tam_SE, no);

    return no;
}

p_no expandir_no_SO(p_no no){
    pos coord_vazia = {-1, -1};

    char nome[MAX];
    strcpy(nome, no->nome);
    pos coord = no->coord;

    strcpy(no->nome, "vazio");
    no->coord = coord_vazia;

    regiao tam_NO = definir_tamanho(no->tam, NO);
    regiao tam_NE = definir_tamanho(no->tam, NE);
    regiao tam_SO = definir_tamanho(no->tam, SO);
    regiao tam_SE = definir_tamanho(no->tam, SE);

    no->NO = criar_no("vazio", coord_vazia, tam_NO, no);
    no->NE = criar_no("vazio", coord_vazia, tam_NE, no);
    no->SO = criar_no(nome, coord, tam_SO, no);
    no->SE = criar_no("vazio", coord_vazia, tam_SE, no);

    return no;
}

p_no expandir_no_SE(p_no no){
    pos coord_vazia = {-1, -1};

    char nome[MAX];
    strcpy(nome, no->nome);
    pos coord = no->coord;

    strcpy(no->nome, "vazio");
    no->coord = coord_vazia;

    regiao tam_NO = definir_tamanho(no->tam, NO);
    regiao tam_NE = definir_tamanho(no->tam, NE);
    regiao tam_SO = definir_tamanho(no->tam, SO);
    regiao tam_SE = definir_tamanho(no->tam, SE);

    no->NO = criar_no("vazio", coord_vazia, tam_NO, no);
    no->NE = criar_no("vazio", coord_vazia, tam_NE, no);
    no->SO = criar_no("vazio", coord_vazia, tam_SO, no);
    no->SE = criar_no(nome, coord, tam_SE, no);

    return no;
}

/* Recebe a direção da expansão e escolhe qual das quatro funções utilizar */
p_no expandir_no(p_no no, enum direcao direcao){
    if (direcao == NO)
        return expandir_no_NO(no);
    else if (direcao == NE)
        return expandir_no_NE(no);
    else if (direcao == SO)
        return expandir_no_SO(no);
    else
        return expandir_no_SE(no);
}

/* Encontra a direção do nó em relação a seu pai para que a contração seja realizada */
enum direcao encontrar_direcao_pai(p_no no){
    if (no->pai == NULL) // se for a raiz, a função é diferente
        return NA;
    if (no->pai->NO == no)
        return NO;
    else if (no->pai->NE == no)
        return NE;
    else if (no->pai->SO == no)
        return SO;
    else
        return SE;
}

enum direcao definir_direcao_contracao(p_no no){
    if (!raiz_sem_filhos(no->NO) || strcmp(no->NO->nome, "vazio"))
        return NO;
    else if (!raiz_sem_filhos(no->NE) || strcmp(no->NE->nome, "vazio"))
        return NE;
    else if (!raiz_sem_filhos(no->SO) || strcmp(no->SO->nome, "vazio"))
        return SO;
    else
        return SE;
}

p_no contrair_no_NO(p_no no, enum direcao dir_pai){
    p_no temp = no->NO;
    temp->pai = no->pai;
    temp->tam = no->tam;

    if (dir_pai == NO)
        no->pai->NO = no->NO;
    else if (dir_pai == NE)
        no->pai->NE = no->NO;
    else if (dir_pai == SO)
        no->pai->SO = no->NO;
    else
        no->pai->SE = no->NO;
    
    liberar_arvore(&(no->NE));
    liberar_arvore(&(no->SO));
    liberar_arvore(&(no->SE));
    free(no);

    return temp;
}

p_no contrair_no_NE(p_no no, enum direcao dir_pai){
    p_no temp = no->NE;
    temp->pai = no->pai;
    temp->tam = no->tam;

    if (dir_pai == NO)
        no->pai->NO = no->NE;
    else if (dir_pai == NE)
        no->pai->NE = no->NE;
    else if (dir_pai == SO)
        no->pai->SO = no->NE;
    else
        no->pai->SE = no->NE;
    
    liberar_arvore(&(no->NO));
    liberar_arvore(&(no->SO));
    liberar_arvore(&(no->SE));
    free(no);

    return temp;
}

p_no contrair_no_SO(p_no no, enum direcao dir_pai){
    p_no temp = no->SO;
    temp->pai = no->pai;
    temp->tam = no->tam;

    if (dir_pai == NO)
        no->pai->NO = no->SO;
    else if (dir_pai == NE)
        no->pai->NE = no->SO;
    else if (dir_pai == SO)
        no->pai->SO = no->SO;
    else
        no->pai->SE = no->SO;
    
    liberar_arvore(&(no->NO));
    liberar_arvore(&(no->NE));
    liberar_arvore(&(no->SE));
    free(no);

    return temp;
}

p_no contrair_no_SE(p_no no, enum direcao dir_pai){
    p_no temp = no->SE;
    temp->pai = no->pai;
    temp->tam = no->tam;

    if (dir_pai == NO)
        no->pai->NO = no->SE;
    else if (dir_pai == NE)
        no->pai->NE = no->SE;
    else if (dir_pai == SO)
        no->pai->SO = no->SE;
    else
        no->pai->SE = no->SE;
    
    liberar_arvore(&(no->NO));
    liberar_arvore(&(no->NE));
    liberar_arvore(&(no->SO));
    free(no);

    return temp;
}

p_no contrair_raiz(p_no raiz, enum direcao dir_filho){
    if (dir_filho == NO){
        strcpy(raiz->nome, raiz->NO->nome);
        raiz->coord = raiz->NO->coord;
    }
    else if (dir_filho == NE){
        strcpy(raiz->nome, raiz->NE->nome);
        raiz->coord = raiz->NE->coord;
    }
    else if (dir_filho == SO){
        strcpy(raiz->nome, raiz->SO->nome);
        raiz->coord = raiz->SO->coord;
    }
    else{
        strcpy(raiz->nome, raiz->SE->nome);
        raiz->coord = raiz->SE->coord;
    }

    liberar_arvore(&(raiz->NO));
    liberar_arvore(&(raiz->NE));
    liberar_arvore(&(raiz->SO));
    liberar_arvore(&(raiz->SE));

    return raiz;
}

p_no contrair_no(p_no no, enum direcao dir_filho){
    if (no->pai == NULL)
        return contrair_raiz(no, dir_filho);
    enum direcao dir_pai = encontrar_direcao_pai(no);
    if (dir_filho == NO)
        return contrair_no_NO(no, dir_pai);
    else if (dir_filho == NE)
        return contrair_no_NE(no, dir_pai);
    else if (dir_filho == SO)
        return contrair_no_SO(no, dir_pai);
    else
        return contrair_no_SE(no, dir_pai);
}

void _liberar_arvore(p_no raiz){
    if (raiz == NULL)
        return;
        
    _liberar_arvore(raiz->NO);   
    _liberar_arvore(raiz->NE);   
    _liberar_arvore(raiz->SO);   
    _liberar_arvore(raiz->SE);
    free(raiz);   
}

void liberar_arvore(p_no *raiz_ref){
    _liberar_arvore(*raiz_ref);
    *raiz_ref = NULL;
}

/* Verifica se duas variáveis do tipo pos são iguais */
int poscmp(pos pos1, pos pos2){
    if (pos1.x == pos2.x && pos1.y == pos2.y)
        return 1;
    else
        return 0;
}

p_no inserir_no(p_no raiz, pos coord, char nome[], regiao tam, p_no pai){
    if (raiz == NULL){
        p_no novo = criar_no(nome, coord, tam, pai);

        return novo;
    }

    if (raiz_sem_filhos(raiz) && strcmp(raiz->nome, "vazio") == 0){
        strcpy(raiz->nome, nome);
        raiz->coord = coord;

        return raiz;
    }

    // encontra a posição onde o nó deve ser inserido, mesmo método da busca por ponto,
    // mas com a verificação para ver se o nó é vazio ou não
    if (strcmp(raiz->nome, "vazio") == 0 && coord.x < (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y >= (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        raiz->NO = inserir_no(raiz->NO, coord, nome, definir_tamanho(tam, NO), raiz);
    else if (strcmp(raiz->nome, "vazio") == 0 && coord.x >= (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y >= (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        raiz->NE = inserir_no(raiz->NE, coord, nome, definir_tamanho(tam, NE), raiz);
    else if (strcmp(raiz->nome, "vazio") == 0 && coord.x < (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y < (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        raiz->SO = inserir_no(raiz->SO, coord, nome, definir_tamanho(tam, SO), raiz);
    else if (strcmp(raiz->nome, "vazio") == 0 && coord.x >= (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y < (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        raiz->SE = inserir_no(raiz->SE, coord, nome, definir_tamanho(tam, SE), raiz);
    // se o nó não for vazio, é necessário expandi-lo
    else if (strcmp(raiz->nome, "vazio") != 0 && coord.x < (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y >= (raiz->tam.y_fim + raiz->tam.y_ini) / 2){
        raiz = expandir_no(raiz, definir_direcao_expansao(raiz->coord, raiz->tam));
        raiz->NO = inserir_no(raiz->NO, coord, nome, definir_tamanho(tam, NO), raiz);
    }
    else if (strcmp(raiz->nome, "vazio") != 0 && coord.x >= (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y >= (raiz->tam.y_fim + raiz->tam.y_ini) / 2){
        raiz = expandir_no(raiz, definir_direcao_expansao(raiz->coord, raiz->tam));
        raiz->NE = inserir_no(raiz->NE, coord, nome, definir_tamanho(tam, NE), raiz);
    }
    else if (strcmp(raiz->nome, "vazio") != 0 && coord.x < (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y < (raiz->tam.y_fim + raiz->tam.y_ini) / 2){
        raiz = expandir_no(raiz, definir_direcao_expansao(raiz->coord, raiz->tam));
        raiz->SO = inserir_no(raiz->SO, coord, nome, definir_tamanho(tam, SO), raiz);
    }
    else if (strcmp(raiz->nome, "vazio") != 0 && coord.x >= (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y < (raiz->tam.y_fim + raiz->tam.y_ini) / 2){
        raiz = expandir_no(raiz, definir_direcao_expansao(raiz->coord, raiz->tam));
        raiz->SE = inserir_no(raiz->SE, coord, nome, definir_tamanho(tam, SE), raiz);
    }
   
    return raiz;
}

p_no busca_por_ponto(p_no raiz, pos coord){
    if (raiz == NULL || poscmp(raiz->coord, coord))
        return raiz;

    if (coord.x < (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y >= (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        return busca_por_ponto(raiz->NO, coord);
    else if (coord.x >= (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y >= (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        return busca_por_ponto(raiz->NE, coord);
    else if (coord.x < (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y < (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        return busca_por_ponto(raiz->SO, coord);
    else
        return busca_por_ponto(raiz->SE, coord);
}

/* Define se um disco de centro coord e raio raio intersecta um quadrante (retorna 1 se intersecta) */
int intersecta_quadrante(pos coord, int raio, p_no quad){
    // calcula o ponto mais próximo de um quadrante ao centro do disco
    pos ponto_mais_prox;
    ponto_mais_prox.x = fmax(quad->tam.x_ini, fmin(coord.x, quad->tam.x_fim));
    ponto_mais_prox.y = fmax(quad->tam.y_ini, fmin(coord.y, quad->tam.y_fim));

    pos segmento;
    segmento.x = coord.x - ponto_mais_prox.x;
    segmento.y = coord.y - ponto_mais_prox.y;

    float distancia = sqrt(segmento.x * segmento.x + segmento.y * segmento.y);

    // se a distância entre o ponto mais próximo e o centro do disco for menor que o raio, intersecta
    if (distancia <= (float) raio)
        return 1;

    return 0;
}

void busca_por_regiao(p_no raiz, pos coord, int raio){
    if (raiz == NULL)
        return;

    if (raiz_sem_filhos(raiz)){
        // se encontrou uma cidade, verificar se está dentro da região
        if (raiz->coord.x != -1 && raiz->coord.y != -1){
            pos segmento;
            segmento.x = coord.x - raiz->coord.x;
            segmento.y = coord.y - raiz->coord.y;

            float distancia = sqrt(segmento.x * segmento.x + segmento.y * segmento.y);
            if (distancia <= (float) raio)
                printf(" %s", raiz->nome);
            
            return;
        }
        // chegou num nó folha vazio
        else
            return;
    }

    // se está num nó interno, verificar se intersecta os quadrantes e, se sim, buscar neles
    if (intersecta_quadrante(coord, raio, raiz->NO))
        busca_por_regiao(raiz->NO, coord, raio);

    if (intersecta_quadrante(coord, raio, raiz->NE))
        busca_por_regiao(raiz->NE, coord, raio);

    if (intersecta_quadrante(coord, raio, raiz->SO))
        busca_por_regiao(raiz->SO, coord, raio);

    if (intersecta_quadrante(coord, raio, raiz->SE))
        busca_por_regiao(raiz->SE, coord, raio);
}

p_no remover_no(p_no raiz, pos coord, p_no *removido){
    pos coord_vazia = {-1, -1};

    if (raiz == NULL)
        return raiz;
    
    // encontrou o nó a ser removido
    if (poscmp(coord, raiz->coord)){
        *removido = criar_no(raiz->nome, raiz->coord, raiz->tam, NULL);
        strcpy(raiz->nome, "vazio");
        raiz->coord = coord_vazia;

        if (raiz->pai != NULL)
            return raiz->pai;
        
        return raiz;
    }
    
    // mesmo método da busca por ponto
    if (coord.x < (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y >= (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        raiz = remover_no(raiz->NO, coord, removido);
    else if (coord.x >= (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y >= (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        raiz = remover_no(raiz->NE, coord, removido);
    else if (coord.x < (raiz->tam.x_fim + raiz->tam.x_ini) / 2 && coord.y < (raiz->tam.y_fim + raiz->tam.y_ini) / 2)
        raiz = remover_no(raiz->SO, coord, removido);
    else
        raiz = remover_no(raiz->SE, coord, removido);

    // volta verificando se os nós precisam ser contraídos (somente um filho não vazio)
    if (precisa_contrair(raiz))
        raiz = contrair_no(raiz, definir_direcao_contracao(raiz));

    if (raiz->pai != NULL)
        return raiz->pai;
    
    return raiz;
}

int escolher_operacao(p_no *raiz_ref, char comando){
    switch (comando){
        case 'i':{
            pos coord;
            char nome[MAX];

            scanf("%d %d %s", &coord.x, &coord.y, nome);

            p_no raiz = *raiz_ref;
            *raiz_ref = inserir_no(*raiz_ref, coord, nome, raiz->tam, raiz);
            printf("Cidade %s inserida no ponto (%d,%d).\n", nome, coord.x, coord.y);

            return 1;
        }
        case 'b':{
            pos coord;

            scanf("%d %d", &coord.x, &coord.y);

            p_no busca = busca_por_ponto(*raiz_ref, coord);

            if (busca != NULL)
                printf("Cidade %s encontrada no ponto (%d,%d).\n", busca->nome, busca->coord.x, busca->coord.y);
            else
                printf("Nenhuma cidade encontrada no ponto (%d,%d).\n", coord.x, coord.y);

            return 1;
        }
        case 'o':{
            pos coord;
            int raio;

            scanf("%d %d %d", &coord.x, &coord.y, &raio);

            printf("Cidades a distancia %d de (%d,%d):", raio, coord.x, coord.y);
            busca_por_regiao(*raiz_ref, coord, raio);
            printf("\n");

            return 1;
        }
        case 'r':{
            pos coord;

            scanf("%d %d", &coord.x, &coord.y);
            
            p_no removido = NULL;
            *raiz_ref = remover_no(*raiz_ref, coord, &removido);

            printf("Cidade %s removida do ponto (%d,%d).\n", removido->nome, removido->coord.x, removido->coord.y);

            free(removido);

            return 1;
        }
        case 's':
            printf("Sistema encerrado.\n");
            return 0;
        default:
            return 1;
    }
}
