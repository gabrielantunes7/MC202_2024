#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

void read_vector(int size, int v[]){
    for (int i = 0; i < size; i++)
        scanf("%d", &v[i]);
}

void print_vector(int size, int v[]){
    for (int i = 0; i < size - 1; i++)
        printf("%d ", v[i]);

    printf("%d\n", v[size - 1]);
}

void reverse_vector(int size, int v[]){
    int temp;
    int i, j;
    for (i = 0, j = size - 1; i < j; i++, j--){
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}

void partial_sum(int size, int v[]){
    for (int i = 1; i < size; i++)
        v[i] += v[i - 1];
}

int main(){
    int n, vector[MAX];
    scanf("%d", &n);
    read_vector(n, vector);

    partial_sum(n, vector);
    reverse_vector(n, vector);

    print_vector(n, vector);

    return 0;
}