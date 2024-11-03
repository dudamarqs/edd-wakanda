#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cidades.h"

Estrada *getEstrada(const char *NomeArquivo) {
    FILE *file = fopen(NomeArquivo, "r");
    if (!file) return NULL;

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        fclose(file);
        return NULL;
    }

    if (fscanf(file, "%d", &estrada->T) != 1 || estrada->T < 3 || estrada->T > 1000000) {
        fclose(file);
        free(estrada);
        return NULL;
    }

    if (fscanf(file, "%d", &estrada->N) != 1 || estrada->N < 2 || estrada->N > 10000) {
        fclose(file);
        free(estrada);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        fclose(file);
        free(estrada);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        if (fscanf(file, "%d %255[^\n]", &estrada->C[i].Posicao, estrada->C[i].Nome) != 2) {
            fclose(file);
            free(estrada->C);
            free(estrada);
            return NULL;
        }

        if (estrada->C[i].Posicao <= 0 || estrada->C[i].Posicao >= estrada->T) {
            fclose(file);
            free(estrada->C);
            free(estrada);
            return NULL;
        }
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