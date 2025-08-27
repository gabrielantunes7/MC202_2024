#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void le_matriz(int lin, int col, double **matriz){
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            scanf("%lf", &matriz[i][j]);
}

double maximo_vetor(double *vetor, int tam){
    double max = vetor[0];

    for (int i = 0; i < tam - 1; i++)
        for (int j = i + 1; j < tam; j++)
            if (vetor[j] > max)
                max = vetor[j];

    return max;
}

double minimo_vetor(double *vetor, int tam){
    double min = vetor[0];

    for (int i = 0; i < tam - 1; i++)
        for (int j = i + 1; j < tam; j++)
            if (vetor[j] < min)
                min = vetor[j];

    return min;
}

double* nao_normalizado(int dim, int n, double **matriz){
    double *centroide = (double*) malloc(dim * sizeof(double));
    double *somatorio = (double*) calloc(dim, sizeof(double));

    for (int j = 0; j < dim; j++)
        for (int i = 0; i < n; i++)
            somatorio[j] += matriz[i][j];

    for (int i = 0; i < dim; i++)
        centroide[i] = somatorio[i] / n;

    free(somatorio);

    return centroide;
}

double* normalizado_janela(int dim, int n, double **matriz){
    double *max = (double*) malloc(dim * sizeof(double));
    double *min = (double*) malloc(dim * sizeof(double));
    double **transposta = (double**) malloc(dim * sizeof(double*));
    for (int i = 0; i < dim; i++)
        transposta[i] = (double*) malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < dim; j++)
            transposta[j][i] = matriz[i][j];

    for (int i = 0; i < dim; i++){
        max[i] = maximo_vetor(transposta[i], n);
        min[i] = minimo_vetor(transposta[i], n);
    }

    double **matriz_normal = (double**) malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
        matriz_normal[i] = (double*) malloc(dim * sizeof(double));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < dim; j++){
            if (max[j] == min[j])
                matriz_normal[i][j] = 0;
            else
                matriz_normal[i][j] = ((2 * (matriz[i][j] - min[j])) / (max[j] - min[j])) - 1;
        }

    double *centroide = (double*) malloc(dim * sizeof(double));
    double *somatorio = (double*) calloc(dim, sizeof(double));

    for (int j = 0; j < dim; j++)
        for (int i = 0; i < n; i++)
            somatorio[j] += matriz_normal[i][j];

    for (int i = 0; i < dim; i++)
        centroide[i] = somatorio[i] / n;

    free(max);
    free(min);
    free(somatorio);
    for (int i = 0; i < n; i++)
        free(matriz_normal[i]);
    free(matriz_normal);

    return centroide;    
}

double* normalizado(int dim, int n, double **matriz){
    double *norma = (double*) calloc(n, sizeof(double));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < dim; j++)
            norma[i] += matriz[i][j] * matriz[i][j];

        norma[i] = sqrt(norma[i]);
    }

    double **matriz_normal = (double**) malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
        matriz_normal[i] = (double*) malloc(dim * sizeof(double));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < dim; j++)
        matriz_normal[i][j] = matriz[i][j] / norma[i];

    double *centroide = (double*) malloc(dim * sizeof(double));
    double *somatorio = (double*) calloc(dim, sizeof(double));

    for (int j = 0; j < dim; j++)
        for (int i = 0; i < n; i++)
            somatorio[j] += matriz_normal[i][j];

    for (int i = 0; i < dim; i++)
        centroide[i] = somatorio[i] / n;
    
    for (int i = 0; i < n; i++)
        free(matriz_normal[i]);
    free(matriz_normal);
    free(norma);
    free(somatorio);

    return centroide;
}

int main(){
    int d, n;
    scanf("%d %d", &d, &n);

    double **matriz = (double**) malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
        matriz[i] = (double*) malloc(d * sizeof(double));

    le_matriz(n, d, matriz);

    printf("nenhum:");
    for (int i = 0; i < d; i++)
        printf(" %.3lf", nao_normalizado(d, n, matriz)[i]);
    printf("\n");

    printf("janela:");
    for (int i = 0; i < d; i++)
        printf(" %.3lf", normalizado_janela(d, n, matriz)[i]);
    printf("\n");

    printf("normal:");
    for (int i = 0; i < d; i++)
        printf(" %.3lf", normalizado(d, n, matriz)[i]);
    printf("\n");

    return 0;
}