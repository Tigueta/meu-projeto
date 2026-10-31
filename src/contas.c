/*
 * Nome: Santiago Gabriel Reyes
 * Data: 30/10/26
 * Arquivo: contas.c
 * Descricao: Contem as funcoes de cadastro e consulta de contas bancarias.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/estruturas.h"

void gotoxy(int x, int y);
void cabecalho(char titulo[]);

int codigo_existe(Conta *inicio, int codigo)
{

    while (inicio != NULL)
    {

        if (inicio->codigo_conta == codigo)
        {

            return 1;
        }

        inicio = inicio->prox;
    }

    return 0;
}

int cadastrar_dados(Conta *nova, Conta *inicio)
{

    char entrada[100];

    system("cls");
    cabecalho("CADASTRO DE CONTA BANCARIA");
    gotoxy(5, 10);
    printf("Codigo da conta: ");
    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%d", &nova->codigo_conta) != 1 || nova->codigo_conta <= 0)
    {
        return 0;
    }

    if (codigo_existe(inicio, nova->codigo_conta))
    {
        gotoxy(5, 25);
        printf("Esse codigo ja esta cadastrado!");
        return 0;
    }

    gotoxy(5, 12);
    printf("Banco: ");

    fgets(nova->banco, sizeof(nova->banco), stdin);
    nova->banco[strcspn(nova->banco, "\n")] = '\0';

    gotoxy(5, 14);
    printf("Agencia: ");

    fgets(nova->agencia, sizeof(nova->agencia), stdin);
    nova->agencia[strcspn(nova->agencia, "\n")] = '\0';

    gotoxy(5, 16);
    printf("Numero da conta: ");

    fgets(nova->numero_conta, sizeof(nova->numero_conta), stdin);
    nova->numero_conta[strcspn(nova->numero_conta, "\n")] = '\0';

    gotoxy(5, 18);
    printf("Tipo de conta: ");

    fgets(nova->tipo_conta, sizeof(nova->tipo_conta), stdin);
    nova->tipo_conta[strcspn(nova->tipo_conta, "\n")] = '\0';

    gotoxy(5, 20);
    printf("Saldo inicial: ");

    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%lf", &nova->vl_saldo) != 1 || nova->vl_saldo < 0)
    {
        return 0;
    }

    gotoxy(5, 22);
    printf("Limite da conta: ");
    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%lf", &nova->vl_limite) != 1 || nova->vl_limite < 0)
    {
        return 0;
    }

    strcpy(nova->status, "ativo");

    nova->ant = NULL;
    nova->prox = NULL;

    return 1;
}

void cadastrar_inicio(Conta **inicio)
{

    Conta *nova = (Conta *)malloc(sizeof(Conta));

    if (nova == NULL)
    {

        return;
    }

    if (!cadastrar_dados(nova, *inicio))
    {

        free(nova);
        return;
    }

    nova->prox = *inicio;

    if (*inicio != NULL)
    {

        (*inicio)->ant = nova;
    }

    *inicio = nova;

    gotoxy(5, 25);
    printf("Conta cadastrada com sucesso!");
}

void cadastrar_final(Conta **inicio)
{

    Conta *nova = (Conta *)malloc(sizeof(Conta));
    Conta *aux;

    if (nova == NULL)
    {

        return;
    }

    if (!cadastrar_dados(nova, *inicio))
    {

        free(nova);
        return;
    }

    if (*inicio == NULL)
    {

        *inicio = nova;
    }

    else
    {

        aux = *inicio;

        while (aux->prox != NULL)
        {

            aux = aux->prox;
        }

        aux->prox = nova;
        nova->ant = aux;
    }

    gotoxy(5, 25);
    printf("Conta cadastrada com sucesso!");
}

void cadastrar_posicao(Conta **inicio)
{

    Conta *nova;
    Conta *aux;
    int posicao;
    int contador = 1;

    system("cls");
    cabecalho("CADASTRO DE CONTA POR POSICAO");
    gotoxy(5, 10);
    printf("Informe a posicao desejada: ");
    scanf("%d", &posicao);
    getchar();

    if (posicao < 1)
    {

        gotoxy(5, 25);
        printf("Posicao invalida!");

        return;
    }

    if (posicao == 1)
    {

        cadastrar_inicio(inicio);

        return;
    }

    aux = *inicio;

    while (aux != NULL && contador < posicao - 1)
    {

        aux = aux->prox;
        contador++;
    }

    if (aux == NULL)
    {

        gotoxy(5, 25);
        printf("Posicao inexistente!");
        return;
    }

    nova = (Conta *)malloc(sizeof(Conta));

    if (nova == NULL)
    {

        return;
    }

    if (!cadastrar_dados(nova, *inicio))
    {

        free(nova);
        return;
    }

    nova->prox = aux->prox;
    nova->ant = aux;

    if (aux->prox != NULL)
    {

        aux->prox->ant = nova;
    }

    aux->prox = nova;

    gotoxy(5, 25);
    printf("Conta cadastrada com sucesso!");
}

void listar_contas(Conta *inicio)
{

    int linha = 10;

    system("cls");
    cabecalho("CONSULTA DE CONTAS BANCARIAS");

    if (inicio == NULL)
    {

        gotoxy(5, 15);
        printf("Nenhuma conta cadastrada.");

        return;
    }

    while (inicio != NULL)
    {

        gotoxy(5, linha);
        printf("Codigo: %d", inicio->codigo_conta);
        gotoxy(35, linha);
        printf("Banco: %s", inicio->banco);
        gotoxy(5, linha + 1);
        printf("Agencia: %s", inicio->agencia);
        gotoxy(35, linha + 1);
        printf("Conta: %s", inicio->numero_conta);
        gotoxy(5, linha + 2);
        printf("Tipo: %s", inicio->tipo_conta);
        gotoxy(35, linha + 2);
        printf("Saldo: R$ %.2f", inicio->vl_saldo);
        gotoxy(5, linha + 3);
        printf("Limite: R$ %.2f", inicio->vl_limite);
        gotoxy(35, linha + 3);
        printf("Status: %s", inicio->status);

        linha += 5;
        inicio = inicio->prox;

        if (linha > 23 && inicio != NULL)
        {

            gotoxy(5, 26);
            printf("Existem mais contas. Pressione uma tecla para continuar.");
            getchar();
            system("cls");
            cabecalho("CONSULTA DE CONTAS BANCARIAS");
            linha = 10;
        }
    }
}