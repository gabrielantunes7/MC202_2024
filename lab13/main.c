#include <stdio.h>
#include <stdlib.h>
#include "backtracking.h"

int main(){
    int n_circuitos, n_alavancas;
    scanf("%d %d", &n_circuitos, &n_alavancas);

    circuito *circuitos = le_circuitos(n_circuitos, n_alavancas);
    encontra_maior_improbabilidade(circuitos, n_circuitos, n_alavancas);

    libera_circuitos(circuitos, n_circuitos);

    return 0;
}