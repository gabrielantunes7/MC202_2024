#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobra.h"
#define COMANDO 7

int main(){
    int m, n, resultado = 0;
    char** matriz;
    p_lista cobra;
    char *comando = (char*) malloc(COMANDO * sizeof(char));
    
    // operações iniciais
    scanf("%s ", comando);
    scanf("%d %d", &m, &n);
    matriz = cria_matriz(m, n);

    scanf("%s ", comando);
    coordenada pos_cobra;
    scanf("%d %d", &pos_cobra.x, &pos_cobra.y);
    cobra = cria_lista(pos_cobra);
    insere_cobra(cobra, matriz);

    scanf("%s ", comando);
    coordenada pos_fruta;
    scanf("%d %d", &pos_fruta.x, &pos_fruta.y);
    insere_fruta(pos_fruta, matriz);

    imprime_matriz(matriz, m, n);

    // sequência de operações
    while (!resultado){ // enquanto resultado == 0, continua
        scanf("%s ", comando);

        if (!strcmp(comando, "FRUTA")){
            coordenada pos_fruta;
            scanf("%d %d", &pos_fruta.x, &pos_fruta.y);
            insere_fruta(pos_fruta, matriz);
        }
        else{
            resultado = move(cobra, matriz, m, n, comando[0]);
            if (resultado == -1){
                printf("GAME OVER\n");
                break;
            }
            // OBS: quando o resultado é "GAME OVER", ele acaba o jogo antes
            // de imprimir a matriz (porque imprimiria repetido)
        }

        imprime_matriz(matriz, m, n);
    }

    if (resultado == 1)
        printf("YOU WIN\n");
    
    free(comando);
    libera_matriz(matriz, m);
    libera_lista(cobra);

    return 0;
}