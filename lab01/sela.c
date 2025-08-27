#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void read_matrix(int lin, int col, long int m[][MAX]){
    for (int i = 0; i < lin; i++)
        for (int j = 0; j < col; j++)
            scanf("%li", &m[i][j]);
}

int find_duplicates(int size, int init_pos, long int value, long int v[]){ // vasculha um vetor por valores iguais ao dado;
    for (int i = init_pos + 1; i < size; i++)                              // se encontra, retorna 1, se nao, 0
        if (v[i] == value)
            return 1;

    return 0;
}

long int find_saddle_point(int lin, int col, long int m[][MAX], int v[2]){
    long int min_lin, max_col;
    int lin_ind = 0, col_ind = 0;
    int i;

    v[0] = v[1] = 0;

    for (i = 0; i < lin; i++){
        min_lin = m[i][0];
    

        for (int j = 0; j < col; j++){
            if (m[i][j] < min_lin){ // encontra minimo da linha
                min_lin = m[i][j];
                col_ind = j;
            }
        }

        if (find_duplicates(col, col_ind, min_lin, m[i]))
            continue;

        max_col = m[0][col_ind];
        for (int k = 0; k < lin; k++){ // encontra maximo da coluna
            if (m[k][col_ind] > max_col){
                max_col = m[k][col_ind];
                lin_ind = k;
            }
        }

        if (min_lin == max_col){ // se minimo linha = maximo coluna, é sela
            v[0] = lin_ind;
            v[1] = col_ind;
            return min_lin;
        }
        
        else
            continue;
    }

    if (i == lin && min_lin != max_col)
        v[0] = v[1] = -1; // nao encontrou sela
    
    return 0;
} 

int main(){
    int m, n;
    long int mat[MAX][MAX];
    int pos[2];
    
    scanf("%d %d", &m, &n);
    read_matrix(m, n, mat);
    long int saddle = find_saddle_point(m, n, mat, pos);

    if (pos[0] == pos[1] && pos[0] == -1)
        printf("nao existe ponto de sela\n");

    else
        printf("(%d, %d) eh ponto de sela com valor %li\n", pos[0], pos[1], saddle);

    return 0;
}