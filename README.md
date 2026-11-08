# Sistema de Controle Bancário

O sistema permite o gerenciamento de contas bancárias, realização de movimentações financeiras e emissão de relatórios, utilizando listas encadeadas e manipulação de arquivos.

### Gerenciamento de contas
- Cadastro de contas no início, final e em posição específica.
- Consulta e alteração de contas.
- Remoção de contas.
- Ordenação de contas pelo código.

### Movimentações bancárias
- Realização de créditos e débitos.
- Transferências entre contas.
- Consulta do histórico de movimentações.
- Controle de saldo e limite de crédito.

### Relatórios
- Relatório de todas as contas.
- Extrato de uma conta.
- Relatório de contas inativas.
- Relatório de limites de crédito.

## Tecnologias utilizadas

- Linguagem C
- GCC
- Visual Studio Code
- Git e GitHub

## Estruturas de dados

- **Lista duplamente encadeada:** utilizada para armazenar as contas bancárias.
- **Lista simplesmente encadeada:** utilizada para armazenar as movimentações.

## Organização do projeto

SistemaControleBancario/
├── include/
│   └── estruturas.h
├── src/
│   ├── main.c
│   ├── contas.c
│   ├── movimentacoes.c
│   ├── arquivos.c
│   ├── relatorios.c
│   └── output/
├── docs/
│   └── documentacao.md
├── testes/
│   └── registro_testes.md
├── README.md
└── .gitignore

## Compilação

Abra o terminal na pasta principal do projeto e execute:


gcc -Wall -Wextra -g3 src/main.c src/contas.c src/movimentacoes.c src/arquivos.c src/relatorios.c -o src/output/main.exe


## Execução

No Windows, execute (no powershell):

.\src\output\main.exe


## Armazenamento

Os dados são armazenados em arquivos binários:

- `contas.dat`
- `movimentacoes.dat`

As informações são carregadas na inicialização e gravadas ao encerrar o sistema.

## Documentação

A documentação técnica esta disponível na pasta `docs`.




