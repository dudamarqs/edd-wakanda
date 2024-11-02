#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cidades.h"

Estrada *getEstrada(const char *NomeArquivo) {
    FILE *file = fopen(NomeArquivo, "r");
    if (!file) return NULL; // retorna NULL se o arquivo não for aberto.

    Estrada *estrada = (Estrada *) malloc(sizeof(Estrada));
    if (!estrada) return NULL;

    fscanf(file, "%d", &estrada->T);
    if (estrada->T < 3 || estrada->T > 1000000) {
        fclose(file);
        free(estrada);
        return NULL;
    }    

    fscanf(file, "%d", &estrada->N);
    if (estrada->N < 2 || estrada->N > 1000000) {
        fclose(file);
        free(estrada);
        return NULL;
    }

    estrada->C = (Cidade *) malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        fclose(file);
        free(estrada);
        return NULL;
    }

    // Lê a posição e o nome de cada cidade
    for (int i = 0; i < estrada->N; i++) {
        int posicao;
        char nome[200];

        fscanf(file, "%s %d", nome, &posicao);

        if (posicao <= 0 || posicao >= estrada->T) {
            fclose(file);
            free(estrada->C); // libera memória alocada para cidades.
            free(estrada); // libera memória alocada para estrada.
            return NULL;
        }

        estrada->C[i].Posicao = posicao;
        strcpy(estrada->C[i].Nome, nome); // copia o nome para a estrutura Cidade.
    }

    fclose(file);
    return estrada;
}

double calcularMenorVizinhanca(const char *NomeArquivo) {
    Estrada *estrada = getEstrada(NomeArquivo);
    if (!estrada) return -1;

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N - 1; i++) {
        int distanciaAtual = estrada->C[i + 1].Posicao - estrada->C[i].Posicao;
        double vizinhancaAtual = distanciaAtual / 2.0;

        if (vizinhancaAtual < menorVizinhanca) {
            menorVizinhanca = vizinhancaAtual;
        }
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *NomeArquivo) {
    Estrada *estrada = getEstrada(NomeArquivo);
    if (!estrada) return NULL;

    double menorVizinhanca = estrada->T;
    char *cidadeComMenorVizinhanca = (char *) malloc(200 * sizeof(char)); // aloca memória para armazenar o nome da cidade

    for (int i = 0; i < estrada->N - 1; i++) {
        int distanciaAtual = estrada->C[i + 1].Posicao - estrada->C[i].Posicao;
        double vizinhancaAtual = distanciaAtual / 2.0;

        if (vizinhancaAtual < menorVizinhanca) {
            menorVizinhanca = vizinhancaAtual;
            strcpy(cidadeComMenorVizinhanca, estrada->C[i].Nome); // copia o nome da cidade
        }
    }

    free(estrada->C);
    free(estrada);

    return cidadeComMenorVizinhanca;
}