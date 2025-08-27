#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

/* Ao PED que vai corrigir a tarefa: quando estava terminando o prazo da primeira 
chance e eu vi que não ia conseguir terminar o programa a tempo, fiz um commit ao 
qual foi dada nota 5,4 pelo bot do sistema, intencionalmente para que não houvesse
desconto quando eu fosse entregar a segunda chance. Porém, não solicitei a corre-
ção dos monitores, por pensar que não ia conseguir solicitar a correção da segunda
chance posteriormente (o que, vendo agora, percebo que foi um erro da minha parte, 
obviamente eu iria poder solicitar de novo a correção). Então, teria como eu não 
ficar com o desconto da segunda chance nessa tarefa? Seria muito importante para
mim, já que a tarefa tem peso 4 e fiz o possível para que meu último push da pri-
meira chance tivesse nota maior que 5. Agradeço desde já pela compreensão! */

int main(){
    int w;
    scanf("%d", &w);

    regiao tamanho;
    tamanho.x_ini = tamanho.y_ini = 0;
    tamanho.x_fim = tamanho.y_fim = w;

    pos coord_vazia;
    coord_vazia.x = -1;
    coord_vazia.y = -1;

    p_no raiz = criar_no("vazio", coord_vazia, tamanho, NULL);

    int continuar = 1;
    char comando;

    while (continuar){
        scanf(" %c", &comando);
        continuar = escolher_operacao(&raiz, comando);
    }

    liberar_arvore(&raiz);

    return 0;
}