#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 401

// int palindromo(char *palavra, int ini, int fim){
//     if (ini >= fim)
//         return 1;

//     return palavra[ini] == palavra[fim] && palindromo(palavra, ini + 1, fim - 1);
// }

int quase_palindromo(char *palavra, int ini, int fim, int k, int contador){
    if (ini >= fim)
        return contador <= k;

    if (palavra[ini] != palavra[fim])
        return quase_palindromo(palavra, ini + 1, fim - 1, k, contador + 2);

    else
        return quase_palindromo(palavra, ini + 1, fim - 1, k, contador);
}

int main(){
    int k;
    char *palavra = (char*) malloc(MAX * sizeof(char));
    char buffer;
    int contador = 0;

    scanf("%d", &k);
    scanf("%c", &buffer); // jogar fora o \n
    fgets(palavra, MAX, stdin);
    
    if (palavra[strlen(palavra) - 1] == '\n')
        palavra[strlen(palavra) - 1] = '\0';

    if (quase_palindromo(palavra, 0, strlen(palavra) - 1, k, contador))
        printf("sim");

    else
        printf("nao");

    return 0;
}