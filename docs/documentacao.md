# DOCUMENTAÇÃO TÉCNICA
# Sistema de Controle Bancário

### 1. Apresentação

O objetivo do sistema é permitir o gerenciamento de contas bancárias e suas movimentações, utilizando alocação dinâmica de memória, ponteiros e listas encadeadas.

### 2. As tecnologias utilizadas

- Linguagem C.
- Compilador GCC.
- Visual Studio Code.
- Sistema operacional Windows.
- Git e GitHub para controle de versão e sincronização do projeto.

### 3. Organização dos arquivos

O projeto foi organizado nessa seguinte maneira:

- `include/estruturas.h`: contém as estruturas de dados e os protótipos das funções.
- `src/main.c`: contém a função principal e os menus de navegação.
- `src/contas.c`: contém as operações de cadastro, consulta, alteração, remoção e ordenação de contas.
- `src/movimentacoes.c`: contém as operações de crédito, débito, transferência e consulta de movimentações.
- `src/arquivos.c`: responsável pela gravação e leitura dos dados em arquivos.
- `src/relatorios.c`: contém os relatórios do sistema.

### 4. Estruturas de dados

O sistema utiliza duas estruturas principais:

**Conta**

As contas bancárias são armazenadas em uma lista duplamente encadeada. Cada elemento possui os dados da conta e dois ponteiros: `ant` e `prox`, que permitem acessar o elemento anterior e o próximo.

**Movimentacao**

As movimentações são armazenadas em uma lista simplesmente encadeada. Cada elemento possui os dados da movimentação e um ponteiro `prox`, que permite acessar o próximo elemento.

### 5. Funcionalidades implementadas

**Gerenciamento de contas**
- Cadastro de contas no início, no final e em uma posição específica.
- Alteração de dados das contas.
- Consulta de contas.
- Remoção de contas no início, no final e em uma posição específica.
- Ordenação das contas pelo código em ordem crescente.

**Movimentações bancárias**
- Realização de créditos.
- Realização de débitos.
- Transferência entre contas.
- Consulta do histórico de movimentações.
- Atualização dos saldos das contas.

**Validações**
- Verificação de códigos de contas duplicados.
- Impedimento de movimentações em contas inativas.
- Verificação do saldo disponível e do limite de crédito.
- Validação das datas das movimentações.
- Impedimento da exclusão de contas que possuem movimentações.

**Relatórios**
- Relatório de todas as contas cadastradas.
- Extrato de uma conta específica.
- Relatório de contas inativas.
- Relatório de limites de crédito.

### 6. Armazenamento dos dados

O sistema utiliza arquivos para manter os dados cadastrados mesmo após seu encerramento.

Os dados das contas são armazenados em `contas.dat`, enquanto as movimentações são armazenadas em `movimentacoes.dat`.

Ao iniciar o programa, os dados são carregados dos arquivos. Ao encerrar, as informações são gravadas para que possam ser utilizadas na próxima execução.

### 7. Compilação e execução

Para compilar o projeto utilizando o GCC, execute o seguinte comando no terminal, a partir da pasta principal:

gcc -Wall -Wextra -g3 src/main.c src/contas.c src/movimentacoes.c src/arquivos.c src/relatorios.c -o src/output/main.exe

Para executar o programa no Windows:

.\src\output\main.exe

### 8. Considerações finais

O desenvolvimento do projeto permitiu aplicar conceitos de linguagem C, alocação dinâmica de memória, ponteiros, listas encadeadas, manipulação de arquivos e organização de código em múltiplos arquivos. O sistema reúne funcionalidades de gerenciamento de contas, movimentações bancárias e emissão de relatórios, conforme os requisitos propostos na atividade.

