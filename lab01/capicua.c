#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

long int invert_int(long int x){
    int temp;
    long int inv = 0; 

    while (x != 0){
        temp = x % 10;
        inv = inv * 10 + temp;
        x /= 10;
    }

    return inv;
}

int is_capicua(long int p){
    long int num = p;
    if (p < 0)
        return 0;

    else if (p == invert_int(num))
        return 1;
    
    else
        return 0;
}

void init_null_vector(long int v[], int n){
    for (int i = 0; i < n; i++)
        v[i] = 0;
}

int main(){
    int n;
    long int k[MAX];

    scanf("%d", &n);

    init_null_vector(k, n);

    for (int i = 0; i < n; i++)
        scanf("%ld", &k[i]);
    
    for (int i = 0; i < n - 1; i++){
        if (is_capicua(k[i]))
            printf("%ld eh capicua\n", k[i]);
        
        else
            printf("%ld nao eh capicua\n", k[i]);
    }

    if (is_capicua(k[n - 1]))
        printf("%ld eh capicua", k[n - 1]);

    else
        printf("%ld nao eh capicua", k[n - 1]);

    return 0;
}