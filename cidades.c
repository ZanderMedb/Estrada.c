#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

int compararCidades(const void *a, const void *b) {
    return ((Cidade *)a)->Posicao - ((Cidade *)b)->Posicao;
}

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        perror("Erro ao alocar memória para estrada");
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d %d", &(estrada->T), &(estrada->N)) != 2) {
        perror("Erro ao ler T e N do arquivo");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    if (estrada->T < 3 || estrada->T > 1000000 || estrada->N < 2 || estrada->N > 10000) {
        perror("Valores de T ou N fora dos limites permitidos");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        perror("Erro ao alocar memória para cidades");
        free(estrada);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        if (fscanf(arquivo, "%d %[^\n]", &(estrada->C[i].Posicao), estrada->C[i].Nome) != 2) {
            perror("Erro ao ler dados das cidades");
            free(estrada->C);
            free(estrada);
            fclose(arquivo);
            return NULL;
        }
    }

    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1.0;

    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    double menorVizinhanca = estrada->T;

    for (int i = 0; i < estrada->N; i++) {
        double inicio = (i == 0) ? 0 : (estrada->C[i].Posicao + estrada->C[i-1].Posicao) / 2.0;
        double fim = (i == estrada->N - 1) ? estrada->T : (estrada->C[i].Posicao + estrada->C[i+1].Posicao) / 2.0;
        double vizinhanca = fim - inicio;

        if (vizinhanca < menorVizinhanca)
            menorVizinhanca = vizinhanca;
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    qsort(estrada->C, estrada->N, sizeof(Cidade), compararCidades);

    double menorVizinhanca = estrada->T;
    int cidadeIndex = -1;

    for (int i = 0; i < estrada->N; i++) {
        double inicio = (i == 0) ? 0 : (estrada->C[i].Posicao + estrada->C[i-1].Posicao) / 2.0;
        double fim = (i == estrada->N - 1) ? estrada->T : (estrada->C[i].Posicao + estrada->C[i+1].Posicao) / 2.0;
        double vizinhanca = fim - inicio;

        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeIndex = i;
        }
    }

    char *nomeCidade = (char *)malloc(256 * sizeof(char));
    if (!nomeCidade) {
        perror("Erro ao alocar memória para nome da cidade");
        free(estrada->C);
        free(estrada);
        return NULL;
    }
    strcpy(nomeCidade, estrada->C[cidadeIndex].Nome);

    free(estrada->C);
    free(estrada);
    return nomeCidade;
}
