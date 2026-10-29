/*
 * Nome: Santiago Gabriel Reyes
 * Data: 28/10/26
 * Arquivo: contas.c
 * Descricao: Implementa as operacoes de cadastro e listagem de contas bancarias.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/estruturas.h"

int codigo_existe(Conta *inicio, int codigo) {
    Conta *aux = inicio;

    while (aux != NULL) {
        if (aux->codigo_conta == codigo) {
            return 1;
        }

        aux = aux->prox;
    }

    return 0;
}

void cadastrar_dados(Conta *nova) {

    printf("\nCodigo da conta: ");
    scanf("%d", &nova->codigo_conta);

    printf("Banco: ");
    scanf(" %49[^\n]", nova->banco);

    printf("Agencia: ");
    scanf(" %9[^\n]", nova->agencia);

    printf("Numero da conta: ");
    scanf(" %19[^\n]", nova->numero_conta);

    printf("Tipo da conta (corrente/poupanca): ");
    scanf(" %19[^\n]", nova->tipo_conta);

    printf("Saldo inicial: ");
    scanf("%lf", &nova->vl_saldo);

    printf("Limite de credito: ");
    scanf("%lf", &nova->vl_limite);

    strcpy(nova->status, "ativo");

    nova->ant = NULL;
    nova->prox = NULL;
}

void cadastrar_inicio(Conta **inicio) {
    Conta *nova = malloc(sizeof(Conta));

    if (nova == NULL) {
        printf("Erro ao reservar memoria!\n");
        return;
    }

    printf("\n--- Cadastro de conta ---\n");
    cadastrar_dados(nova);

    if (codigo_existe(*inicio, nova->codigo_conta)) {
        free(nova);
        printf("Codigo ja cadastrado!\n");
        return;
    }

    nova->prox = *inicio;

    if (*inicio != NULL) {
        (*inicio)->ant = nova;
    }

    *inicio = nova;

    printf("Conta cadastrada no inicio!\n");
}

void cadastrar_final(Conta **inicio) {
    Conta *nova = malloc(sizeof(Conta));
    Conta *aux = *inicio;

    if (nova == NULL) {
        printf("Erro ao reservar memoria!\n");
        return;
    }

    printf("\n--- Cadastro de conta ---\n");
    cadastrar_dados(nova);

    if (codigo_existe(*inicio, nova->codigo_conta)) {
        free(nova);
        printf("Codigo ja cadastrado!\n");
        return;
    }

    if (*inicio == NULL) {
        *inicio = nova;
    } else {
        while (aux->prox != NULL) {
            aux = aux->prox;
        }

        aux->prox = nova;
        nova->ant = aux;
    }

    printf("Conta cadastrada no final!\n");
}

void cadastrar_posicao(Conta **inicio) {
    Conta *nova;
    Conta *aux = *inicio;
    int pos, i;

    printf("Posicao para inserir: ");
    scanf("%d", &pos);

    if (pos < 1) {
        printf("Posicao invalida!\n");
        return;
    }

    if (pos == 1) {
        cadastrar_inicio(inicio);
        return;
    }

    for (i = 1; aux != NULL && i < pos - 1; i++) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Posicao invalida!\n");
        return;
    }

    nova = malloc(sizeof(Conta));

    if (nova == NULL) {
        printf("Erro ao reservar memoria!\n");
        return;
    }

    printf("\n--- Cadastro de conta ---\n");
    cadastrar_dados(nova);

    if (codigo_existe(*inicio, nova->codigo_conta)) {
        free(nova);
        printf("Codigo ja cadastrado!\n");
        return;
    }

    nova->prox = aux->prox;
    nova->ant = aux;

    if (aux->prox != NULL) {
        aux->prox->ant = nova;
    }

    aux->prox = nova;

    printf("Conta cadastrada na posicao %d!\n", pos);
}

void listar_contas(Conta *inicio) {
    Conta *aux = inicio;

    if (aux == NULL) {
        printf("\nNenhuma conta cadastrada.\n");
        return;
    }

    while (aux != NULL) {
        printf("\n------------------------------\n");
        printf("Codigo: %d\n", aux->codigo_conta);
        printf("Banco: %s\n", aux->banco);
        printf("Agencia: %s\n", aux->agencia);
        printf("Numero: %s\n", aux->numero_conta);
        printf("Tipo: %s\n", aux->tipo_conta);
        printf("Saldo: R$ %.2f\n", aux->vl_saldo);
        printf("Limite: R$ %.2f\n", aux->vl_limite);
        printf("Status: %s\n", aux->status);

        aux = aux->prox;
    }
}


