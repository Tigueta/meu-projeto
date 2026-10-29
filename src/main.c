#include <stdio.h>
#include "../include/estruturas.h"

int main() {
    Conta *inicio_contas = NULL;
    int opcao;

    do {
        printf("\n====================================\n");
        printf("    SISTEMA DE CONTROLE BANCARIO\n");
        printf("====================================\n");
        printf("1 - Cadastrar conta no inicio\n");
        printf("2 - Cadastrar conta no final\n");
        printf("3 - Cadastrar conta em uma posicao\n");
        printf("4 - Listar contas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida!\n");
            return 1;
        }

        switch (opcao) {
            case 1:
                cadastrar_inicio(&inicio_contas);
                break;

            case 2:
                cadastrar_final(&inicio_contas);
                break;

            case 3:
                cadastrar_posicao(&inicio_contas);
                break;

            case 4:
                listar_contas(inicio_contas);
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
