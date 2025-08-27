#include <stdio.h>
#include <stdlib.h>

float probabilidade(int n, int x){
    /** calcula a probabilidade de joão ganhar (maria chegar em joão)
     *  
     * caso base 1 (x == 0): maria chegou em joão, probabilidade 1 de ganhar
     * caso base 2 (n == 0): acabaram as jogadas, probabilidade 0
     * 
     * caso geral (p entre 1 e 6, número jogado no dado): se p == x, acertou o número; se p < x, chama a função de novo com uma jogada a menos e p passos a menos 
     * 
     */

    if (x == 0)
        return 1;

    if (n == 0)
        return 0;
    
    float prob = 0.0;

    for (int p = 1; p <= 6; p++){
        if (p == x)
            prob += 1.0 / 6.0;

        else if (p < x)
            prob += (1.0 / 6.0) * probabilidade(n - 1, x - p);
    }
    
    return prob;
}

int main(){
    int n, x;
    scanf("%d %d", &n, &x);

    printf("%.3f\n", probabilidade(n, x));

    return 0;
}