/*
 * Nome: Jose Manuel Salazar
 * Data: 2/11/26
 * Arquivo: movimentacoes.c
 * Contem as funcoes de registro e consulta de movimentacoes bancarias.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/estruturas.h"

void gotoxy(int x, int y);
void cabecalho(char titulo[]);

int converter_data(char data[])
{
    int dia;
    int mes;
    int ano;
    int dias_mes;

    if (strlen(data) != 10 || sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3)
    {

        return 0;
    }

    if (ano < 1 || mes < 1 || mes > 12)
    {

        return 0;
    }

    dias_mes = 31;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {

        dias_mes = 30;
    }
    else if (mes == 2)
    {

        dias_mes = 28;

        if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0))
        {

            dias_mes = 29;
        }
    }

    if (dia < 1 || dia > dias_mes)
    {

        return 0;
    }

    return ano * 10000 + mes * 100 + dia;
}

void realizar_movimentacao(Conta *contas, Movimentacao **movimentos)
{

    Conta *conta = contas;
    Movimentacao *aux;
    Movimentacao *nova;
    Movimentacao *ultima = NULL;

    int codigo;
    int sequencial = 1;
    int data_nova;
    int data_anterior = 0;
    int data_atual;

    char entrada[100];
    char tipo;
    char data[11];

    double valor;

    system("cls");
    cabecalho("MOVIMENTACAO DE CREDITO E DEBITO");

    if (contas == NULL)
    {

        gotoxy(5, 15);
        printf("Nenhuma conta cadastrada!");

        return;
    }

    gotoxy(5, 10);
    printf("Codigo da conta: ");
    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%d", &codigo) != 1)
    {

        gotoxy(5, 25);
        printf("Codigo invalido!");

        return;
    }

    while (conta != NULL && conta->codigo_conta != codigo)
    {

        conta = conta->prox;
    }

    if (conta == NULL)
    {

        gotoxy(5, 25);
        printf("Conta nao encontrada!");

        return;
    }

    if (strcmp(conta->status, "ativo") != 0)
    {

        gotoxy(5, 25);
        printf("Conta inativa!");

        return;
    }

    gotoxy(5, 12);
    printf("Tipo de movimentacao (C/D): ");
    fgets(entrada, sizeof(entrada), stdin);

    tipo = entrada[0];

    if (tipo != 'C' && tipo != 'c' && tipo != 'D' && tipo != 'd')
    {

        gotoxy(5, 25);
        printf("Tipo de movimentacao invalido!");

        return;
    }

    gotoxy(5, 14);
    printf("Data (DD/MM/AAAA): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    data_nova = converter_data(data);

    if (data_nova == 0)
    {

        gotoxy(5, 25);
        printf("Data invalida!");
        return;
    }

    gotoxy(5, 16);
    printf("Valor da movimentacao: ");
    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%lf", &valor) != 1 || valor <= 0)
    {
        gotoxy(5, 25);
        printf("Valor invalido!");

        return;
    }

    aux = *movimentos;

    while (aux != NULL)
    {

        if (aux->sequencial >= sequencial)
        {

            sequencial = aux->sequencial + 1;
        }

        if (aux->codigo_conta == codigo)
        {

            data_atual = converter_data(aux->dt_movimento);

            if (data_atual > data_anterior)
            {

                data_anterior = data_atual;
            }
        }

        ultima = aux;
        aux = aux->prox;
    }

    if (data_nova < data_anterior)
    {

        gotoxy(5, 25);
        printf("A data nao pode ser anterior a ultima movimentacao!");

        return;
    }

    if ((tipo == 'D' || tipo == 'd') && conta->vl_saldo - valor < -conta->vl_limite)
    {

        gotoxy(5, 25);
        printf("Saldo insuficiente para realizar o debito!");

        return;
    }

    nova = (Movimentacao *)malloc(sizeof(Movimentacao));

    if (nova == NULL)
    {

        gotoxy(5, 25);
        printf("Erro ao alocar memoria!");

        return;
    }

    nova->sequencial = sequencial;
    nova->codigo_conta = codigo;

    strcpy(nova->dt_movimento, data);

    if (tipo == 'C' || tipo == 'c')
    {

        strcpy(nova->tp_movimentacao, "credito");
        conta->vl_saldo += valor;
    }
    else
    {

        strcpy(nova->tp_movimentacao, "debito");
        conta->vl_saldo -= valor;
    }

    nova->vl_movimento = valor;
    nova->vl_saldo = conta->vl_saldo;
    nova->prox = NULL;

    if (*movimentos == NULL)
    {

        *movimentos = nova;
    }
    else
    {

        ultima->prox = nova;
    }

    gotoxy(5, 20);
    printf("Movimentacao registrada com sucesso!");

    gotoxy(5, 22);
    printf("Novo saldo: R$ %.2f", conta->vl_saldo);
}