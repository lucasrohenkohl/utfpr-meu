# Estoque de tomates — UTFPR

Trabalho de Algoritmos e Fundamentos de Programação em **C**, para executar no
console do Code::Blocks com compilador GCC.

O programa controla até **20 cadastros de tomate**. Cada cadastro contém código
positivo e único, nome de até 49 caracteres, quantidade inteira de caixas e
preço em reais por caixa. Os dados ficam em memória e são perdidos ao encerrar.

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
| 4 | Registrar entrada ou saída de caixas, sem permitir estoque negativo. |
| 5 | Mostrar total de caixas, valor do estoque, maior preço, média e reposições. |
| 6 | Limpar o estoque, apagando todos os cadastros e liberando as 20 vagas. |
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
(por exemplo, `Italiano`). Depois da escolha,
informe a quantidade e o preço por caixa. O tipo escolhido aparece na
listagem, na consulta e no relatório. Um mesmo tipo pode ter cadastros com
códigos diferentes; cada código continua sendo único.

- Digite **uma resposta por linha** e use ponto nos preços, como `35.50`.
- A quantidade inicial pode ser zero; o preço deve ser positivo.
- Entradas e saídas exigem quantidade inteira maior que zero.
- Códigos e quantidades respeitam o limite de `int` informado na tela; entradas
  que ultrapassariam esse limite de estoque são bloqueadas.
- Na opção de tipo **6 — Digitar outro nome**, nomes podem conter espaços, mas não podem
  ficar vazios ou exceder 49 caracteres.
  Para nomes acentuados, o limite é de 49 bytes na codificação do console.
- Letras em campos numéricos, números fracionados em quantidades e conteúdo
  extra na mesma linha são rejeitados, com nova solicitação da entrada.
- Código inexistente, estoque insuficiente e falta de cadastros geram mensagens
  informativas. O fim da entrada encerra o programa; cadastros incompletos não
  são contabilizados.

O valor do estoque é a soma de `quantidade × preço`. A média é esse valor
dividido pelo total de caixas disponíveis. Sem caixas, a média é informada como
indisponível. O maior preço considera todos os cadastros, inclusive os sem
estoque; em empate, permanece o primeiro cadastrado. A reposição lista os tipos
com quantidade zero.

A opção **6 — Limpar estoque** apaga todos os cadastros da execução atual,
incluindo códigos, nomes, quantidades e preços. Depois dela, é possível começar
novamente e reutilizar os códigos. A limpeza é feita zerando `total_cadastros`:
as posições antigas deixam de ser consultadas e são sobrescritas pelos novos
cadastros. Não é necessário percorrer e zerar cada vetor.

## Exemplo para conferir

Na opção 1 do menu principal, cadastre os seguintes valores na ordem
**código / número do tipo / caixas / preço**:

- `1 / 1 / 10 / 30.00` — Italiano;
- `2 / 2 / 5 / 50.00` — Cereja;
- `3 / 3 / 0 / 20.00` — Saladete.

Digite cada campo em uma linha. Para um nome personalizado, escolha o tipo 6
e digite o nome antes da quantidade e do preço.

Por exemplo, para cadastrar **Caqui**, escolha **1 — Cadastrar** no menu
principal, informe um código novo, escolha **6 — Digitar outro nome** e digite
`Caqui`. Em seguida, informe as caixas e o preço. Também é possível usar nomes
como `Rosa`, `Amarelo` ou `Tomate da horta`, que aparecerão nas listagens,
consultas e relatórios.

O relatório deverá mostrar **15 caixas**, **R$ 550.00** em estoque,
**Cereja** com maior preço (**R$ 50.00**), média de **R$ 36.67** por caixa
e **1 tipo sem estoque**, o Saladete.

Registre uma entrada de 3 caixas do Italiano: o saldo passa a 13. Uma saída de
4 passa o saldo a 9. Uma tentativa de saída de 10 é recusada, mantendo as 9
caixas. Após essas operações, o relatório deve indicar 14 caixas e R$ 520.00.

## Estruturas utilizadas

Toda a lógica está em `main`, com `printf` e `scanf`. O programa usa `if/else`,
`switch-case`, `do-while`, `for`, `while`, vetores de tamanho fixo e matriz de
caracteres. O contador `total_cadastros` delimita as posições válidas.

Cadastro, consulta e movimentação compartilham a leitura e a busca por código.
Um `for` lê os dois campos numéricos do cadastro ou da movimentação, reduzindo
a repetição das validações.

Os cinco tipos prontos ficam em uma matriz de caracteres. Um `for` copia o nome
escolhido para o cadastro, sem funções adicionais nem biblioteca de strings.

Não há funções próprias além de `main`, structs, variáveis ponteiro, alocação
dinâmica ou gravação de dados em arquivos. O `&` em `scanf` é necessário para
ler as variáveis, conforme o uso básico de entrada de dados em C.

As entradas numéricas são lidas em uma variável `double` para conferir a faixa
e rejeitar frações antes da conversão para `int`. O limite inteiro é definido
pela constante `LIMITE_INTEIRO`, com valor 2147483647 para o GCC/MinGW usado no
Code::Blocks. Não há uso de `limits.h`. `float.h` fornece o limite do preço.
Os preços são armazenados em `float`; os totais usam `double` e são exibidos
com duas casas decimais.

## Entrega

Preencha **nome completo, R.A. e turma** no comentário inicial e ajuste a data
se necessário. Para a entrega no ambiente virtual, envie somente
**`estoque_tomates.c`**, conforme o enunciado.
