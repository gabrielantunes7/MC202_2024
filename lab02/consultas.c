#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME_DOENCA 101
#define MAX_NOME 62
#define MAX_CONSULTAS 100

typedef struct _doenca{
    char cid[4];
    char nome[MAX_NOME_DOENCA];
} doenca;

typedef struct _medico{
    int crm;
    char nome[MAX_NOME];
} medico;

typedef struct _paciente{
    char nome[MAX_NOME];
} paciente;

typedef struct _consulta{
    paciente paciente;
    medico medico;
    doenca doenca; 
} consulta;

void procura_doenca(const char cid_busca[4], char nome_busca[]){
    FILE *fp = fopen("dados/doencas.txt", "r");
    int qtde_doencas;
    char cid[4];
    char nome_doenca_lido[MAX_NOME_DOENCA];

    fscanf(fp, "%d", &qtde_doencas);

    for (int i = 0; i < qtde_doencas; i++){
        fscanf(fp, " %s %[^\n]", cid, nome_doenca_lido);

        if (strcmp(cid, cid_busca) == 0){
            strcpy(nome_busca, nome_doenca_lido);
            fclose(fp);
            break;
        }

    }
}

void procura_medico(const int crm_busca, char nome_busca[]){
    FILE *fp = fopen("dados/medicos.txt", "r");
    int qtde_medicos;
    int crm;
    char nome_medico_lido[MAX_NOME];

    fscanf(fp, "%d", &qtde_medicos);

    for (int i = 0; i < qtde_medicos; i++){
        fscanf(fp, "%d %[^\n]", &crm, nome_medico_lido);

        if (crm == crm_busca){
            strcpy(nome_busca, nome_medico_lido);
            fclose(fp);
            break;
        }

    }
}

void registra_consulta(consulta consultas[], int *pos, const char nome_reg[], const char cid_reg[], const int crm_reg){
    char nome_doenca[MAX_NOME_DOENCA];
    char nome_medico[MAX_NOME_DOENCA];

    strcpy(consultas[*pos].paciente.nome, nome_reg);
    strcpy(consultas[*pos].doenca.cid, cid_reg);
    consultas[*pos].medico.crm = crm_reg;

    procura_doenca(cid_reg, nome_doenca);
    strcpy(consultas[*pos].doenca.nome, nome_doenca);

    procura_medico(crm_reg, nome_medico);
    strcpy(consultas[*pos].medico.nome, nome_medico);

    *pos = *pos + 1;
}

void remove_consulta(consulta consultas[], int *pos, const char nome_rem[]){
    for (int j = 0; j < *pos; j++){
        if (strcmp(nome_rem, consultas[j].paciente.nome) == 0){
            if (j < *pos - 1)
                for (int k = j; k < *pos - 1; k++)
                    consultas[k] = consultas[k + 1];
            
            consultas[*pos - 1] = (consulta){0};
            *pos = *pos - 1;  
            break;
        }
    }
}

void altera_consulta(consulta consultas[], int pos, const char nome_alterar[], const char cid_alterar[4]){
    char nome_doenca[MAX_NOME_DOENCA];

    for (int j = 0; j < pos; j++)
        if (strcmp(consultas[j].paciente.nome, nome_alterar) == 0){
            procura_doenca(cid_alterar, nome_doenca);
            strcpy(consultas[j].doenca.nome, nome_doenca);
            break;
        }
}

int main(){
    char comando[10];
    int qtde_op;
    consulta consultas[MAX_CONSULTAS] = {0};
    int num_consultas = 0;

    scanf(" %s", comando);
    scanf(" %d", &qtde_op);

    if (strcmp(comando, "abrir") == 0){
        while (1){
            scanf(" %s", comando);

            if (strcmp(comando, "registrar") == 0){
                char nome_reg[MAX_NOME];
                char cid_reg[4];
                int crm_reg;

                scanf(" %s %s %d", nome_reg, cid_reg, &crm_reg);
                registra_consulta(consultas, &num_consultas, nome_reg, cid_reg, crm_reg);
            }

            else if (strcmp(comando, "remover") == 0){
                char nome_rem[MAX_NOME];

                scanf(" %s", nome_rem);
                remove_consulta(consultas, &num_consultas, nome_rem);
            }

            else if (strcmp(comando, "alterar") == 0){
                char nome_alterar[MAX_NOME];
                char cid_alterar[4];

                scanf(" %s %s", nome_alterar, cid_alterar);
                altera_consulta(consultas, num_consultas, nome_alterar, cid_alterar);
            }

            else if (strcmp(comando, "fechar") == 0)
                break;
        }
    }

    for (int i = 0; i < num_consultas; i++)
        printf("%s atendido por %s: %s\n", consultas[i].paciente.nome, consultas[i].medico.nome, consultas[i].doenca.nome);

    return 0;
}