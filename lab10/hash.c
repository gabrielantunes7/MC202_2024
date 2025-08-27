#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash.h"

// Documentações em "hash.h"

p_hash cria_hash(int tam_dicionario){
    p_hash t = (p_hash) malloc(sizeof(struct _hash));
    t->vetor = (p_lista*) malloc(tam_dicionario * sizeof(p_lista));
    for (int i = 0; i < tam_dicionario; i++)
        t->vetor[i] = cria_lista();
    t->tam = tam_dicionario;

    return t;
}

void libera_hash(p_hash t){
    for (int i = 0; i < t->tam; i++)
        libera_lista(t->vetor[i]);
    free(t->vetor);
    free(t);
}

/*  Define o hash de uma palavra
    (soma dos caracteres, palavras parecidas próximas) */
int define_hash(char *palavra, int tam_dicionario){
    int n = 0;
    for (int i = 0; i < strlen(palavra); i++)
        n = (256 * n + palavra[i]) % tam_dicionario;

    return n % tam_dicionario;
}

void insere_hash(p_hash t, char *palavra){
    int n = define_hash(palavra, t->tam);
    t->vetor[n] = insere_lista(t->vetor[n], palavra);
}

/* Vê quantos caracteres há de diferença entre duas palavras */
int compara_palavra(char *palavra1, char *palavra2){
    int tam1 = strlen(palavra1);
    int tam2 = strlen(palavra2);
    int menor_tam = (int) fmin(tam1, tam2);
    
    // se uma palavra é dois ou mais caracteres maior que a outra, só pode ser vermelha
    if (abs(tam1 - tam2) >= 2)
        return 2;

    // se a diferença de tamanho é de um caractere, pode ser amarela
    if (abs(tam1 - tam2) == 1){
        int contador = 0;
        
        // verifica se as ordens das letras são diferentes
        // olha as duas primeiras e as duas últimas letras
        for (int i = 0; i < 2; i++)
            if (palavra1[i] != palavra2[i])
                contador++;
        for (int i = tam1 - 1, j = tam2 - 1; i >= tam1 - 2 && j >= tam2 - 2; i--, j--)
            if (palavra1[i] != palavra2[j])
                contador++;

        if (contador == 4)
            return 2;
        
        int aux = 0;
        int *vetor1 = (int*) calloc(26, sizeof(int));
        int *vetor2 = (int*) calloc(26, sizeof(int));
        
        for (int i = 0; i < menor_tam; i++){
            vetor1[palavra1[i] - 'a']++;
            vetor2[palavra2[i] - 'a']++;
        }

        if (menor_tam == tam1)
            for (int i = menor_tam; i < tam2; i++)
                vetor2[palavra2[i] - 'a']++;
        else
            for (int i = menor_tam; i < tam1; i++)
                vetor1[palavra1[i] - 'a']++;
        
        for (int i = 0; i < 26; i++)
            aux += abs(vetor1[i] - vetor2[i]);
        
        free(vetor1);
        free(vetor2);

        if (aux == 1)
            return 1;
        else
            return 2;
    }
        
    int contador = 0;
    for (int i = 0; i < menor_tam; i++){
        if (palavra1[i] != palavra2[i])
            contador++;
        if (contador >= 2)
            break;    
        }
    
    return contador;
}

cor define_cor(p_hash t, char *palavra){
    int min = 1000;
    int indice = define_hash(palavra, t->tam);
    int raio_busca = t->tam / 2;

    // vai no hash da palavra, se min for zero, significa que a palavra é verde
    // não precisa fazer as outras verificações
    for (p_no aux = t->vetor[indice]->ini; aux != NULL; aux = aux->prox){
        int valor = compara_palavra(palavra, aux->palavra);
        if (valor < min)
            min = valor;
    }

    if (min == 0)
        return VERDE;

    for (int i = - raio_busca; i <= raio_busca; i++){
        if (i == 0)
            continue;
        
        int indice_atual = (i + indice + t->tam) % t->tam;

        for (p_no aux = t->vetor[indice_atual]->ini; aux != NULL; aux = aux->prox){
            int valor = compara_palavra(palavra, aux->palavra);
            if (valor < min)
                min = valor;
        }
    }

    if (min == 1)
        return AMARELO;
    
    return VERMELHO;
}