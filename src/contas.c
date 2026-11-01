/*
 * Nome: Santiago Gabriel Reyes e Jose Manuel Salazar
 * Data: 31/10/26
 * Arquivo: contas.c
 * Descricao: Contem as funcoes de cadastro, consulta, alteracao e remocao de contas bancarias.
 * 
 * (Santiago: Incluiu funcoes de cadastro, consulta e remocao)
 * (Jose: Incluiu funcoes de alteracao)
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

    int codigo;
    int encontrou = 0;
    int linha = 12;

    Conta *aux = inicio;

    system("cls");
    cabecalho("CONSULTA DE CONTAS BANCARIAS");

    gotoxy(5, 10);
    printf("Informe o codigo da conta (0 para listar todas):");
    scanf("%d", &codigo);
    getchar();

    if (inicio == NULL)
    {

        gotoxy(5, 15);
        printf("Nenhuma conta cadastrada.");

        return;

    }

    while (aux != NULL)
    {
        if (codigo == 0 || aux->codigo_conta == codigo) {

            encontrou = 1;

            gotoxy(5, linha);
            printf("Codigo : %d", aux->codigo_conta);
            gotoxy(35, linha);
            printf("Banco: %s", aux->banco);
            gotoxy(5, linha + 1);
            printf("Agencia: %s", aux->agencia);
            gotoxy(35, linha + 1);
            printf("Conta: %s", aux->numero_conta);
            gotoxy(5, linha + 2);
            printf("Tipo: %s", aux->tipo_conta);
            gotoxy(35, linha + 2);
            printf("Saldo: R$ %.2f", aux->vl_saldo);
            gotoxy(5, linha + 3);
            printf("Limite: R$ %.2f", aux->vl_limite);
            gotoxy(35, linha + 3);
            printf("Status: %s", aux->status);

            linha += 5;

            if (linha > 23 && aux->prox != NULL && codigo == 0) {

                gotoxy(5, 27);
                printf("Pressione uma tecla para continuar...");
                getchar();

                system("cls");
                cabecalho("CONSULTA DE CONTAS BANCARIAS");
                linha = 10;

            }

        } 

        aux = aux->prox;

    } 

    if (!encontrou) {

        gotoxy(5, 15);
        printf("Conta nao encontrada!");
    
    }

}


void alterar_conta(Conta *inicio)
{

    Conta *aux = inicio;
    int codigo;

    system("cls");
    cabecalho("ALTERACAO DE CONTA BANCARIA");

    gotoxy(5, 10);
    printf("Informe o codigo da conta: ");
    scanf("%d", &codigo);
    getchar();

    while (aux != NULL && aux->codigo_conta != codigo)
    {
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        gotoxy(5, 25);
        printf("Conta nao encontrada!");
        return;
    }

    gotoxy(5, 12);
    printf("Novo banco: ");
    fgets(aux->banco, sizeof(aux->banco), stdin);
    aux->banco[strcspn(aux->banco, "\n")] = '\0';

    gotoxy(5, 14);
    printf("Nova agencia: ");
    fgets(aux->agencia, sizeof(aux->agencia), stdin);
    aux->agencia[strcspn(aux->agencia, "\n")] = '\0';

    gotoxy(5, 16);
    printf("Novo numero da conta: ");
    fgets(aux->numero_conta, sizeof(aux->numero_conta), stdin);
    aux->numero_conta[strcspn(aux->numero_conta, "\n")] = '\0';

    gotoxy(5, 18);
    printf("Novo tipo de conta: ");
    fgets(aux->tipo_conta, sizeof(aux->tipo_conta), stdin);
    aux->tipo_conta[strcspn(aux->tipo_conta, "\n")] = '\0';

    gotoxy(5, 25);
    printf("Dados alterados com sucesso!");
}

int conta_tem_movimentacao(Movimentacao *movimentos, int codigo)
{

    while (movimentos != NULL)
    {

        if (movimentos->codigo_conta == codigo)
        {
            return 1;
        }

        movimentos = movimentos->prox;
    }

    return 0;
}

void remover_inicio(Conta **inicio, Movimentacao *movimentos)
{

    Conta *aux;


    if (*inicio == NULL) {

        gotoxy(5, 25);
        printf("Nenhuma conta cadastrada!");
        return;

    }

    aux = *inicio;

    if (conta_tem_movimentacao(movimentos, aux->codigo_conta)) {

        gotoxy(5, 25);
        printf("Conta possui movimentacoes e nao pode ser removida!");

        return;

    }

    *inicio = aux->prox;

    if (*inicio != NULL) {

        (*inicio)->ant = NULL;

    }

    free(aux);

    gotoxy(5, 25);
    printf("Conta removida com sucesso!");

}

void remover_final(Conta **inicio, Movimentacao *movimentos) {

    Conta *aux;

    if (*inicio == NULL) {

        gotoxy(5, 25);
        printf("Nenhuma conta cadastrada!");
        return;

    }

    aux = *inicio;

    while (aux->prox != NULL) {

        aux = aux->prox;

    }

    if (conta_tem_movimentacao(movimentos, aux->codigo_conta)) {

        gotoxy(5, 25);
        printf("Conta possui movimentacoes e nao pode ser removida!");
        return;

    }

    if (aux->ant != NULL) {

        aux->ant->prox = NULL;

    } else {

        *inicio = NULL;

    }


    free(aux);

    gotoxy(5, 25);
    printf("Conta removida com sucesso!");

}

void remover_posicao(Conta **inicio, Movimentacao *movimentos) {


    Conta *aux;
    int posicao;
    int contador = 1;


    if (*inicio == NULL) {

        gotoxy(5, 25);
        printf("Nenhuma conta cadastrada!");

        return;

    }

    system("cls");
    cabecalho("REMOVER CONTA POR POSICAO");
    gotoxy(5, 10);
    printf("Informe a posicao: ");
    scanf("%d", &posicao);
    getchar();


    if (posicao < 1) {

        gotoxy(5, 25);
        printf("Posicao invalida!");

        return;
    }

    aux = *inicio;

    while (aux != NULL && contador < posicao) {

        aux = aux->prox;
        contador++;

    }

    if (aux == NULL) {

        gotoxy(5, 25);
        printf("Posicao inexistente!");

        return;
    }

    if (conta_tem_movimentacao(movimentos, aux->codigo_conta)) {

        gotoxy(5, 25);
        printf("Conta possui movimentacoes e nao pode ser removida!");

        return;

    }

    if (aux->ant != NULL) {

        aux->ant->prox = aux->prox;

    } else {

        *inicio = aux->prox;

    }

    if (aux->prox != NULL) {

        aux->prox->ant = aux->ant;
        
    }

    free(aux);

    gotoxy(5, 25);
    printf("Conta removida com sucesso!");


}



