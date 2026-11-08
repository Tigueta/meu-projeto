# REGISTRO DE TESTES

### 1. Cadastro de contas

- **Procedimento:** cadastrar contas no início, no final e em posições específicas da lista.
- **Resultado esperado:** inserir as contas nas posições escolhidas, mantendo a organização da lista.
- **Resultado obtido:** as contas foram cadastradas corretamente.
- **Situação:** Aprovado.

### 2. Consulta de contas

- **Procedimento:** consultar uma conta específica e listar todas as contas cadastradas.
- **Resultado esperado:** exibir corretamente os dados das contas.
- **Resultado obtido:** as informações foram exibidas corretamente.
- **Situação:** Aprovado.

### 3. Alteração de contas

- **Procedimento:** selecionar uma conta e alterar seus dados.
- **Resultado esperado:** atualizar corretamente as informações da conta.
- **Resultado obtido:** alteração realizada corretamente.
- **Situação:** Aprovado.

### 4. Remoção de contas

- **Procedimento:** remover contas no início, no final e em posições específicas.
- **Resultado esperado:** excluir a conta selecionada sem comprometer os ponteiros da lista.
- **Resultado obtido:** remoções realizadas corretamente.
- **Situação:** Aprovado.

### 5. Ordenação de contas

- **Procedimento:** cadastrar contas com códigos fora de ordem e utilizar a função de ordenação.
- **Resultado esperado:** organizar as contas pelo código em ordem crescente.
- **Resultado obtido:** contas ordenadas corretamente.
- **Situação:** Aprovado.

### 6. Créditos e débitos

- **Procedimento:** realizar operações de crédito e débito em contas cadastradas.
- **Resultado esperado:** atualizar corretamente o saldo após cada movimentação.
- **Resultado obtido:** movimentações realizadas e saldos atualizados corretamente.
- **Situação:** Aprovado.

### 7. Transferências

- **Procedimento:** realizar transferências entre duas contas cadastradas.
- **Resultado esperado:** debitar o valor da conta de origem e creditar na conta de destino.
- **Resultado obtido:** transferência realizada corretamente.
- **Situação:** Aprovado.

### 8. Validação de saldo e limite

- **Procedimento:** tentar realizar débitos que ultrapassem o saldo disponível e o limite de crédito.
- **Resultado esperado:** impedir operações que ultrapassem o limite permitido.
- **Resultado obtido:** validação funcionando corretamente.
- **Situação:** Aprovado.

### 9. Validação de datas

- **Procedimento:** informar datas inválidas ou anteriores à última movimentação da conta.
- **Resultado esperado:** impedir o registro de datas inválidas ou fora da sequência permitida.
- **Resultado obtido:** validação funcionando corretamente.
- **Situação:** Aprovado.

### 10. Contas inativas

- **Procedimento:** tentar realizar movimentações e transferências utilizando contas inativas.
- **Resultado esperado:** impedir as operações.
- **Resultado obtido:** bloqueio funcionando corretamente.
- **Situação:** Aprovado.

### 11. Consulta de movimentações

- **Procedimento:** consultar o histórico de movimentações de uma conta.
- **Resultado esperado:** exibir somente as movimentações relacionadas à conta selecionada.
- **Resultado obtido:** histórico exibido corretamente.
- **Situação:** Aprovado.

### 12. Relatórios

- **Procedimento:** acessar os relatórios de contas, extrato, contas inativas e limites de crédito.
- **Resultado esperado:** apresentar corretamente as informações solicitadas.
- **Resultado obtido:** relatórios funcionando corretamente.
- **Situação:** Aprovado.

### 13. Paginação

- **Procedimento:** consultar listas e extratos com quantidade de registros suficiente para utilizar várias páginas.
- **Resultado esperado:** permitir a visualização de todos os registros por meio da paginação.
- **Resultado obtido:** paginação funcionando corretamente.
- **Situação:** Aprovado.

### 14. Gravação e leitura de arquivos

- **Procedimento:** cadastrar contas e movimentações, encerrar o programa e abri-lo novamente.
- **Resultado esperado:** recuperar os dados anteriormente armazenados.
- **Resultado obtido:** dados carregados corretamente após reiniciar o programa.
- **Situação:** Aprovado.

