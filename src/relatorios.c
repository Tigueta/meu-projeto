#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "../include/estruturas.h"

static void gotoxy(int x, int y)
{

    COORD posicao;
    posicao.X = x;
    posicao.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicao);
}

static void desenhar_tela()
{

    int i;

    system("cls");

    for (i = 1; i <= 98; i++)
    {

        gotoxy(i, 1);
        printf("-");
        gotoxy(i, 29);
        printf("-");
    }

    for (i = 1; i <= 29; i++)
    {

        gotoxy(1, i);
        printf("|");
        gotoxy(98, i);
        printf("|");
    }

    gotoxy(1, 1);
    printf("+");
    gotoxy(98, 1);
    printf("+");
    gotoxy(1, 29);
    printf("+");
    gotoxy(98, 29);
    printf("+");
}



static void cabecalho(char titulo[])
{

    desenhar_tela();

    gotoxy(33, 3);
    printf("SISTEMA DE CONTROLE BANCARIO");

    gotoxy(2, 5);
    printf("================================================================================================");

    gotoxy(43, 7);
    printf("%s", titulo);
}



void relatorio_contas(Conta *inicio) {

    Conta *aux = inicio;
    int linha = 11;

    cabecalho("RELATORIO DE CONTAS");

    if (inicio == NULL)
    {

        gotoxy(30, 15);
        printf("Nenhuma conta cadastrada.");

        return;
    }

    gotoxy(3, 9);
    printf("COD");

    gotoxy(9, 9);
    printf("BANCO");

    gotoxy(25, 9);
    printf("AGENCIA");

    gotoxy(36, 9);
    printf("NUMERO");

    gotoxy(51, 9);
    printf("TIPO");

    gotoxy(62, 9);
    printf("SALDO");

    gotoxy(74, 9);
    printf("LIMITE");

    gotoxy(87, 9);
    printf("STATUS");

    while (aux != NULL)
    {

        gotoxy(3, linha);
        printf("%d", aux->codigo_conta);

        gotoxy(9, linha);
        printf("%.18s", aux->banco);

        gotoxy(25, linha);
        printf("%.10s", aux->agencia);

        gotoxy(36, linha);
        printf("%.14s", aux->numero_conta);

        gotoxy(51, linha);
        printf("%.10s", aux->tipo_conta);

        gotoxy(62, linha);
        printf("%.2f", aux->vl_saldo);

        gotoxy(74, linha);
        printf("%.2f", aux->vl_limite);

        gotoxy(87, linha);
        printf("%.8s", aux->status);

        aux = aux->prox;
        linha++;

        if (linha > 25 && aux != NULL)
        {

            gotoxy(5, 27);
            printf("Pressione qualquer tecla para continuar...");
            getch();

            cabecalho("RELATORIO DE CONTAS");

            linha = 11;

            gotoxy(3, 10);
            printf("COD");

            gotoxy(9, 10);
            printf("BANCO");

            gotoxy(25, 10);
            printf("AGENCIA");

            gotoxy(36, 10);
            printf("NUMERO");

            gotoxy(51, 10);
            printf("TIPO");

            gotoxy(62, 10);
            printf("SALDO");

            gotoxy(74, 10);
            printf("LIMITE");

            gotoxy(87, 10);
            printf("STATUS");
        }
    }

    gotoxy(5, 27);
    printf("Relatorio finalizado.");

}



void relatorio_extrato(Conta *contas, Movimentacao *movimentos) {

    int codigo;
    int encontrou = 0;
    int linha = 13;
    int caractere;

    Conta *conta = contas;
    Movimentacao *aux = movimentos;

    desenhar_tela();
    cabecalho("EXTRATO DE CONTA");

    gotoxy(5, 7);
    printf("Digite o codigo da conta: ");
    scanf("%d", &codigo);

    while ((caractere = getchar()) != '\n' && caractere != EOF) {}

    while (conta != NULL && conta->codigo_conta != codigo) {

        conta = conta->prox;

    }

    if (conta == NULL){

        gotoxy(5, 8);
        printf("Conta nao encontrada!");

        return;
    }

    gotoxy(5, 9);
    printf("Banco: %s", conta->banco);

    gotoxy(5, 10);
    printf("Numero da conta: %s", conta->numero_conta);

    gotoxy(5, 12);
    printf("DATA       TIPO          FAVORECIDO          VALOR       SALDO");

    while (aux != NULL) {

        if (aux->codigo_conta == codigo) {

            if (linha > 25) {

                gotoxy(5, 27);
                printf("Pressione qualquer tecla para continuar...");
                getch();

                cabecalho("EXTRATO DE CONTA");

                gotoxy(5, 9);
                printf("Banco: %s", conta->banco);

                gotoxy(5, 10);
                printf("Numero da conta: %s", conta->numero_conta);

                gotoxy(5, 12);
                printf("DATA       TIPO          FAVORECIDO          VALOR       SALDO");

                linha = 13;
                
            }

            gotoxy(5, linha);

            printf("%-11s %-13s %-20.20s R$ %-9.2f R$ %.2f",aux->dt_movimento,aux->tp_movimentacao,aux->ds_favorecido,aux->vl_movimento,aux->vl_saldo);

            encontrou++;
            linha++;

        }

        aux = aux->prox;
    }

    if (encontrou == 0) {

        gotoxy(5, 15);
        printf("Essa conta ainda nao possui movimentacoes.");

    } else {

        gotoxy(5, 27);
        printf("Extrato finalizado. Total de movimentacoes: %d", encontrou);

    }
}

void relatorio_inativas(Conta *inicio)
{

    Conta *aux = inicio;
    int encontrou = 0;
    int linha = 7;

    desenhar_tela();
    cabecalho("CONTAS INATIVAS");

    gotoxy(5, 5);
    printf("CODIGO====BANCO=================NUMERO DA CONTA");

    while (aux != NULL)
    {

        if (aux->status[0] == 'I' || aux->status[0] == 'i')
        {
            gotoxy(5, linha);

            printf("%-10d %-21.21s %-20s",
                   aux->codigo_conta,
                   aux->banco,
                   aux->numero_conta);

            linha++;
            encontrou++;
        }

        aux = aux->prox;
    }

    if (encontrou == 0)
    {
        gotoxy(5, 7);
        printf("Nenhuma conta inativa encontrada.");
    }
}



void relatorio_limites(Conta *inicio)
{
    Conta *aux = inicio;
    int linha = 7;

    desenhar_tela();
    cabecalho("LIMITES DE CREDITO");

    gotoxy(5, 5);
    printf("CODIGO====BANCO=================SALDO==========LIMITE");

    if (inicio == NULL)
    {
        gotoxy(5, 7);
        printf("Nenhuma conta cadastrada.");
        return;
    }

    while (aux != NULL)
    {
        gotoxy(5, linha);

        printf("%-10d %-21.21s R$ %-12.2f R$ %.2f",aux->codigo_conta,aux->banco,aux->vl_saldo,aux->vl_limite);

        aux = aux->prox;
        linha++;
    }
}
