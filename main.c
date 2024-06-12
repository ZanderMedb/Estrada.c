#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "cidades.h"

int main() {
    setlocale(LC_ALL, "");

    char nomeArquivo[256];
    int opcao;

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeArquivo);

    printf("Escolha uma opção:\n");
    printf("1. Calcular menor vizinhança\n");
    printf("2. Encontrar cidade com a menor vizinhança\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
            if (menorVizinhanca < 0) {
                printf("Erro ao processar o arquivo.\n");
            } else {
                printf("Menor vizinhança: %.2f\n", menorVizinhanca);
            }
            break;
        }
        case 2: {
            char* cidade = cidadeMenorVizinhanca(nomeArquivo);
            if (!cidade) {
                printf("Erro ao processar o arquivo.\n");
            } else {
                printf("Cidade com a menor vizinhança: %s\n", cidade);
                free(cidade);
            }
            break;
        }
        default:
            printf("Opção inválida.\n");
    }

    return 0;
}
