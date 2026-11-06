/*
 * Nome: Jose Manuel Salazar
 * Data: 02/11/26
 * Arquivo: movimentacoes.c
 * Descrição: Contem as funcoes de registro e consulta de movimentacoes bancarias.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "../include/estruturas.h"

void gotoxy(int x, int y);
void cabecalho(char titulo[]);

int converter_data(char data[]) {

    int dia;
    int mes;
    int ano;
    int dias_mes;

    if (strlen(data) != 10 || sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) != 3) {

        return 0;
    }

    if (ano < 1 || mes < 1 || mes > 12) {

        return 0;
    }


    dias_mes = 31;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {

        dias_mes = 30;

    } else if (mes == 2) {

        dias_mes = 28;

        if ((ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0)) {

            dias_mes = 29;

        }

    }

    if (dia < 1 || dia > dias_mes)
    {

        return 0;
    }

    return ano * 10000 + mes * 100 + dia;
}



void realizar_movimentacao(Conta *contas, Movimentacao **movimentos) {

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
    char data[20];
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




    if (tipo == 'C' || tipo == 'c'){

        strcpy(nova->tp_movimentacao, "credito");
        conta->vl_saldo += valor;

    } else {

        strcpy(nova->tp_movimentacao, "debito");
        conta->vl_saldo -= valor;

    }

    nova->vl_movimento = valor;
    nova->vl_saldo = conta->vl_saldo;
    nova->prox = NULL;

    if (*movimentos == NULL) {

        *movimentos = nova;

    } else {

        ultima->prox = nova;

    }

    gotoxy(5, 20);
    printf("Movimentacao registrada com sucesso!");
    gotoxy(5, 22);
    printf("Novo saldo: R$ %.2f", conta->vl_saldo);

}



void consultar_movimentacoes(Conta *contas, Movimentacao *movimentos) {

    int codigo;
    int encontrou = 0;
    int linha = 13;

    system("cls");
    cabecalho("HISTORICO DE MOVIMENTACOES");
    gotoxy(5, 10);
    printf("Codigo da conta: ");
    scanf("%d", &codigo);
    getchar();

    while (contas != NULL && contas->codigo_conta != codigo) {

        contas = contas->prox;

    }

    if (contas == NULL) {

        gotoxy(5, 25);
        printf("Conta nao encontrada!");

        return;
    }

    gotoxy(5, 11);
    printf("Conta: %d | Banco: %s", contas->codigo_conta, contas->banco);
    gotoxy(5, 13);
    printf("SEQ.  DATA        TIPO       VALOR          SALDO");
    gotoxy(5, 14);
    printf("----------------------------------------------------------");

    while (movimentos != NULL) {

        if (movimentos->codigo_conta == codigo) {

            encontrou = 1;

            gotoxy(5, linha);
            printf("%-5d %-11s %-10s R$ %-10.2f R$ %.2f", movimentos->sequencial, movimentos->dt_movimento, movimentos->tp_movimentacao, movimentos->vl_movimento, movimentos->vl_saldo);

            linha++;

        }

        movimentos = movimentos->prox;

    }

    if (!encontrou) {

        gotoxy(5, 16);
        printf("Nenhuma movimentacao encontrada!");

    }

    gotoxy(5, 27);
    printf("Pressione uma tecla para voltar...");
    getch();

}



void realizar_transferencia(Conta *contas, Movimentacao **movimentos) {


    Conta *origem = NULL;
    Conta *destino = NULL;
    Conta *aux_conta;

    Movimentacao *aux_mov;
    Movimentacao *debito;
    Movimentacao *credito;
    Movimentacao *ultima = NULL;


    int codigo_origem;
    int codigo_destino;
    int sequencial = 1;
    int data_nova;
    int data_origem = 0;
    int data_destino = 0;
    int data_atual;
    double valor;
    char entrada[100];
    char data[20];


    system("cls");
    cabecalho("TRANSFERENCIA ENTRE CONTAS");


    if (contas == NULL) {

        gotoxy(5, 15);
        printf("Nenhuma conta cadastrada!");

        return;
    }

    gotoxy(5, 10);
    printf("Codigo da conta de origem: ");
    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%d", &codigo_origem) != 1) {

        gotoxy(5, 25);
        printf("Codigo de origem invalido!");

        return;
    }

    gotoxy(5, 12);
    printf("Codigo da conta de destino: ");
    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%d", &codigo_destino) != 1) {

        gotoxy(5, 25);
        printf("Codigo de destino invalido!");

        return;
    }

    if (codigo_origem == codigo_destino) {

        gotoxy(5, 25);
        printf("As contas devem ser diferentes!");

        return;
    }

    aux_conta = contas;

    while (aux_conta != NULL) {

        if (aux_conta->codigo_conta == codigo_origem)

            origem = aux_conta;

        if (aux_conta->codigo_conta == codigo_destino)

            destino = aux_conta;

        aux_conta = aux_conta->prox;

    }

    if (origem == NULL || destino == NULL) {

        gotoxy(5, 25);
        printf("Uma das contas nao foi encontrada!");

        return;
    }

    if (strcmp(origem->status, "ativo") != 0 || strcmp(destino->status, "ativo") != 0) {

        gotoxy(5, 25);
        printf("As duas contas precisam estar ativas!");

        return;
    }

    gotoxy(5, 14);
    printf("Valor da transferencia: ");
    fgets(entrada, sizeof(entrada), stdin);

    if (sscanf(entrada, "%lf", &valor) != 1 || valor <= 0) {
        gotoxy(5, 25);
        printf("Valor invalido!");

        return;
    }

    if (origem->vl_saldo - valor < -origem->vl_limite) {

        gotoxy(5, 25);
        printf("Saldo insuficiente para a transferencia!");

        return;
    }

    gotoxy(5, 16);
    printf("Data (DD/MM/AAAA): ");

    fgets(data, sizeof(data), stdin);

    data[strcspn(data, "\n")] = '\0';

    data_nova = converter_data(data);

    if (data_nova == 0) {

        gotoxy(5, 25);
        printf("Data invalida!");

        return;
    }

    aux_mov = *movimentos;

    while (aux_mov != NULL) {

        if (aux_mov->sequencial >= sequencial)

            sequencial = aux_mov->sequencial + 1;

        if (aux_mov->codigo_conta == codigo_origem) {
            
            data_atual = converter_data(aux_mov->dt_movimento);

            if (data_atual > data_origem)
            
                data_origem = data_atual;
            
        }

        if (aux_mov->codigo_conta == codigo_destino) {

            data_atual = converter_data(aux_mov->dt_movimento);

            if (data_atual > data_destino)

                data_destino = data_atual;

        }

        ultima = aux_mov;
        aux_mov = aux_mov->prox;

    }

    if (data_nova < data_origem || data_nova < data_destino) {

        gotoxy(5, 25);
        printf("Data não pode ser anterior a ultima movimentacao!");

        return;

    }

    debito = (Movimentacao *)malloc(sizeof(Movimentacao));
    credito = (Movimentacao *)malloc(sizeof(Movimentacao));

    if (debito == NULL || credito == NULL) {

        free(debito);
        free(credito);

        gotoxy(5, 25);
        printf("Erro ao alocar memoria!");

        return;

    }

    debito->sequencial = sequencial;
    debito->codigo_conta = codigo_origem;

    strcpy(debito->dt_movimento, data);
    strcpy(debito->tp_movimentacao, "debito");
    sprintf(debito->ds_favorecido, "Conta %d", codigo_destino);

    debito->vl_movimento = valor;
    debito->vl_saldo = origem->vl_saldo - valor;
    debito->prox = credito;

    credito->sequencial = sequencial + 1;
    credito->codigo_conta = codigo_destino;

    strcpy(credito->dt_movimento, data);
    strcpy(credito->tp_movimentacao, "credito");
    sprintf(credito->ds_favorecido, "Conta %d", codigo_origem);
    
    credito->vl_movimento = valor;
    credito->vl_saldo = destino->vl_saldo + valor;
    credito->prox = NULL;

    if (*movimentos == NULL) {

        *movimentos = debito;

    } else {

        ultima->prox = debito;

    }

    origem->vl_saldo -= valor;
    destino->vl_saldo += valor;

    gotoxy(5, 20);
    printf("Transferencia realizada com sucesso!");

    gotoxy(5, 22);
    printf("Novo saldo da origem: R$ %.2f", origem->vl_saldo);

    gotoxy(5, 23);
    printf("Novo saldo do destino: R$ %.2f", destino->vl_saldo);


}




