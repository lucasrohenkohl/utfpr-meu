# Estoque de tomates — UTFPR

Trabalho de Algoritmos e Fundamentos de Programação em **C**, para executar no
console do Code::Blocks com compilador GCC.

O programa controla até **20 cadastros de tomate**. Cada cadastro contém código
positivo e único, nome de até 49 caracteres, unidade (caixas ou kg), quantidade e
preço em reais por caixa ou por kg. Os dados ficam em memória e são perdidos ao encerrar.

## Abrir no Code::Blocks

1. Use uma instalação do Code::Blocks com GCC/MinGW configurado.
2. Acesse **File → New → Project → Console application** e selecione **C**.
3. Remova o `main.c` gerado da lista de arquivos do projeto.
4. Use **Project → Add files** para adicionar `estoque_tomates.c`.
5. Se necessário, em **Project → Build options → Compiler settings**, habilite
   o padrão **C99**, ou adicione `-std=c99` em **Other compiler options**.
6. Pressione **F9 (Build and run)**.

Mantenha apenas um arquivo com `main` no projeto. As mensagens do programa usam
caracteres sem acentos para facilitar a exibição no console do Windows.

Também é possível compilar em um terminal com GCC:

```sh
gcc -std=c99 -Wall -Wextra -pedantic estoque_tomates.c -o estoque_tomates
./estoque_tomates
```

No Windows, o executável será `estoque_tomates.exe`.

## Menu e regras

| Opção | Operação |
| --- | --- |
| 1 | Cadastrar um tipo de tomate; bloqueia códigos repetidos e o 21º cadastro. |
| 2 | Listar todos os cadastros, com um separador a cada cinco registros. |
| 3 | Buscar pelo código e mostrar todos os campos do cadastro. |
| 4 | Registrar entrada ou saída na unidade do cadastro, sem permitir estoque negativo. |
| 5 | Mostrar cada produto, seu subtotal e os totais de caixas, kg e valor do estoque. |
| 6 | Limpar o estoque, apagando todos os cadastros e liberando as 20 vagas. |
| 7 | Apagar somente um cadastro, informando seu código. |
| 0 | Encerrar o programa. |

No cadastro, depois do código, escolha o tipo pelo número:

| Número | Tipo de tomate |
| --- | --- |
| 1 | Italiano |
| 2 | Cereja |
| 3 | Saladete |
| 4 | Santa Cruz |
| 5 | Débora |
| 6 | Digitar outro nome — permite cadastrar qualquer nome de até 49 caracteres. |

Nas opções 1 a 5, apenas o nome do tipo é preenchido automaticamente
(por exemplo, `Italiano`). Depois da escolha, selecione a unidade:

- **1 — Caixas:** quantidade inteira e preço por caixa.
- **2 — Quilogramas (kg):** peso com até três casas decimais e preço por kg.

Em seguida, informe a quantidade e o preço. O tipo e a unidade aparecem na
listagem, na consulta e no relatório. Um mesmo tipo pode ter cadastros com
códigos diferentes; cada código continua sendo único. Para controlar um tipo
em caixas e em kg, crie um cadastro para cada unidade, com códigos diferentes.

- Digite **uma resposta por linha** e use ponto nos pesos e preços, como `2.500` e `35.50`.
- A quantidade inicial pode ser zero; o preço deve ser positivo.
- Entradas e saídas exigem quantidade maior que zero: caixas inteiras ou kg
  com precisão de 0.001 kg (1 grama).
- Códigos e caixas vão até 2147483647; cada cadastro em kg admite até
  2147483.647 kg. Entradas que ultrapassariam esses saldos são bloqueadas.
- Na opção de tipo **6 — Digitar outro nome**, nomes podem conter espaços, mas não podem
  ficar vazios ou exceder 49 caracteres.
  Para nomes acentuados, o limite é de 49 bytes na codificação do console.
- Letras em campos numéricos, caixas fracionadas, pesos com frações menores
  que um grama e conteúdo extra na mesma linha são rejeitados, com nova
  solicitação da entrada.
- Código inexistente, estoque insuficiente e falta de cadastros geram mensagens
  informativas. O fim da entrada encerra o programa; cadastros incompletos não
  são contabilizados.

O relatório mostra **todos os produtos**, com código, nome, quantidade e unidade,
preço por caixa ou kg e subtotal (`quantidade × preço da unidade`). Depois dos
produtos, o resumo apresenta **total de caixas e total de kg separadamente**,
além da soma dos subtotais em reais. Os valores refletem os saldos
atuais, após entradas, saídas ou exclusões. Gerar o relatório não altera os dados.

O maior preço e a média são calculados **separadamente por unidade**. A média
por caixa usa o valor dos produtos em caixas dividido pelo total de caixas;
a média por kg usa o valor dos produtos em kg dividido pelo peso total.
Se todos os saldos de uma unidade forem zero, sua média fica indisponível.
O maior preço considera todos os cadastros daquela unidade, inclusive os sem
estoque; em empate, permanece o primeiro cadastrado. A reposição lista os
cadastros com quantidade zero.

A opção **6 — Limpar estoque** apaga todos os cadastros da execução atual,
incluindo códigos, nomes, unidades, quantidades e preços. Depois dela, é possível começar
novamente e reutilizar os códigos. A limpeza é feita zerando `total_cadastros`:
as posições antigas deixam de ser consultadas e são sobrescritas pelos novos
cadastros. Não é necessário percorrer e zerar cada vetor.

Para apagar **um cadastro por vez**, escolha **7 — Apagar um cadastro por código**
no menu principal e informe o código desejado. O programa remove esse cadastro
completo, incluindo nome, unidade, quantidade e preço, e mantém os demais na mesma ordem.
Se o código não existir, nenhuma alteração é feita. Cada exclusão libera uma
vaga, e o código apagado pode ser usado novamente.

## Exemplo para conferir

Na opção 1 do menu principal, cadastre os seguintes valores na ordem
**código / número do tipo / unidade / quantidade / preço por unidade**:

- `1 / 1 / 1 / 10 / 30.00` — Italiano em caixas;
- `2 / 2 / 1 / 5 / 50.00` — Cereja em caixas;
- `3 / 3 / 1 / 0 / 20.00` — Saladete em caixas.

Digite cada campo em uma linha. Para um nome personalizado, escolha o tipo 6
e digite o nome antes da unidade, quantidade e preço.

Por exemplo, para cadastrar **Caqui**, escolha **1 — Cadastrar** no menu
principal, informe um código novo, escolha **6 — Digitar outro nome** e digite
`Caqui`. Em seguida, escolha a unidade e informe a quantidade e o preço. Também é possível usar nomes
como `Rosa`, `Amarelo` ou `Tomate da horta`, que aparecerão nas listagens,
consultas e relatórios.

O relatório deverá mostrar **15 caixas**, **R$ 550.00** em estoque,
**Cereja** com maior preço (**R$ 50.00**), média de **R$ 36.67** por caixa
e **1 tipo sem estoque**, o Saladete.

Registre uma entrada de 3 caixas do Italiano: o saldo passa a 13. Uma saída de
4 passa o saldo a 9. Uma tentativa de saída de 10 é recusada, mantendo as 9
caixas. Após essas operações, o relatório deve indicar 14 caixas e R$ 520.00.

Outro exemplo: **40 caixas de Italiano a R$ 100.00** têm subtotal de R$ 4000.00;
**100 caixas de Débora a R$ 150.00** têm subtotal de R$ 15000.00. O resumo deve
mostrar **140 caixas e R$ 19000.00**, com os dois produtos detalhados. Após uma
entrada de 10 caixas de Débora, seu saldo passa a 110 e o resumo passa a
**150 caixas e R$ 20500.00**.

Para conferir um estoque com as duas unidades, cadastre `1 / 1 / 1 / 2 / 30.00`
e `2 / 2 / 2 / 2.500 / 8.00`. Os subtotais serão R$ 60.00 e R$ 20.00; o resumo
mostrará **2 caixas**, **2.500 kg** e **R$ 80.00**. Uma saída de `0.250` kg do
segundo cadastro deixa seu saldo em **2.250 kg** e o valor geral em **R$ 78.00**.

## Estruturas utilizadas

Toda a lógica está em `main`, com `printf` e `scanf`. O programa usa `if/else`,
`switch-case`, `do-while`, `for`, `while`, vetores de tamanho fixo e matriz de
caracteres. O contador `total_cadastros` delimita as posições válidas.

Cadastro, consulta, movimentação e exclusão compartilham a leitura e a busca por código.
Um `for` lê os dois campos numéricos do cadastro ou da movimentação, reduzindo
a repetição das validações.

Os cinco tipos prontos ficam em uma matriz de caracteres. Um `for` copia o nome
escolhido para o cadastro, sem funções adicionais nem biblioteca de strings.
Na exclusão individual, laços `for` deslocam os vetores e a matriz de nomes para
preencher a posição removida, incluindo o vetor de unidades, e o contador de
cadastros é decrementado.

O vetor de unidades guarda a escolha de cada cadastro. As quantidades continuam
em `int`: caixas são armazenadas diretamente; pesos são convertidos em gramas
inteiras. Isso permite entradas e saídas como 0.100 kg e 0.200 kg sem deixar um
resíduo de arredondamento ao retirar 0.300 kg. A exibição e o cálculo do subtotal
convertem gramas para kg dividindo por 1000.0.

Não há funções próprias além de `main`, structs, variáveis ponteiro, alocação
dinâmica ou gravação de dados em arquivos. O `&` em `scanf` é necessário para
ler as variáveis, conforme o uso básico de entrada de dados em C.

As entradas numéricas são lidas em uma variável `double` para conferir a faixa
e validar a precisão antes da conversão para `int`. Na conversão de kg para
gramas, uma tolerância de 0.000001 grama compensa apenas erros de representação
binária. O limite inteiro é definido
pela constante `LIMITE_INTEIRO`, com valor 2147483647 para o GCC/MinGW usado no
Code::Blocks. Não há uso de `limits.h`. `float.h` fornece o limite do preço.
Os preços são armazenados em `float`; os totais usam `double` e são exibidos
com duas casas decimais.

## Entrega

Para a entrega no ambiente virtual, envie somente
**`estoque_tomates.c`**, conforme o enunciado.
