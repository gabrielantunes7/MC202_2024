#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PACIENTES 100
#define MAX_NOME_PACIENTE 31

typedef struct _paciente{
    char nome[MAX_NOME_PACIENTE];
    char sobrenome[MAX_NOME_PACIENTE];
} paciente;

void le_nomes(int n, paciente vetor[]){ // ler os nomes dos pacientes e guardá-los num vetor
    int under_pos = 0;
    char palavra[MAX_NOME_PACIENTE * 2 + 1];

    for (int i = 0; i < n; i++){
        scanf(" %s", palavra);

        for (int j = 0; j < (int) strlen(palavra); j++)
            if (palavra[j] == '_'){
                under_pos = j;
                break;
            }

        for (int j = 0; j < under_pos; j++)
            vetor[i].nome[j] = palavra[j];

        vetor[i].nome[under_pos] = '\0';

        for (int j = under_pos + 1; j < (int) strlen(palavra); j++)
            vetor[i].sobrenome[j - (under_pos + 1)] = palavra[j];

        vetor[i].sobrenome[(int) strlen(palavra) - (under_pos + 1)] = '\0';
    }
}

void procura_homonimos(int n, char palavra[31], paciente vetor[]){ // procurar os homônimos de um nome dado e printar os nomes encontrados
    for (int i = 0; i < n; i++)
        if (strcmp(palavra, vetor[i].nome) == 0)
            printf("%s_%s\n", vetor[i].nome, vetor[i].sobrenome);
}

void procura_parentes(int n, char palavra[31], paciente vetor[]){ // procurar os parentes de um sobrenome dado e printar os nomes encontrados
    for (int i = 0; i < n; i++)
        if (strcmp(palavra, vetor[i].sobrenome) == 0)
            printf("%s_%s\n", vetor[i].nome, vetor[i].sobrenome);
}

int main(){
    int n;
    paciente pacientes[MAX_PACIENTES];
    char comando[41], nome_busca[MAX_NOME_PACIENTE];

    scanf("%d", &n);
    le_nomes(n, pacientes);
    scanf(" %s %s", comando, nome_busca);

    if (strcmp("homonimos", comando) == 0)
        procura_homonimos(n, nome_busca, pacientes);

    else if (strcmp("parentes", comando) == 0)
        procura_parentes(n, nome_busca, pacientes);

    return 0;
}