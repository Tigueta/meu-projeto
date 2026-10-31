/*
 * Nome: Santiago Gabriel Reyes
 * Data: 30/10/26
 * Arquivo: main.c
 * Descricao: Contem a funcao principal e os menus do sistema bancario.
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "../include/estruturas.h"

void gotoxy(int x, int y)
{

    COORD posicao;
    posicao.X = x;
    posicao.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posicao);
}

void desenhar_tela()
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

void cabecalho(char titulo[])
{

    desenhar_tela();

    gotoxy(33, 3);
    printf("SISTEMA DE CONTROLE BANCARIO");

    gotoxy(2, 5);
    printf("================================================================================================");

    gotoxy(43, 7);
    printf("%s", titulo);
}

char ler_opcao()
{

    char opcao;

    gotoxy(5, 26);
    printf("Escolha uma opcao: ");

    scanf(" %c", &opcao);
    getchar();

    return opcao;
}

void pausar()
{

    gotoxy(5, 28);
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

void menu_contas(Conta **inicio, Movimentacao *movimentos)
{

    char opcao;

    do
    {

        system("cls");
        cabecalho("MENU DE CONTAS BANCARIAS");
        gotoxy(5, 11);
        printf("1 - Cadastrar Contas Bancarias no Final");
        gotoxy(5, 13);
        printf("2 - Cadastrar Contas Bancarias no Inicio");
        gotoxy(5, 15);
        printf("3 - Cadastrar Contas Bancarias na Posicao");
        gotoxy(5, 17);
        printf("4 - Remover Contas Bancarias no Final");
        gotoxy(5, 18);
        printf("5 - Remover Contas Bancarias no Inicio");
        gotoxy(5, 19);
        printf("6 - Remover Contas Bancarias na Posicao");
        gotoxy(5, 21);
        printf("7 - Alteracao das Contas Bancarias");
        gotoxy(5, 22);
        printf("8 - Consultar Contas Bancarias");
        gotoxy(5, 24);
        printf("9 - Retornar ao Menu Anterior");
        opcao = ler_opcao();
        system("cls");

        switch (opcao)
        {

        case '1':

            cadastrar_final(inicio);
            pausar();
            break;

        case '2':

            cadastrar_inicio(inicio);
            pausar();
            break;

        case '3':

            cadastrar_posicao(inicio);
            pausar();
            break;

        case '7':

            alterar_conta(*inicio);
            pausar();
            break;

        case '8':

            listar_contas(*inicio);
            pausar();
            break;

        case '9':

            break;

        case '4':
        case '5':
        case '6':
            cabecalho("FUNCIONALIDADE EM DESENVOLVIMENTO");
            gotoxy(20, 15);
            printf("Esta opcao sera implementada posteriormente.");
            pausar();
            break;

        default:

            cabecalho("OPCAO INVALIDA");
            gotoxy(35, 15);
            printf("Tente novamente.");
            pausar();
        }

    } while (opcao != '9');
}

void menu_movimentacao()
{

    char opcao;

    do
    {

        system("cls");
        cabecalho("MENU DE MOVIMENTACAO BANCARIA");

        gotoxy(5, 12);
        printf("1 - Movimentacao de Debito e Credito");
        gotoxy(5, 15);
        printf("2 - Transferencia entre Contas Bancarias");
        gotoxy(5, 18);
        printf("3 - Consulta Movimentacoes Bancarias");
        gotoxy(5, 22);
        printf("4 - Retornar ao Menu Anterior");

        opcao = ler_opcao();

        if (opcao >= '1' && opcao <= '3')
        {

            system("cls");
            cabecalho("FUNCIONALIDADE EM DESENVOLVIMENTO");
            gotoxy(20, 15);
            printf("Esta opcao sera implementada posteriormente.");
            pausar();
        }

        else if (opcao != '4')
        {

            system("cls");
            cabecalho("OPCAO INVALIDA");
            gotoxy(35, 15);
            printf("Tente novamente.");
            pausar();
        }

    } while (opcao != '4');
}

int main()
{

    Conta *inicio_contas = NULL;
    Movimentacao *inicio_movimentacoes = NULL;
    char opcao;

    system("color 0F");
    system("mode con: cols=100 lines=30");

    do
    {
        system("cls");
        cabecalho("MENU PRINCIPAL");

        gotoxy(5, 12);
        printf("1 - Contas bancarias");

        gotoxy(5, 15);
        printf("2 - Movimentacao bancaria");

        gotoxy(5, 18);
        printf("3 - Sair do programa");

        opcao = ler_opcao();

        switch (opcao)
        {

        case '1':
            menu_contas(&inicio_contas, inicio_movimentacoes);
            break;

        case '2':

            menu_movimentacao();
            break;

        case '3':

            system("cls");
            cabecalho("ENCERRANDO O SISTEMA");
            gotoxy(35, 15);
            printf("Programa encerrado!");
            Sleep(1000);
            break;

        default:

            system("cls");
            cabecalho("OPCAO INVALIDA");
            gotoxy(35, 15);
            printf("Tente novamente.");
            pausar();
        }

    } while (opcao != '3');

    return 0;
}