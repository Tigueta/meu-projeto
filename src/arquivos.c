/*
 * Nome: Jose Manuel Salazar e Santiago Gabriel Reyes
 * Data: 03/11/26
 * Arquivo: arquivos.c
 * Descrição: Contem as funcoes de leitura e escrita de arquivos binarios para persistencia dos dados do sistema.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/estruturas.h"

typedef struct {

    int codigo_conta;
    char banco[50];
    char agencia[10];
    char numero_conta[20];
    char tipo_conta[20];
    double vl_saldo;
    double vl_limite;
    char status[10];

} DadosConta;




typedef struct {

    int sequencial;
    int codigo_conta;
    char dt_movimento[11];
    char tp_movimentacao[15];
    char ds_favorecido[50];
    double vl_movimento;
    double vl_saldo;

} DadosMovimentacao;




int salvar_contas(Conta *inicio) {

    FILE *arquivo;
    Conta *aux;
    DadosConta dados = {0};

    arquivo = fopen("contas.dat", "wb");


    if (arquivo == NULL){

        return 0;
    }


    for (aux = inicio; aux != NULL; aux = aux->prox) {

        dados = (DadosConta){0};

        dados.codigo_conta = aux->codigo_conta;
        strcpy(dados.banco, aux->banco);
        strcpy(dados.agencia, aux->agencia);
        strcpy(dados.numero_conta, aux->numero_conta);
        strcpy(dados.tipo_conta, aux->tipo_conta);
        dados.vl_saldo = aux->vl_saldo;
        dados.vl_limite = aux->vl_limite;
        strcpy(dados.status, aux->status);

        if (fwrite(&dados, sizeof(dados), 1, arquivo) != 1) {

            fclose(arquivo);
            return 0;

        }

    }

    if (fclose(arquivo) != 0){

        return 0;
    }

    return 1;

}




int carregar_contas(Conta **inicio) {

    FILE *arquivo;
    DadosConta dados;
    Conta *nova;
    Conta *fim = NULL;

    if (inicio == NULL || *inicio != NULL) {

        return 0;

    }

    arquivo = fopen("contas.dat", "rb");

    if (arquivo == NULL) {

        return 1;

    }

    while (fread(&dados, sizeof(dados), 1, arquivo) == 1) {

        nova = (Conta *)malloc(sizeof(Conta));

        if (nova == NULL) {

            fclose(arquivo);
            return 0;

        }

        nova->codigo_conta = dados.codigo_conta;
        strcpy(nova->banco, dados.banco);
        strcpy(nova->agencia, dados.agencia);
        strcpy(nova->numero_conta, dados.numero_conta);
        strcpy(nova->tipo_conta, dados.tipo_conta);
        nova->vl_saldo = dados.vl_saldo;
        nova->vl_limite = dados.vl_limite;
        strcpy(nova->status, dados.status);

        nova->ant = fim;
        nova->prox = NULL;

        if (fim == NULL) {

            *inicio = nova;

        } else {

            fim->prox = nova;

        }

        fim = nova;

    }

    if (ferror(arquivo)) {

        fclose(arquivo);

        return 0;
        
    }


    fclose(arquivo);

    return 1;

}




int salvar_movimentacoes(Movimentacao *inicio) {

    FILE *arquivo;
    Movimentacao *aux;
    DadosMovimentacao dados = {0};

    arquivo = fopen("movimentacoes.dat", "wb");

    if (arquivo == NULL) {

        return 0;

    }

    for (aux = inicio; aux != NULL; aux = aux->prox) {

        dados = (DadosMovimentacao){0};

        dados.sequencial = aux->sequencial;
        dados.codigo_conta = aux->codigo_conta;
        strcpy(dados.dt_movimento, aux->dt_movimento);
        strcpy(dados.tp_movimentacao, aux->tp_movimentacao);
        strcpy(dados.ds_favorecido, aux->ds_favorecido);
        dados.vl_movimento = aux->vl_movimento;
        dados.vl_saldo = aux->vl_saldo;

        if (fwrite(&dados, sizeof(dados), 1, arquivo) != 1) {

            fclose(arquivo);

            return 0;

        }

    }

    if (fclose(arquivo) != 0)

        return 0;

    return 1;
}




int carregar_movimentacoes(Movimentacao **inicio) {

    FILE *arquivo;
    DadosMovimentacao dados;
    Movimentacao *nova;
    Movimentacao *fim = NULL;

    if (inicio == NULL || *inicio != NULL) {

        return 0;

    }

    arquivo = fopen("movimentacoes.dat", "rb");

    if (arquivo == NULL) {

        return 1;

    }

    while (fread(&dados, sizeof(dados), 1, arquivo) == 1) {

        nova = (Movimentacao *)malloc(sizeof(Movimentacao));

        if (nova == NULL) {

            fclose(arquivo);

            return 0;
        }

        nova->sequencial = dados.sequencial;
        nova->codigo_conta = dados.codigo_conta;
        strcpy(nova->dt_movimento, dados.dt_movimento);
        strcpy(nova->tp_movimentacao, dados.tp_movimentacao);
        strcpy(nova->ds_favorecido, dados.ds_favorecido);
        nova->vl_movimento = dados.vl_movimento;
        nova->vl_saldo = dados.vl_saldo;

        nova->prox = NULL;

        if (fim == NULL) {

            *inicio = nova;

        } else {

            fim->prox = nova;

        }

            fim = nova;
            
    }

    if (ferror(arquivo)) {

        fclose(arquivo);

        return 0;

    }

    fclose(arquivo);

    return 1;

}



