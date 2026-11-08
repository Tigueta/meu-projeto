/*
 * Nome: Jose Manuel Salazar e Santiago Gabriel Reyes
 * Data: 01/11/26
 * Arquivo: arquivos.c
 * Descricao: Contem as funcoes de leitura e escrita de arquivos binarios para persistencia dos dados do sistema bancario.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../include/estruturas.h"

#define ARQUIVO_CONTAS "contas.dat"
#define ARQUIVO_MOVIMENTACOES "movimentacoes.dat"

#define TEMP_CONTAS "contas.tmp"
#define TEMP_MOVIMENTACOES "movimentacoes.tmp"

#define MAX_REGISTROS 1000000

typedef struct
{
    char identificacao[9];
    unsigned int versao;
    unsigned int quantidade;
} Cabecalho;

typedef struct
{
    int codigo_conta;
    char banco[50];
    char agencia[10];
    char numero_conta[20];
    char tipo_conta[20];
    double vl_saldo;
    double vl_limite;
    char status[10];
} DadosConta;

typedef struct
{
    int sequencial;
    int codigo_conta;
    char dt_movimento[11];
    char tp_movimentacao[15];
    char ds_favorecido[50];
    double vl_movimento;
    double vl_saldo;
} DadosMovimentacao;

int arquivo_inexistente(char nome[])
{
    DWORD resultado = GetFileAttributesA(nome);

    if (resultado == INVALID_FILE_ATTRIBUTES)
    {
        DWORD erro = GetLastError();

        if (erro == ERROR_FILE_NOT_FOUND ||
            erro == ERROR_PATH_NOT_FOUND)
            return 1;
    }

    return 0;
}

void liberar_contas(Conta *inicio)
{
    Conta *aux;

    while (inicio != NULL)
    {
        aux = inicio;
        inicio = inicio->prox;
        free(aux);
    }
}

void liberar_movimentacoes(Movimentacao *inicio)
{
    Movimentacao *aux;

    while (inicio != NULL)
    {
        aux = inicio;
        inicio = inicio->prox;
        free(aux);
    }
}

int texto_valido(char texto[], int tamanho)
{
    return memchr(texto, '\0', tamanho) != NULL;
}

int ler_cabecalho(FILE *arquivo, char identificacao[], unsigned int *quantidade) {

    Cabecalho cabecalho;

    if (fread(&cabecalho, sizeof(cabecalho), 1, arquivo) != 1)

        return 0;

    if (strcmp(cabecalho.identificacao, identificacao) != 0)

        return 0;

    if (cabecalho.versao != 1 || cabecalho.quantidade > MAX_REGISTROS)

        return 0;

    *quantidade = cabecalho.quantidade;

    return 1;

}

int salvar_contas(Conta *inicio) {

    FILE *arquivo;
    Conta *aux;
    DadosConta dados;
    Cabecalho cabecalho;
    unsigned int quantidade = 0;
    int sucesso = 1;

    for (aux = inicio; aux != NULL; aux = aux->prox) {

        if (quantidade >= MAX_REGISTROS)

            return 0;

        quantidade++;

    }

    arquivo = fopen(TEMP_CONTAS, "wb");

    if (arquivo == NULL)

        return 0;

    memset(&cabecalho, 0, sizeof(cabecalho));

    strcpy(cabecalho.identificacao, "CONTAS");
    cabecalho.versao = 1;
    cabecalho.quantidade = quantidade;

    if (fwrite(&cabecalho, sizeof(cabecalho), 1, arquivo) != 1)
        sucesso = 0;

    for (aux = inicio; aux != NULL && sucesso; aux = aux->prox)
    {
        memset(&dados, 0, sizeof(dados));

        dados.codigo_conta = aux->codigo_conta;
        strcpy(dados.banco, aux->banco);
        strcpy(dados.agencia, aux->agencia);
        strcpy(dados.numero_conta, aux->numero_conta);
        strcpy(dados.tipo_conta, aux->tipo_conta);
        dados.vl_saldo = aux->vl_saldo;
        dados.vl_limite = aux->vl_limite;
        strcpy(dados.status, aux->status);

        if (fwrite(&dados, sizeof(dados), 1, arquivo) != 1)
            sucesso = 0;
    }

    if (fclose(arquivo) != 0)
        sucesso = 0;

    if (!sucesso)
    {
        remove(TEMP_CONTAS);
        return 0;
    }

    if (!MoveFileExA(TEMP_CONTAS, ARQUIVO_CONTAS,
                     MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
    {
        remove(TEMP_CONTAS);
        return 0;
    }

    return 1;
}

int carregar_contas(Conta **inicio)
{
    FILE *arquivo;
    Conta *nova;
    Conta *fim = NULL;
    DadosConta dados;
    unsigned int quantidade = 0;
    unsigned int i;
    int sucesso = 1;

    if (inicio == NULL || *inicio != NULL)
        return 0;

    arquivo = fopen(ARQUIVO_CONTAS, "rb");

    if (arquivo == NULL)
    {
        if (arquivo_inexistente(ARQUIVO_CONTAS))
            return 1;

        return 0;
    }

    if (!ler_cabecalho(arquivo, "CONTAS", &quantidade))
        sucesso = 0;

    for (i = 0; i < quantidade && sucesso; i++)
    {
        if (fread(&dados, sizeof(dados), 1, arquivo) != 1)
        {
            sucesso = 0;
            break;
        }

        if (!texto_valido(dados.banco, sizeof(dados.banco)) ||
            !texto_valido(dados.agencia, sizeof(dados.agencia)) ||
            !texto_valido(dados.numero_conta, sizeof(dados.numero_conta)) ||
            !texto_valido(dados.tipo_conta, sizeof(dados.tipo_conta)) ||
            !texto_valido(dados.status, sizeof(dados.status)) ||
            dados.codigo_conta <= 0 ||
            dados.vl_limite < 0)
        {
            sucesso = 0;
            break;
        }

        nova = (Conta *)malloc(sizeof(Conta));

        if (nova == NULL)
        {
            sucesso = 0;
            break;
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

        if (fim == NULL)
            *inicio = nova;
        else
            fim->prox = nova;

        fim = nova;
    }

    if (sucesso && fgetc(arquivo) != EOF)
        sucesso = 0;

    if (fclose(arquivo) != 0)
        sucesso = 0;

    if (!sucesso)
    {
        liberar_contas(*inicio);
        *inicio = NULL;
        return 0;
    }

    return 1;
}

int salvar_movimentacoes(Movimentacao *inicio)
{
    FILE *arquivo;
    Movimentacao *aux;
    DadosMovimentacao dados;
    Cabecalho cabecalho;
    unsigned int quantidade = 0;
    int sucesso = 1;

    for (aux = inicio; aux != NULL; aux = aux->prox)
    {
        if (quantidade >= MAX_REGISTROS)
            return 0;

        quantidade++;
    }

    arquivo = fopen(TEMP_MOVIMENTACOES, "wb");

    if (arquivo == NULL)
        return 0;

    memset(&cabecalho, 0, sizeof(cabecalho));

    strcpy(cabecalho.identificacao, "MOVIMENT");
    cabecalho.versao = 1;
    cabecalho.quantidade = quantidade;

    if (fwrite(&cabecalho, sizeof(cabecalho), 1, arquivo) != 1)
        sucesso = 0;

    for (aux = inicio; aux != NULL && sucesso; aux = aux->prox)
    {
        memset(&dados, 0, sizeof(dados));

        dados.sequencial = aux->sequencial;
        dados.codigo_conta = aux->codigo_conta;
        strcpy(dados.dt_movimento, aux->dt_movimento);
        strcpy(dados.tp_movimentacao, aux->tp_movimentacao);
        strcpy(dados.ds_favorecido, aux->ds_favorecido);
        dados.vl_movimento = aux->vl_movimento;
        dados.vl_saldo = aux->vl_saldo;

        if (fwrite(&dados, sizeof(dados), 1, arquivo) != 1)
            sucesso = 0;
    }

    if (fclose(arquivo) != 0)
        sucesso = 0;

    if (!sucesso)
    {
        remove(TEMP_MOVIMENTACOES);
        return 0;
    }

    if (!MoveFileExA(TEMP_MOVIMENTACOES, ARQUIVO_MOVIMENTACOES,
                     MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
    {
        remove(TEMP_MOVIMENTACOES);
        return 0;
    }

    return 1;
}

int carregar_movimentacoes(Movimentacao **inicio)
{
    FILE *arquivo;
    Movimentacao *nova;
    Movimentacao *fim = NULL;
    DadosMovimentacao dados;
    unsigned int quantidade = 0;
    unsigned int i;
    int sucesso = 1;

    if (inicio == NULL || *inicio != NULL)
        return 0;

    arquivo = fopen(ARQUIVO_MOVIMENTACOES, "rb");

    if (arquivo == NULL)
    {
        if (arquivo_inexistente(ARQUIVO_MOVIMENTACOES))
            return 1;

        return 0;
    }

    if (!ler_cabecalho(arquivo, "MOVIMENT", &quantidade))
        sucesso = 0;

    for (i = 0; i < quantidade && sucesso; i++)
    {
        if (fread(&dados, sizeof(dados), 1, arquivo) != 1)
        {
            sucesso = 0;
            break;
        }

        if (!texto_valido(dados.dt_movimento, sizeof(dados.dt_movimento)) ||
            !texto_valido(dados.tp_movimentacao, sizeof(dados.tp_movimentacao)) ||
            !texto_valido(dados.ds_favorecido, sizeof(dados.ds_favorecido)) ||
            dados.sequencial <= 0 ||
            dados.codigo_conta <= 0 ||
            dados.vl_movimento <= 0)
        {
            sucesso = 0;
            break;
        }

        nova = (Movimentacao *)malloc(sizeof(Movimentacao));

        if (nova == NULL)
        {
            sucesso = 0;
            break;
        }

        nova->sequencial = dados.sequencial;
        nova->codigo_conta = dados.codigo_conta;
        strcpy(nova->dt_movimento, dados.dt_movimento);
        strcpy(nova->tp_movimentacao, dados.tp_movimentacao);
        strcpy(nova->ds_favorecido, dados.ds_favorecido);
        nova->vl_movimento = dados.vl_movimento;
        nova->vl_saldo = dados.vl_saldo;
        nova->prox = NULL;

        if (fim == NULL)
            *inicio = nova;
        else
            fim->prox = nova;

        fim = nova;
    }

    if (sucesso && fgetc(arquivo) != EOF)
        sucesso = 0;

    if (fclose(arquivo) != 0)
        sucesso = 0;

    if (!sucesso)
    {
        liberar_movimentacoes(*inicio);
        *inicio = NULL;
        return 0;
    }

    return 1;
}

