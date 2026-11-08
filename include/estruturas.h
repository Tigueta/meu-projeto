/*
 * Nome: Santiago Gabriel Reyes
 * Data: 30/10/26
 * Arquivo: estruturas.h
 * Descricao: Contem as estruturas de dados e os prototipos das funcoes do sistema bancario.
 */

typedef struct Conta
{

    int codigo_conta;
    char banco[50];
    char agencia[10];
    char numero_conta[20];
    char tipo_conta[20];
    double vl_saldo;
    double vl_limite;
    char status[10];

    struct Conta *ant;
    struct Conta *prox;

} Conta;

typedef struct Movimentacao
{

    int sequencial;
    int codigo_conta;
    char dt_movimento[11];
    char tp_movimentacao[15];
    char ds_favorecido[50];
    double vl_movimento;
    double vl_saldo;

    struct Movimentacao *prox;

} Movimentacao;

int codigo_existe(Conta *inicio, int codigo);
int cadastrar_dados(Conta *nova, Conta *inicio);
void cadastrar_inicio(Conta **inicio);
void cadastrar_final(Conta **inicio);
void cadastrar_posicao(Conta **inicio);
void listar_contas(Conta *inicio);
void alterar_conta(Conta *inicio);
void remover_inicio(Conta **inicio, Movimentacao *movimentos);
void remover_final(Conta **inicio, Movimentacao *movimentos);
void remover_posicao(Conta **inicio, Movimentacao *movimentos);
void consultar_contas(Conta *inicio);

int conta_tem_movimentacao(Movimentacao *movimentos, int codigo);
void realizar_movimentacao(Conta *contas, Movimentacao **movimentos);
void consultar_movimentacoes(Conta *contas, Movimentacao *movimentos);
void realizar_transferencia(Conta *contas, Movimentacao **movimentos);

int salvar_contas(Conta *inicio);
int carregar_contas(Conta **inicio);
int salvar_movimentacoes(Movimentacao *inicio);
int carregar_movimentacoes(Movimentacao **inicio);
void liberar_contas(Conta *inicio);

void relatorio_contas(Conta *inicio);
void relatorio_extrato(Conta *contas, Movimentacao *movimentos);
void relatorio_inativas(Conta *inicio);
void relatorio_limites(Conta *inicio);

void ordenar_contas(Conta **inicio);

