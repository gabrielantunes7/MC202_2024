#ifndef BATCOMPUTADOR_H
#define BATCOMPUTADOR_H

typedef struct _bat_memoria{
    int *bat_dados;
    int bat_alocado;
    int bat_uso;
} bat_memoria;

typedef bat_memoria *p_bat_memoria;

p_bat_memoria cria_bat_memoria();
void destroi_bat_memoria(p_bat_memoria v);
void bat_alloc(p_bat_memoria v, int tam, int *lista);
void bat_free(p_bat_memoria v, int endereco);
void bat_print(p_bat_memoria v, int endereco);
void bat_uso(p_bat_memoria v);
void escolhe_bat_operacao(p_bat_memoria v, char *comando);

#endif